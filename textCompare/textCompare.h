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
	//根据包含路径的名字打开文件
	void textCompareOpenFile(QStringList &fileNames);

//信号槽
public slots:
	//供调用的编辑窗口关闭通知
//	void editCloseNotify(QUuid uid);
	void editCloseNotify(QWidget *sender);
	//通过对话框打开文件
	void chooseFiletoOpen(void);
	//状态栏显示信息
	void showMassageinStatuBar(QString massge);
	//检查DockWidget的tab状态和做出相应的动作
	void checkEditTabified();

private:
	Ui::textCompareClass ui;
	
	//现有已经打开的文件
	QStringList existFiles;
	//已有的文本显示控件的容器
	list<weiDockWidget *> vecDockWidget;

protected:
	//拖曳文件到窗口以打开
	void dragEnterEvent(QDragEnterEvent *event);
	void dropEvent(QDropEvent *event);
};
