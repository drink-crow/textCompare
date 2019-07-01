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
	//��д2
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

	//���ڶԿ�ѡ�����������ı�ʱ�����ȴ���ѡ�����ݸı��źţ��ٴ����ı��ı��źţ�����Ҫ����һ�εĿ�ѡ��Ϣ��������
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

		//��������һ�е����
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
	//�޸�ǰ�޿�ѡ
	//if (pre.TextSelectedStart == pre.TextSelectedEnd)
	//{
	//	//�����ޱ仯
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
	//	//��������һ�У����������У�����ճ��������
	//	else if (newTextLineCount > preTextLineCount)
	//	{
	//		int addLineNum = newTextLineCount - preTextLineCount;

	//		target->docBit[preCursor.TextCursorLocal] = modStatus::modified;
	//		QTextCursor c = target->textCursor();
	//		//�����µ���ɫ��
	//		c.setPosition(startPos2ModColor + target->lineStr.length(), QTextCursor::MoveAnchor);
	//		for (int i = preCursor.TextCursorLocal + 1; i <= preCursor.TextCursorLocal + addLineNum; i++)
	//		{
	//			target->docBit.insert(i, modStatus::modified);
	//			c.insertText(target->lineStr);
	//		}
	//		//target->docBit[currentTextCursorLocalLineNum] = modStatus::modified;

	//		//ѡ���µ���ɫ�в����豳����ɫ
	//		c.setPosition(startPos2ModColor, QTextCursor::MoveAnchor);
	//		c.setPosition(newEndPos2ModColor, QTextCursor::KeepAnchor);
	//		target->setTextCursor(c);
	//		target->setTextBackgroundColor(target->docBit2Color[modStatus::modified]);

	//		target->preLineCount = newTextLineCount;
	//	}

	//	//�������٣��޿�ѡ״̬��ֻ�ܼ���һ��
	//	else if (newTextLineCount == preTextLineCount - 1)
	//	{
	//		target->preLineCount -= 1;
	//		target->docBit.removeAt(pre.LineNumTextSelectedStart);
	//		target->docBit[currentTextCursorLocalLineNum] = modStatus::modified;
	//		QTextCursor c = target->textCursor();
	//		//ɾ���ɵ���ɫ��
	//		c.setPosition(newEndPos2ModColor, QTextCursor::MoveAnchor);
	//		c.setPosition(newEndPos2ModColor + target->lineStr.length(), QTextCursor::KeepAnchor);
	//		c.removeSelectedText();

	//		//ѡ���µ���ɫ�в����豳����ɫ
	//		c.setPosition(newEndPos2ModColor - target->lineStr.length(), QTextCursor::MoveAnchor);
	//		c.setPosition(newEndPos2ModColor, QTextCursor::KeepAnchor);
	//		target->setTextCursor(c);
	//		this->target->setTextBackgroundColor(target->docBit2Color[modStatus::modified]);
	//	}
	//	else
	//	{
	//		QMessageBox::warning(NULL, "warning", "���޿�ѡ�������Ҳ�����Ӧ���ı��޸ķ�֧", QMessageBox::Yes, QMessageBox::Yes);
	//	}

	//}
	////�޸�ǰ�п�ѡ
	//else
	//{

	//	//�������仯
	//	if (newTextLineCount == preTextLineCount)
	//	{
	//		//��ѡ�������б��޸���ɫ
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
	//	//�������
	//	else if (newTextLineCount > preTextLineCount)
	//	{
	//		//int isReplaceAllBlock = (preSelect.IsSelectEndPosInHome&&preSelect.IsSelectStartPosInHome) ? 1 : 0;

	//		//֮ǰѡ��ļ��������ı��ı���
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
	//	//������С
	//	else if (newTextLineCount < preTextLineCount)
	//	{
	//		//ɾ��������
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
	//�޿�ѡ
	if (pre.TextSelectedStart == pre.TextSelectedEnd)
	{
		//�����ޱ仯
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
		//�������ϴ�
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
		//������Сһ��
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
			QMessageBox::warning(NULL, "warning", "undo���޿�ѡ�������Ҳ�����Ӧ���ı��޸ķ�֧", QMessageBox::Yes, QMessageBox::Yes);
		}
	}
	//�п�ѡ
	else
	{

	}
}

