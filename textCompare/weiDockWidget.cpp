#include "stdafx.h"
#include "weiDockWidget.h"


weiDockWidget::weiDockWidget(QWidget *parent, QUuid getUid)
	: QDockWidget(parent)
{
	isClosing = false;
	uid = getUid;
	emptyTitle = new QWidget;
	defaultTitle = new QWidget;
	newTitle = new customTitleBar(this);

	dockWidgetContent = new QWidget;
	vLayout = new QVBoxLayout;	
	textEdit = new weiTextedit(dockWidgetContent);
	
	//取消自动换行
	textEdit->setWordWrapMode(QTextOption::NoWrap);
	

	//设置layout布局
	vLayout->setContentsMargins(0, 4, 0, 0);

	//vLayout->setSpacing(0);
	vLayout->addWidget(textEdit);
	dockWidgetContent->setLayout(vLayout);
	this->setWidget(dockWidgetContent);
	this->setTitleBarWidget(newTitle);
	
	//设置属性
	//可停靠在任何地方
	this->setAllowedAreas(Qt::AllDockWidgetAreas);
	//可关闭，移动，悬浮
	this->setFeatures(DockWidgetClosable | DockWidgetMovable | DockWidgetFloatable);
	//连接信号与槽
	connect(this, SIGNAL(topLevelChanged(bool)), this, SLOT(notifyTopLevelChange()));
	//connect(this, SIGNAL(visibilityChanged(bool)), this, SLOT(notifyTopLevelChange()));
}


weiDockWidget::~weiDockWidget()
{
	delete textEdit; textEdit = nullptr;
	delete vLayout; vLayout = nullptr;
	delete dockWidgetContent; dockWidgetContent = nullptr;
}

void weiDockWidget::openFile(QString Name)
{
	//设置标题为文件名
	QString fileName;
	fileName = Name.right(Name.length() - Name.lastIndexOf('/') - 1);
	//设置自定义标题栏标题
	setTitleText(fileName);
	//设置折叠页标题
	this->setWindowTitle(fileName);

	//读取文件
	//QFile file(Name);
	//if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
	//{
	//	QMessageBox::critical(NULL, "Open Error", "can not open file " + Name, QMessageBox::Yes, QMessageBox::Yes);
	//	emit editClose(this);
	//}
	//QTextStream in(&file);
	//QString strAll = in.readAll();
	//this->textEdit->setPlainText(strAll);
	if (!this->textEdit->openFiletoEdit(Name))
		emit  editClose(this);
}

void weiDockWidget::closeEvent(QCloseEvent *event)
{
	//忽略关闭时间，通知主窗口去关闭自己
	//emit editClose(this);
	isClosing = true;
	event->accept();
}

void weiDockWidget::notifyTopLevelChange()
{
	emit checktabified();
}


