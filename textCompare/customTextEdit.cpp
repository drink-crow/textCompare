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
