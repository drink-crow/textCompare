#include "stdafx.h"
#include "customTextEdit.h"


customTextEdit::customTextEdit(QWidget *parent)
	: QTextEdit(parent)
{
	isSelectMove = false;
	selectStartLineNum = -1;
	selectEndLineNum = -1;
	isSelectEnter = false;
}


customTextEdit::~customTextEdit()
{
}

void customTextEdit::customRedo()
{
	if (document()->isRedoAvailable())
	{
		emit redoSingal();	
	}
	redo();
}

void customTextEdit::customUndo()
{

	if(document()->isUndoAvailable())
	{
		emit undoSingal();	
	}
	undo();

}

//�����¼���ֻ���������ֹ���
//void customTextEdit::wheelEvent(QWheelEvent * e)
//{
//	e->accept();
//	
//}
//
//void customTextEdit::mousePressEvent(QMouseEvent * e)
//{
//	e->accept();
//}

//�����ƶ��¼���������ֱ��������ˮƽ�Ļ�����
void customTextEdit::scrollContentsBy(int dx, int dy)
{
	//��ҪһЩĬ�ϵĲ���
	QTextEdit::scrollContentsBy(dx, dy);
	emit scrollBarMove(dx, dy);
}

void customTextEdit::keyPressEvent(QKeyEvent * e)
{
	//����redo,undo
	if (e->modifiers() == Qt::ControlModifier) 
	{
		if (e->key() == Qt::Key_Z)
		{
			customUndo();
			return;
		}
		else if (e->key() == Qt::Key_Y)
		{
			customRedo();
			return;
		}
	}
	QTextEdit::keyPressEvent(e);
}

void customTextEdit::dragMoveEvent(QDragMoveEvent * event)
{
	//qDebug() << "inter dragMoveEvent" << endl;
	event->accept();
}

void customTextEdit::dragLeaveEvent(QDragLeaveEvent * event)
{
	qDebug() << "inter dragLeaveEvent" << endl;
	event->accept();
}

//void customTextEdit::dragEnterEvent(QDragEnterEvent * event)
//{
//	//�϶���Դ������
//	//����Ҫ�ж�source�Ƿ�Ϊ�գ��������ǳ��������ʱ��source���ǿ�
//	if (event->source())
//	{
//		if (event->source()->parent() == this)
//		qDebug() << "drag form itself" << endl;
//
//
//	}
//
//
//
//	event->accept();
//}

void customTextEdit::dropEvent(QDropEvent * e)
{
	qDebug() << "drop Event accept" << endl;

	//�϶���Դ������
	if (e->source())
	{
		if (e->source()->parent() == this)
			qDebug() << "drag form itself" << endl;
		e->accept();
		//Ӧ��Ĭ�϶���

		//���б��
		isSelectMove = true;
		QTextCursor c = textCursor();
		QTextDocument *d = document();
		isSelectEnter = c.selection().toPlainText().right(1) == "\n" ? true : false;
		int TextSelectedStart = c.selectionStart();
		int TextSelectedEnd = c.selectionEnd();
		c.setPosition(TextSelectedStart, QTextCursor::MoveAnchor);
		selectStartLineNum = c.blockNumber();
		c.setPosition(TextSelectedEnd, QTextCursor::MoveAnchor);
		selectEndLineNum = c.blockNumber();

		QTextEdit::dropEvent(e);
	}
	//�϶���Դ���ⲿ���ⲿ�ļ�����������
	else
	{
		//����������ļ�
		if (e->mimeData()->hasFormat("text/uri-list"))
		{
			QList<QUrl> urls = e->mimeData()->urls();
			if (urls.isEmpty())
				return;
			QString fileName = urls.first().toLocalFile();
			QStringList fileNameList;
			for (auto &a : urls)
			{
				fileName = a.toLocalFile();
				if (fileName.isEmpty())
					continue;
				fileNameList.push_back(fileName);
			}
			if (fileNameList.isEmpty())
				return;

			e->accept();
			emit openFilesSingal(fileNameList);
		}
		//��������
		else
		{
			e->accept();
			QTextEdit::dropEvent(e);
		}
	}
}
