#pragma once
#include <qtextedit.h>
#include <QUndoCommand>

enum modStatus
{
	//分别为原生，修改，已保存
	native,
	modified,
	saved
};

enum changeType
{
	//普通修改模式
	defualt,
	//框选拖动修改模式
	move,
	//打开文件
	openFile
};

struct selectionInfo
{
	int TextSelectedStart=-1;
	int TextSelectedEnd = -1;
	int LineNumTextSelectedStart = -1;
	int LineNumTextSelectedEnd = -1;
	int IsSelectStartPosInHome = -1;
	int IsSelectEndPosInHome = -1;
};

struct cursorInfo
{
	int TextCursorLocal = -1;
	int LineCount = -1;
};

using namespace std;
class modifyColorWidget :
	public QTextEdit
{
	friend class modCommand;

public:


	modifyColorWidget(QWidget *parent = Q_NULLPTR);
	~modifyColorWidget();

	//设置关联的编辑窗口
	void setConnectedTextEdit(QTextEdit* connected);
	//文档内容改变(被动调用)
	void contentChange(changeType type, vector<int> position, vector<int> charsRemoved, vector<int> charsAdded, int effectCharsCount);

	//void cursorTextEditChanged();
	//void selectionTextEditChanged();

	//接受到文本redo和undo
	void setRedo();
	void setUndo();
	//size_t getassistUndoStackSize() const { return assistUndoStack.size(); }

	void setFileOpening() { isFileOpening = true; }

	void debugBit();

private:
	QTextEdit* connectedTextEdit;

	selectionInfo preSelect;
	selectionInfo curSelect;

	cursorInfo preCursor;
	cursorInfo curCursor;

	QString doc;
	QList<int> docBit;
	int lineCount;
	int preLineCount;

	QString lineStr;

	QMap<int,QColor> docBit2Color;
	QVector<QTextCharFormat> docBit2Format;

	//redo undo 标记
	bool isRedo;
	bool isUndo;
	//打开的文件
	bool isFileOpening;

	QUndoStack* undoStack;
	QUndoView* undoView;
	QAction* undoAction;
	QAction* redoAction;

	//用来记录每次动做后的增减字符数
	vector<int> assistUndoStack;
};

class modCommand :public QUndoCommand
{
public:
	modCommand(modifyColorWidget*, changeType, vector<int>, vector<int>, vector<int>, int);

	void redo() override;
	void undo() override;

private:
	//修改的对象
	modifyColorWidget* target;
	//contentChange传来的值
	vector<int> position;
	vector<int> charsRemoved;
	vector<int> charsAdded;
	changeType type;
	int effectCharsCount;

	//selectionInfo pre;
	//cursorInfo preCursor;
	//selectionInfo cur;
	//int preTextLineCount;
	//int newTextLineCount;

	vector<int> preColor;

	QTextEdit *connectedTextEdit;
	//TSS = TextSelectedStart
	//TSE = TextSelectedEnd
	//TCL = TextCursorLocal
	//QTextCursor cTE;
	//QTextDocument *dTE;
	//int currentTSS = cTE.selectionStart();
	//int currentTSE = cTE.selectionEnd();
	//int currentTextCursorLocalLineNum;
	//int newEndPos2ModColor;
	//int startPos2ModColor;

	//int positionLineNumber;
	//int removedLineCount;
	//int addLineCount;
};

