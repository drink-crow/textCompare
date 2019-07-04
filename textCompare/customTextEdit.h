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
	inline bool getIsSelectMove() const { return isSelectMove; }
	inline int getSelectStartLineNum() const { return selectStartLineNum; }
	inline int getSelectEndLineNum() const { return selectEndLineNum; }
	inline bool getIsSelectEnd() const { return isSelectEnter; }
	inline void doneSelectMove() { isSelectMove = false; }

protected:
	//void wheelEvent(QWheelEvent *e);
	//void mousePressEvent(QMouseEvent *e);
	virtual void scrollContentsBy(int dx, int dy);
	virtual void keyPressEvent(QKeyEvent *e);
	virtual void dragMoveEvent(QDragMoveEvent *event);
	virtual void dragLeaveEvent(QDragLeaveEvent *event);
	//virtual void dragEnterEvent(QDragEnterEvent *event);
	virtual void dropEvent(QDropEvent *e);

private:
	//框选内容后移动标记
	bool isSelectMove;
	//框选开始的行号
	int selectStartLineNum;
	//框选结束的行号
	int selectEndLineNum;
	//框选末尾是否包含/n
	bool isSelectEnter;

signals:
	void scrollBarMove(int dx, int dy);
	void redoSingal();
	void undoSingal();
	void openFilesSingal(QStringList& filelist);
};

