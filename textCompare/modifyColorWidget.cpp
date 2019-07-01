#include "stdafx.h"
#include "modifyColorWidget.h"


modifyColorWidget::modifyColorWidget(QWidget *parent)
	:QTextEdit(parent)
{
	connectedTextEdit = nullptr;

	docBit2Color.insert(modStatus::native, Qt::white);
	docBit2Color.insert(modStatus::modified, Qt::yellow);
	docBit2Color.insert(modStatus::saved, Qt::green);

	undoStack = new QUndoStack(this);
	undoAction = undoStack->createUndoAction(this, "Undo");
	redoAction = undoStack->createRedoAction(this, "Redo");
	this->addAction(undoAction);
	this->addAction(redoAction);

	undoView = new QUndoView(undoStack);

	lineCount = -1;
	lineStr = "O\n";

	isRedo = false;
	isUndo = false;

	isFileOpening = false;


	int fontId = QFontDatabase::addApplicationFont(":/Font/Font/consola.ttf");
	QString consola = QFontDatabase::applicationFontFamilies(fontId).at(0);
	QFont font(consola);
	setFont(font);

	this->setAlignment(Qt::AlignHCenter);
}


modifyColorWidget::~modifyColorWidget()
{
}

void modifyColorWidget::setConnectedTextEdit(QTextEdit * connected)
{
	connectedTextEdit = connected;
}

void modifyColorWidget::contentChange(int position, int charsRemoved, int charsAdded)
{
	if (connectedTextEdit == nullptr)
		return;
	else if (isFileOpening)
	{
		new modCommand(this);
		isFileOpening = false;
	}
	else if (isRedo == true)
	{
		isRedo = false;
		undoStack->redo();
	}
	else if (isUndo == true)
	{
		isUndo = false;
		undoStack->undo();
	}
	else if (doc.isEmpty())
	{
		docBit.clear();
		int num = connectedTextEdit->document()->lineCount();
		for (int i = 0; i < num; i++)
		{
			doc += lineStr;
			docBit << modStatus::native;
		}
		this->setText(doc);
		lineCount = num;
		preLineCount = connectedTextEdit->document()->lineCount();
	}
	//重写2
	else
	{
		undoStack->push(new modCommand(this));
	}

	this->moveCursor(QTextCursor::Start);
	debugBit();
}

void modifyColorWidget::selectionTextEditChanged()
{
	if (connectedTextEdit == nullptr)
		return;

	//由于对框选的内容做出改变时，会先触发选择内容改变信号，再触发文本改变信号，所以要把上一次的框选信息储存起来
	preSelect = curSelect;

	QTextCursor c = connectedTextEdit->textCursor();
	QTextDocument *d = connectedTextEdit->document();

	curSelect.TextSelectedStart = c.selectionStart();
	curSelect.TextSelectedEnd = c.selectionEnd();

	c.setPosition(curSelect.TextSelectedStart, QTextCursor::MoveAnchor);
	curSelect.LineNumTextSelectedStart = c.blockNumber();
	c.setPosition(curSelect.TextSelectedEnd, QTextCursor::MoveAnchor);
	curSelect.LineNumTextSelectedEnd = c.blockNumber();


	curSelect.IsSelectStartPosInHome = (curSelect.TextSelectedStart == d->findBlockByNumber(curSelect.LineNumTextSelectedStart).position()) ? 1 : 0;
	curSelect.IsSelectEndPosInHome = (curSelect.TextSelectedEnd == d->findBlockByNumber(curSelect.LineNumTextSelectedEnd).position()) ? 1 : 0;

	qDebug() << "selection change" << QTime::currentTime() << endl;
}

void modifyColorWidget::setRedo()
{
	isRedo = true;
}

void modifyColorWidget::setUndo()
{
	isUndo = true;
}

void modifyColorWidget::cursorTextEditChanged()
{
	if (connectedTextEdit == nullptr)
		return;

	preCursor = curCursor;

	curCursor.TextCursorLocal = connectedTextEdit->textCursor().blockNumber();

	qDebug() << "cursor change" << QTime::currentTime() << endl;
}

