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

//滚轮事件，只包含鼠标滚轮滚动
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

//滑条移动事件，包含垂直滑动条和水平的滑动条
void customTextEdit::scrollContentsBy(int dx, int dy)
{
	//需要一些默认的操作
	QTextEdit::scrollContentsBy(dx, dy);
	emit scrollBarMove(dx, dy);
}

void customTextEdit::keyPressEvent(QKeyEvent * e)
{
	//拦截redo,undo
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
//	//拖动来源是自身
//	//首先要判断source是否为空，当输入是程序以外的时候source就是空
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

	//拖动来源是自身
	if (e->source())
	{
		if (e->source()->parent() == this)
			qDebug() << "drag form itself" << endl;
		e->accept();
		//应用默认动作

		//进行标记
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
	//拖动来源是外部，外部文件，或者内容
	else
	{
		//被拖入的是文件
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
		//其它内容
		else
		{
			e->accept();
			QTextEdit::dropEvent(e);
		}
	}
}
