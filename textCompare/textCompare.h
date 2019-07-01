#pragma once

#include <QtWidgets/QMainWindow>
#include <QTranslator>
#include "ui_textCompare.h"

#include "weiTextedit.h"
#include "weiDockWidget.h"

#include <vector>
using namespace std;

class textCompare : public QMainWindow
{
	Q_OBJECT

public:
	textCompare(QWidget *parent = Q_NULLPTR);
	//���ݰ���·�������ִ��ļ�
	void textCompareOpenFile(QStringList &fileNames);

//�źŲ�
public slots:
	//�����õı༭���ڹر�֪ͨ
//	void editCloseNotify(QUuid uid);
	void editCloseNotify(QWidget *sender);
	//ͨ���Ի�����ļ�
	void chooseFiletoOpen(void);
	//״̬����ʾ��Ϣ
	void showMassageinStatuBar(QString massge);
	//���DockWidget��tab״̬��������Ӧ�Ķ���
	void checkEditTabified();

private:
	Ui::textCompareClass ui;
	
	//�����Ѿ��򿪵��ļ�
	QStringList existFiles;
	//���е��ı���ʾ�ؼ�������
	list<weiDockWidget *> vecDockWidget;

protected:
	//��ҷ�ļ��������Դ�
	void dragEnterEvent(QDragEnterEvent *event);
	void dropEvent(QDropEvent *event);
};