void modifyColorWidget::debugBit()
{
	QString a;
	char t[40];
	
	for (int i = 0; i < docBit.length(); i++)
	{
		sprintf_s(t, "%2i ", i+1);
		a += t;
	}
	qDebug() << a << endl;
	a.clear();
	for (int i = 0; i < docBit.length(); i++)
	{
		sprintf_s(t, "%2i ", docBit[i]);
		a += t;
	}
	sprintf_s(t, "PreLineCount=%i", preLineCount);
	a += t;
	qDebug() << a << endl;
}

modCommand::modCommand(modifyColorWidget *t)
{
	target = t;
	pre = target->preSelect;
	preCursor = target->preCursor;

	connectedTextEdit = target->connectedTextEdit;
	newTextLineCount = connectedTextEdit->document()->lineCount();
	preTextLineCount = target->preLineCount;
	//TSS = TextSelectedStart
	//TSE = TextSelectedEnd
	//TCL = TextCursorLocal
	//cTE = connectedTextEdit->textCursor();
	//dTE = connectedTextEdit->document();

	//int currentTSS = cTE.selectionStart();
	//int currentTSE = cTE.selectionEnd();
	currentTextCursorLocalLineNum = connectedTextEdit->textCursor().blockNumber();

	//
	if (pre.TextSelectedStart == pre.TextSelectedEnd)
	{
		newEndPos2ModColor = target->document()->findBlockByNumber(currentTextCursorLocalLineNum).position() + target->lineStr.length();
		startPos2ModColor = target->document()->findBlockByNumber(preCursor.TextCursorLocal).position();

		//新行数少一行的情况
		if (newTextLineCount == preTextLineCount - 1)
		{
			preColor.push_back(target->docBit[currentTextCursorLocalLineNum]);
			preColor.push_back(target->docBit[preCursor.TextCursorLocal]);
		}
		else
		{
			if(preCursor.TextCursorLocal != -1)
				preColor.push_back(target->docBit[preCursor.TextCursorLocal]);
		}
	}
	else
	{
		newEndPos2ModColor = target->document()->findBlockByNumber(currentTextCursorLocalLineNum).position() + target->lineStr.length();
		startPos2ModColor = target->document()->findBlockByNumber(pre.LineNumTextSelectedStart).position();

		for (int i = pre.LineNumTextSelectedStart; i <= pre.LineNumTextSelectedEnd; i++)
		{
			preColor.push_back(target->docBit[i]);
		}
	}

	//cur = target->curSelect;
}

