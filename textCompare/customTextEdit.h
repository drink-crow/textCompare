#pragma once
#include <qtextedit.h>
class customTextEdit :
	public QTextEdit
{
	Q_OBJECT
public:
	customTextEdit(QWidget *parent = Q_NULLPTR);
	~customTextEdit();

	void customRedo();
	void customUndo();
	
protected:
	//void wheelEvent(QWheelEvent *e);
	//void mousePressEvent(QMouseEvent *e);
	void scrollContentsBy(int dx, int dy);
	void keyPressEvent(QKeyEvent *e);

signals:
	void scrollBarMove(int dx, int dy);
	void redoSingal();
	void undoSingal();
};

