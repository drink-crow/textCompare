#pragma once
#include <qwidget.h>
#include "ui_customTitle.h"
class customTitleBar :
	public QWidget
{
	Q_OBJECT

private:
	Ui::Form ui;

public:
	customTitleBar(QWidget *parent = Q_NULLPTR);
	~customTitleBar();
	
	//设置标题
	void setTitleText(QString &title) { ui.topTitle->setText(title); }

	//折叠与否对应的设置的函数
	void setTaborNot(bool isTab);

	//设置标题栏最小化最大化等按钮在不同状态时的不同表现
	void setTitleBarBtn();

public slots:
	//发送对应的关闭，最小化，最大化信号到父控件
	void emitCloseToParent();
	void emitMinToParent();
	void emitMaxToParent();

signals:
	void closeRequest(QWidget* parent);
};

