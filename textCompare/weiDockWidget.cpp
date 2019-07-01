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
	
	//ȡ���Զ�����
	textEdit->setWordWrapMode(QTextOption::NoWrap);
	

	//����layout����
	vLayout->setContentsMargins(0, 4, 0, 0);

	//vLayout->setSpacing(0);
	vLayout->addWidget(textEdit);
	dockWidgetContent->setLayout(vLayout);
	this->setWidget(dockWidgetContent);
	this->setTitleBarWidget(newTitle);
	
	//��������
	//��ͣ�����κεط�
	this->setAllowedAreas(Qt::AllDockWidgetAreas);
	//�ɹرգ��ƶ�������
	this->setFeatures(DockWidgetClosable | DockWidgetMovable | DockWidgetFloatable);
	//�����ź����
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
	//���ñ���Ϊ�ļ���
	QString fileName;
	fileName = Name.right(Name.length() - Name.lastIndexOf('/') - 1);
	//�����Զ������������
	setTitleText(fileName);
	//�����۵�ҳ����
	this->setWindowTitle(fileName);

	//��ȡ�ļ�
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
	//���Թر�ʱ�䣬֪ͨ������ȥ�ر��Լ�
	//emit editClose(this);
	isClosing = true;
	event->accept();
}

void weiDockWidget::notifyTopLevelChange()
{
	emit checktabified();
}


