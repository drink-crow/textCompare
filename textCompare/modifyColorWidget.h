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

enum changeType
{
	//��ͨ�޸�ģʽ
	defualt,
	//��ѡ�϶��޸�ģʽ
	move,
	//���ļ�
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

	//���ù����ı༭����
	void setConnectedTextEdit(QTextEdit* connected);
	//�ĵ����ݸı�(��������)
	void contentChange(changeType type, vector<int> position, vector<int> charsRemoved, vector<int> charsAdded, int effectCharsCount);

	//void cursorTextEditChanged();
	//void selectionTextEditChanged();

	//���ܵ��ı�redo��undo
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

	//redo undo ���
	bool isRedo;
	bool isUndo;
	//�򿪵��ļ�
	bool isFileOpening;

	QUndoStack* undoStack;
	QUndoView* undoView;
	QAction* undoAction;
	QAction* redoAction;

	//������¼ÿ�ζ�����������ַ���
	vector<int> assistUndoStack;
};

class modCommand :public QUndoCommand
{
public:
	modCommand(modifyColorWidget*, changeType, vector<int>, vector<int>, vector<int>, int);

	void redo() override;
	void undo() override;

private:
	//�޸ĵĶ���
	modifyColorWidget* target;
	//contentChange������ֵ
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