void modCommand::redo()
{
	//修改前无框选
	//if (pre.TextSelectedStart == pre.TextSelectedEnd)
	//{
	//	//行数无变化
	//	if (preTextLineCount == newTextLineCount)
	//	{
	//		if (target->docBit[currentTextCursorLocalLineNum] == modStatus::modified)
	//			return;
	//		target->docBit[currentTextCursorLocalLineNum] = modStatus::modified;

	//		QTextCursor c = target->textCursor();
	//		c.setPosition(startPos2ModColor, QTextCursor::MoveAnchor);
	//		c.setPosition(newEndPos2ModColor, QTextCursor::KeepAnchor);
	//		target->setTextCursor(c);
	//		target->setTextBackgroundColor(target->docBit2Color[modStatus::modified]);
	//	}
	//	//行数增多一行，或增多数行（复制粘贴而来）
	//	else if (newTextLineCount > preTextLineCount)
	//	{
	//		int addLineNum = newTextLineCount - preTextLineCount;

	//		target->docBit[preCursor.TextCursorLocal] = modStatus::modified;
	//		QTextCursor c = target->textCursor();
	//		//增加新的颜色行
	//		c.setPosition(startPos2ModColor + target->lineStr.length(), QTextCursor::MoveAnchor);
	//		for (int i = preCursor.TextCursorLocal + 1; i <= preCursor.TextCursorLocal + addLineNum; i++)
	//		{
	//			target->docBit.insert(i, modStatus::modified);
	//			c.insertText(target->lineStr);
	//		}
	//		//target->docBit[currentTextCursorLocalLineNum] = modStatus::modified;

	//		//选择新的颜色行并赋予背景颜色
	//		c.setPosition(startPos2ModColor, QTextCursor::MoveAnchor);
	//		c.setPosition(newEndPos2ModColor, QTextCursor::KeepAnchor);
	//		target->setTextCursor(c);
	//		target->setTextBackgroundColor(target->docBit2Color[modStatus::modified]);

	//		target->preLineCount = newTextLineCount;
	//	}

	//	//行数减少，无框选状态下只能减少一行
	//	else if (newTextLineCount == preTextLineCount - 1)
	//	{
	//		target->preLineCount -= 1;
	//		target->docBit.removeAt(pre.LineNumTextSelectedStart);
	//		target->docBit[currentTextCursorLocalLineNum] = modStatus::modified;
	//		QTextCursor c = target->textCursor();
	//		//删除旧的颜色行
	//		c.setPosition(newEndPos2ModColor, QTextCursor::MoveAnchor);
	//		c.setPosition(newEndPos2ModColor + target->lineStr.length(), QTextCursor::KeepAnchor);
	//		c.removeSelectedText();

	//		//选择新的颜色行并赋予背景颜色
	//		c.setPosition(newEndPos2ModColor - target->lineStr.length(), QTextCursor::MoveAnchor);
	//		c.setPosition(newEndPos2ModColor, QTextCursor::KeepAnchor);
	//		target->setTextCursor(c);
	//		this->target->setTextBackgroundColor(target->docBit2Color[modStatus::modified]);
	//	}
	//	else
	//	{
	//		QMessageBox::warning(NULL, "warning", "在无框选条件下找不到对应的文本修改分支", QMessageBox::Yes, QMessageBox::Yes);
	//	}

	//}
	////修改前有框选
	//else
	//{

	//	//无行数变化
	//	if (newTextLineCount == preTextLineCount)
	//	{
	//		//框选的所有行标修改颜色
	//		for (int i = pre.LineNumTextSelectedStart; i <= pre.LineNumTextSelectedEnd; i++)
	//		{
	//			target->docBit[i] = modStatus::modified;
	//		}
	//		QTextCursor c = target->textCursor();
	//		c.setPosition(startPos2ModColor, QTextCursor::MoveAnchor);
	//		c.setPosition(newEndPos2ModColor, QTextCursor::KeepAnchor);
	//		target->setTextCursor(c);
	//		target->setTextBackgroundColor(target->docBit2Color[modStatus::modified]);
	//	}
	//	//行数变大
	//	else if (newTextLineCount > preTextLineCount)
	//	{
	//		//int isReplaceAllBlock = (preSelect.IsSelectEndPosInHome&&preSelect.IsSelectStartPosInHome) ? 1 : 0;

	//		//之前选择的加上新增的被改变了
	//		int addLineNum = newTextLineCount - preTextLineCount;
	//		for (int i = pre.LineNumTextSelectedStart; i <= pre.LineNumTextSelectedEnd; i++)
	//		{
	//			target->docBit[i] = modStatus::modified;
	//		}
	//		QTextCursor c = target->textCursor();
	//		c.setPosition((pre.LineNumTextSelectedEnd + 1) * target->lineStr.length(), QTextCursor::MoveAnchor);
	//		for (int i = pre.LineNumTextSelectedEnd + 1; i <= pre.LineNumTextSelectedEnd + addLineNum; i++)
	//		{
	//			target->docBit.insert(i, modStatus::modified);
	//			c.insertText(target->lineStr);
	//		}
	//		c.setPosition(startPos2ModColor, QTextCursor::MoveAnchor);
	//		c.setPosition(newEndPos2ModColor, QTextCursor::KeepAnchor);
	//		target->setTextCursor(c);
	//		this->target->setTextBackgroundColor(target->docBit2Color[modStatus::modified]);
	//		target->preLineCount = newTextLineCount;
	//	}
	//	//行数变小
	//	else if (newTextLineCount < preTextLineCount)
	//	{
	//		//删除多余行
	//		//int isReplaceAllBlock = (preSelect.IsSelectEndPosInHome&&preSelect.IsSelectStartPosInHome) ? 1 : 0;
	//		for (int i = currentTextCursorLocalLineNum + 1; i <= target->preSelect.LineNumTextSelectedEnd; i++)
	//		{
	//			target->docBit.removeAt(currentTextCursorLocalLineNum + 1);
	//		}
	//		for (int i = pre.LineNumTextSelectedStart; i <= currentTextCursorLocalLineNum; i++)
	//		{
	//			target->docBit[i] = modStatus::modified;
	//		}

	//		QTextCursor c = target->textCursor();
	//		c.setPosition(newEndPos2ModColor, QTextCursor::MoveAnchor);
	//		c.setPosition((pre.LineNumTextSelectedEnd + 1) * target->lineStr.length(), QTextCursor::KeepAnchor);
	//		c.removeSelectedText();
	//		c.setPosition(startPos2ModColor, QTextCursor::MoveAnchor);
	//		c.setPosition(newEndPos2ModColor, QTextCursor::KeepAnchor);
	//		target->setTextCursor(c);
	//		target->setTextBackgroundColor(target->docBit2Color[modStatus::modified]);
	//		target->preLineCount = newTextLineCount;
	//	}
	//}

	
}

