#include "stdafx.h"
#include "weiTextedit.h"

weiTextedit::weiTextedit(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//ui.lineBrowser->setWordWrapMode(QTextOption::NoWrap);
	////�ر��кŵĹ�����
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

//ͬ���кźͱ༭���Ļ���
void weiTextedit::handleScrollBarMove(int dx, int dy)
{
	//char t[50]; sprintf_s(t, "dx=%d,dy=%d\n", dx, dy);
	//qDebug(t);
	scLine->setValue(scText->value());
	scColor->setValue(scText->value());
}

void weiTextedit::cursorTextEditChanged()
{
	ui.modifyColor->cursorTextEditChanged();
}

void weiTextedit::selectionTextEditChanged()
{
	ui.modifyColor->selectionTextEditChanged();
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
	
	//�ı��к�
	int contentLineCount = ui.textEdit->document()->lineCount();
	int lineBrowserLineCount = ui.lineBrowser->document()->lineCount();

	if (lineBrowserLineCount - 1 != contentLineCount)
	{
		int t = scText->value();
		ui.lineBrowser->setLineNum(contentLineCount);
		scLine->setValue(t);
	}

	//�¾��ı��ַ�����һ����ֻҪ�жϱ��ı�ķ�Χǰ���Ƿ�һ�¾ͺ���
	//����ж�����Ϊ���������뷨�£��ı�����Ϊ���Ҳ����contentsChange(int, int, int)�źŲ���
	QString addText(ui.textEdit->document()->toPlainText().mid(position, charsAdded));
	if (charsRemoved == charsAdded)
	{	
		//ǰ���ı�һ�£�����ı�
		if (text.mid(position, charsAdded) == addText)
		{
			return;
		}
	}
	//�ı������ı�
	text.replace(position, charsRemoved, addText);
	//qDebug() << "context changed!!!!!!\nposition = " << position << "charsRemoved = " << charsRemoved << "charsAdded" << charsAdded << endl;

	//�ı��޸���ɫ��ʾ��
	int t = scText->value();
	ui.modifyColor->contentChange(position, charsRemoved, charsAdded);
	scColor->setValue(t);

}

