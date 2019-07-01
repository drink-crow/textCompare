#include "stdafx.h"
#include "customTitleBar.h"


customTitleBar::customTitleBar(QWidget *parent)
	:QWidget(parent)
{
	ui.setupUi(this);

	//设置系统风格的标题栏按钮
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
	QPixmap mini = style()->standardPixmap(QStyle::SP_TitleBarMinButton);
	ui.minButton->setIcon(mini);
	QPixmap max = style()->standardPixmap(QStyle::SP_TitleBarMaxButton);
	ui.maxButton->setIcon(max);
	QPixmap close = style()->standardPixmap(QStyle::SP_TitleBarCloseButton);
	ui.closeButton->setIcon(close);
	
	setTitleBarBtn();
}


customTitleBar::~customTitleBar()
{

}

void customTitleBar::setTaborNot(bool isTab)
{
	if (isTab)
	{
		ui.vTabWidget->hide();
	}
	else
	{
		ui.vTabWidget->show();
	}
	setTitleBarBtn();
}

void customTitleBar::setTitleBarBtn()
{
	if (((QDockWidget*)this->parentWidget())->isFloating())
	{
		ui.minButton->show();
		ui.maxButton->show();
	}
	else
	{
		ui.minButton->hide();
		ui.maxButton->hide();
	}
}

void customTitleBar::emitCloseToParent()
{
	//this->parentWidget()->close();
	//让mainWindow去关闭窗口，以实现关闭窗口后一些操作
	emit closeRequest(parentWidget());
}

void customTitleBar::emitMinToParent()
{
	this->parentWidget()->showMinimized();
}

void customTitleBar::emitMaxToParent()
{
	//切换最大化和普通化窗口图标
	if (this->parentWidget()->isMaximized())
	{
		QPixmap max = style()->standardPixmap(QStyle::SP_TitleBarMaxButton);
		ui.maxButton->setIcon(max);
		this->parentWidget()->showNormal();
	}
	else
	{
		QPixmap nor = style()->standardPixmap(QStyle::SP_TitleBarNormalButton);
		ui.maxButton->setIcon(nor);
		this->parentWidget()->showMaximized();
	}
}