void modCommand::undo()
{
	//无框选
	if (pre.TextSelectedStart == pre.TextSelectedEnd)
	{
		//行数无变化
		if (preTextLineCount == newTextLineCount)
		{
			//if (target->docBit[currentTextCursorLocalLineNum] == preColor.first() == modStatus::modified)
			//	return;

			target->docBit[preCursor.TextCursorLocal] = preColor.first();
			QTextCursor c = target->textCursor();
			c.setPosition(startPos2ModColor, QTextCursor::MoveAnchor);
			c.setPosition(newEndPos2ModColor, QTextCursor::KeepAnchor);
			target->setTextCursor(c);
			target->setTextBackgroundColor(target->docBit2Color[preColor.first()]);
		}
		//新行数较大
		else if (newTextLineCount > preTextLineCount)
		{
			for (int i = pre.LineNumTextSelectedStart + 1; i <= pre.LineNumTextSelectedStart + newTextLineCount - preTextLineCount; i++)
			{
				target->docBit.removeAt(pre.LineNumTextSelectedStart + 1);
			}
			target->docBit[pre.LineNumTextSelectedStart] = preColor.first();

			QTextCursor c = target->textCursor();
			c.setPosition(startPos2ModColor + target->lineStr.length(), QTextCursor::MoveAnchor);
			c.setPosition(newEndPos2ModColor, QTextCursor::KeepAnchor);
			c.removeSelectedText();
			c.setPosition(startPos2ModColor, QTextCursor::MoveAnchor);
			c.setPosition(startPos2ModColor + target->lineStr.length(), QTextCursor::KeepAnchor);
			target->setTextCursor(c);
			target->setTextBackgroundColor(target->docBit2Color[preColor.first()]);
			target->preLineCount = preTextLineCount;
		}
		//新行数小一行
		else if (newTextLineCount == preTextLineCount - 1)
		{
			target->docBit[currentTextCursorLocalLineNum] = preColor[0];
			target->docBit.insert(currentTextCursorLocalLineNum + 1, preColor[1]);

			QTextCursor c = target->textCursor();
			c.setPosition(newEndPos2ModColor - target->lineStr.length(), QTextCursor::MoveAnchor);
			c.setPosition(newEndPos2ModColor, QTextCursor::KeepAnchor);
			target->setTextCursor(c);
			target->setTextBackgroundColor(target->docBit2Color[preColor[0]]);
			c = target->textCursor();
			c.setPosition(newEndPos2ModColor, QTextCursor::MoveAnchor);
			c.setPosition(newEndPos2ModColor + target->lineStr.length(), QTextCursor::KeepAnchor);
			target->setTextCursor(c);
			target->setTextBackgroundColor(target->docBit2Color[preColor[1]]);
			target->preLineCount += 1;

		}
		else
		{
			QMessageBox::warning(NULL, "warning", "undo在无框选条件下找不到对应的文本修改分支", QMessageBox::Yes, QMessageBox::Yes);
		}
	}
	//有框选
	else
	{

	}
}

