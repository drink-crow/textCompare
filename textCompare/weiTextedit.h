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

	//�����Զ�����ģʽ
	void setWordWrapMode(QTextOption::WrapMode policy);
	//����ı�
	void setPlainText(QString &str);
	//���ı���
	bool openFiletoEdit(QString file);
	//
	customTextEdit* getTextEdit() const { return ui.textEdit; }

private:
	Ui::mainWidget ui;

	//lineBrowser�Ĵ�ֱ������
	QScrollBar *scLine;
	//textEdit�Ĵ�ֱ������
	QScrollBar *scText;
	//modifyColor�Ĵ�ֱ������
	QScrollBar *scColor;

	QString text;

public slots:
	void contentChanged(int position, int charsRemoved, int charsAdded);
	void handleScrollBarMove(int dx, int dy);

	void cursorTextEditChanged();
	void selectionTextEditChanged();

	void textUndo();
	void textRedo();

	//�����ı��ı��źŵĲ�����Ŀ���ı���ȡ����Ӧ���ַ�
	inline QString getText(QString *text, int position, int charsRemoved, int charsAdded)
		{return 	text->mid(position, charsAdded);}
};