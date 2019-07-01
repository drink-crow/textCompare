#include "stdafx.h"
#include "customTextEdit.h"


customTextEdit::customTextEdit(QWidget *parent)
	: QTextEdit(parent)
{
}


customTextEdit::~customTextEdit()
{
}

void customTextEdit::customRedo()
{
	emit redoSingal();	
	redo();
}

void customTextEdit::customUndo()
{
	emit undoSingal();	
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
