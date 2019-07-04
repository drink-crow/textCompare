#include "stdafx.h"
#include "weiTextedit.h"

weiTextedit::weiTextedit(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//ui.lineBrowser->setWordWrapMode(QTextOption::NoWrap);
	////关闭行号的滚动条
	//ui.lineBrowser->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	//ui.lineBrowser->setAlignment(Qt::AlignRight);
	
	//ui.lineBrowser->setDisabled(true);
	ui.modifyColor->setConnectedTextEdit(ui.textEdit);

	scLine = ui.lineBrowser->verticalScrollBar();
	scText = ui.textEdit->verticalScrollBar();
	scColor = ui.modifyColor->verticalScrollBar();

	//connect(ui.textEdit, SIGNAL(textChanged()), this, SLOT(contentChanged()));
	connect(ui.textEdit, SIGNAL(scrollBarMove(int, int)), this, SLOT(handleScrollBarMove(int, int)));

	//
	connect(ui.textEdit, SIGNAL(cursorPositionChanged()), this, SLOT(cursorTextEditChanged()));
	connect(ui.textEdit, SIGNAL(selectionChanged()), this, SLOT(selectionTextEditChanged()));
	connect(ui.textEdit, SIGNAL(redoSingal()), this, SLOT(textRedo()));
	connect(ui.textEdit, SIGNAL(undoSingal()), this, SLOT(textUndo()));
	connect(ui.textEdit->document(), SIGNAL(contentsChange(int, int, int)), this, SLOT(contentChanged(int, int, int)));

}

void weiTextedit::setWordWrapMode(QTextOption::WrapMode policy)
{
	ui.textEdit->setWordWrapMode(policy);
}

void weiTextedit::setPlainText(QString &str)
{
	ui.textEdit->setPlainText(str);
}

bool weiTextedit::openFiletoEdit(QString file)
{
	
	
	QFile fFile(file);
	if (!fFile.open(QIODevice::ReadWrite | QIODevice::Text))
	{
		QMessageBox::critical(NULL, "Open Error", "can not open file " + file, QMessageBox::Yes, QMessageBox::Yes);
		return false;
	}
	QTextStream in(&fFile);

	this->ui.modifyColor->setFileOpening();
	this->setPlainText(in.readAll());
	
	return true;
}

//同步行号和编辑器的滑条
void weiTextedit::handleScrollBarMove(int dx, int dy)
{
	//char t[50]; sprintf_s(t, "dx=%d,dy=%d\n", dx, dy);
	//qDebug(t);
	scLine->setValue(scText->value());
	scColor->setValue(scText->value());
}

void weiTextedit::cursorTextEditChanged()
{
	//ui.modifyColor->cursorTextEditChanged();
}

void weiTextedit::selectionTextEditChanged()
{
	//ui.modifyColor->selectionTextEditChanged();
}

void weiTextedit::textUndo()
{
	ui.modifyColor->setUndo();
}

void weiTextedit::textRedo()
{
	ui.modifyColor->setRedo();
}

void weiTextedit::contentChanged(int position, int charsRemoved, int charsAdded)
{
	//qDebug() << "-----------into contentChanged-------------\n";
	
	//改变行号
	int contentLineCount = ui.textEdit->document()->lineCount();
	int lineBrowserLineCount = ui.lineBrowser->document()->lineCount();

	if (lineBrowserLineCount - 1 != contentLineCount)
	{
		int t = scText->value();
		ui.lineBrowser->setLineNum(contentLineCount);
		scLine->setValue(t);
	}

	//新旧文本字符总数一样，只要判断被改变的范围前后是否一致就好了
	//如此判断是因为在中文输入法下，文本输入为完成也会有contentsChange(int, int, int)信号产生
	QTextDocument *d = ui.textEdit->document();
	QString addText(d->toPlainText().mid(position, charsAdded));
	if (charsRemoved == charsAdded)
	{	
		//前后文本一致，无须改变，先判断是否有选择移动
		if (!ui.textEdit->getIsSelectMove() && text.mid(position, charsAdded) == addText)
		{
			return;
		}
	}
	qDebug() << "ROW position: " << position << " charsRemoved: " << charsRemoved << " charsAdded: " << charsAdded << endl;
	//改变现有文本
	QString removedText = text.mid(position, charsRemoved);
	text.replace(position, charsRemoved, addText);
	//qDebug() << "context changed!!!!!!\nposition = " << position << "charsRemoved = " << charsRemoved << "charsAdded" << charsAdded << endl;
	//一行为单位

	vector<int> vPosition;
	vector<int> vCharsRemoved;
	vector<int> vCharsAdded;
	changeType type = changeType::defualt;
	QTextCursor c = ui.textEdit->textCursor();
	c.setPosition(position, QTextCursor::MoveAnchor);

	//选择移动模式下
	if (ui.textEdit->getIsSelectMove())
	{
		type = changeType::move;

		int selectStartLine = ui.textEdit->getSelectStartLineNum();
		int effectCount = ui.textEdit->getSelectEndLineNum() - ui.textEdit->getSelectStartLineNum() + 1;
		int startLine = c.blockNumber();
		//移动到被选择目标的前面
		//这两个等于证明是移动到原来位置的后面或者同一行间移动
		if (selectStartLine == startLine)
		{
			//这里的顺序一定要先删了再增
			vPosition.push_back(startLine);
			vCharsRemoved.push_back(effectCount);
			vCharsAdded.push_back(1);

			vPosition.push_back(startLine + removedText.count('\n') + 1 - effectCount);
			vCharsRemoved.push_back(1);
			vCharsAdded.push_back(effectCount);
		}
		//移动到原来位置的前面
		else
		{
			//这里的顺序一定要先删了再增
			vPosition.push_back(selectStartLine);
			vCharsRemoved.push_back(effectCount);
			vCharsAdded.push_back(1);

			vPosition.push_back(startLine);
			vCharsRemoved.push_back(1);
			vCharsAdded.push_back(effectCount);
		}

		qDebug() << "move position: " << vPosition[0] << " charsRemoved: " << vCharsRemoved[0] << " charsAdded: " << vCharsAdded[0] << endl;
		qDebug() << "move position: " << vPosition[1] << " charsRemoved: " << vCharsRemoved[1] << " charsAdded: " << vCharsAdded[1] << endl;

		ui.textEdit->doneSelectMove();
	}
	//普通修改模式
	else
	{
		vPosition.push_back(c.blockNumber());

		int removedLineCount = removedText.count('\n');
		int addedLineCount = addText.count('\n');
		//这种情况是插入一个字符，给出的charsRemoved，charsAdded是删去一整行又加上一整行的
		if (1 == removedLineCount &&
			1 == addedLineCount && 
			removedText.endsWith('\n') && 
			removedText.endsWith('\n'))
		{
			vCharsRemoved.push_back(1);
			vCharsAdded.push_back(1);
		}
		else
		{
			vCharsRemoved.push_back(removedText.count('\n') + 1);
			vCharsAdded.push_back(addText.count('\n') + 1);
		}
			qDebug() << "defualt position: " << vPosition[0] << " charsRemoved: " << vCharsRemoved[0] << " charsAdded: " << vCharsAdded[0] << endl;
	}

	//改变修改颜色提示框
	int t = scText->value();
	ui.modifyColor->contentChange(type, vPosition, vCharsRemoved, vCharsAdded, charsAdded - charsRemoved);
	scColor->setValue(t);
}

