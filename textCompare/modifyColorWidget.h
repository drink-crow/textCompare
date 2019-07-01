#pragma once
#include <qtextedit.h>
#include <QUndoCommand>

enum modStatus
{
	//�ֱ�Ϊԭ�����޸ģ��ѱ���
	native,
	modified,
	saved
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

class modifyColorWidget :
	public QTextEdit
{
	friend class modCommand;

public:
	modifyColorWidget(QWidget *parent = Q_NULLPTR);
	~modifyColorWidget();

	//���ù����ı༭����
	void setConnectedTextEdit(QTextEdit* connected);
	//�������ĵ����ݸı�
	void contentChange(int position, int charsRemoved, int charsAdded);

	void cursorTextEditChanged();
	void selectionTextEditChanged();

	//���ܵ��ı�redo��undo
	void setRedo();
	void setUndo();

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

	//redo undo ���
	bool isRedo;
	bool isUndo;
	//�򿪵��ļ�
	bool isFileOpening;

	QUndoStack* undoStack;
	QUndoView* undoView;
	QAction* undoAction;
	QAction* redoAction;
};

class modCommand :public QUndoCommand
{
public:
	modCommand(modifyColorWidget*);

	void redo() override;
	void undo() override;

private:
	modifyColorWidget* target;

	//selectionInfo pre;
	//cursorInfo preCursor;
	//selectionInfo cur;
	int preTextLineCount;
	int newTextLineCount;

	QVector<int> preColor;

	QTextEdit *connectedTextEdit;
	//TSS = TextSelectedStart
	//TSE = TextSelectedEnd
	//TCL = TextCursorLocal
	//QTextCursor cTE;
	//QTextDocument *dTE;
	//int currentTSS = cTE.selectionStart();
	//int currentTSE = cTE.selectionEnd();
	int currentTextCursorLocalLineNum;
	int newEndPos2ModColor;
	int startPos2ModColor;

	int positionLineNumber;
	int removedLineCount;
	int addLineCount;
};

