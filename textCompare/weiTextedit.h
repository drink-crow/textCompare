#pragma once

#include <QtWidgets/QMainWindow>
#include <QTranslator>
#include "ui_weiTextedit.h"

class weiTextedit :public QWidget 
{
	Q_OBJECT

	friend class textCompare;

public:
	weiTextedit(QWidget *parent = Q_NULLPTR);

	//设置自动换行模式
	void setWordWrapMode(QTextOption::WrapMode policy);
	//添加文本
	void setPlainText(QString &str);
	//打开文本等
	bool openFiletoEdit(QString file);
	//
	customTextEdit* getTextEdit() const { return ui.textEdit; }

private:
	Ui::mainWidget ui;

	//lineBrowser的垂直滑动条
	QScrollBar *scLine;
	//textEdit的垂直滑动条
	QScrollBar *scText;
	//modifyColor的垂直滑动条
	QScrollBar *scColor;

	QString text;

public slots:
	void contentChanged(int position, int charsRemoved, int charsAdded);
	void handleScrollBarMove(int dx, int dy);

	void cursorTextEditChanged();
	void selectionTextEditChanged();

	void textUndo();
	void textRedo();

	//根据文本改变信号的参数从目标文本中取出对应的字符
	inline QString getText(QString *text, int position, int charsRemoved, int charsAdded)
		{return 	text->mid(position, charsAdded);}
};