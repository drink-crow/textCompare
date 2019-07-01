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
	
	//���ñ���
	void setTitleText(QString &title) { ui.topTitle->setText(title); }

	//�۵�����Ӧ�����õĺ���
	void setTaborNot(bool isTab);

	//���ñ�������С����󻯵Ȱ�ť�ڲ�ͬ״̬ʱ�Ĳ�ͬ����
	void setTitleBarBtn();

public slots:
	//���Ͷ�Ӧ�Ĺرգ���С��������źŵ����ؼ�
	void emitCloseToParent();
	void emitMinToParent();
	void emitMaxToParent();

signals:
	void closeRequest(QWidget* parent);
};

