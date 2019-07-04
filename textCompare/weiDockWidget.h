#pragma once
#include <QtWidgets/QMainWindow>
#include "customTitleBar.h"
#include "weiTextedit.h"

constexpr int originTopMargin = 2;
constexpr int tabAddTopMargin = 4;

class weiDockWidget : public QDockWidget
{
	Q_OBJECT

	//friend class weiDockWidget;
public:
	explicit weiDockWidget(QWidget *parent = Q_NULLPTR, QUuid getUid = QUuid::createUuid());
	~weiDockWidget();
	//��ʾ�򿪵��ļ�
	void openFile(QString Name);

	void setTitleTaborNot(bool isTab) { newTitle->setTaborNot(isTab); }
	void setTitleText(QString title) { newTitle->setTitleText(title); }
	void setCustomTitle() { this->setTitleBarWidget(newTitle); }
	void setEmptyTitle() { this->setTitleBarWidget(emptyTitle); }
	void setTabMargins() { this->vLayout->setContentsMargins(0, originTopMargin +tabAddTopMargin, 0, 0); }
	void setUntabMargins(){ this->vLayout->setContentsMargins(0, originTopMargin, 0, 0); }
	void addText(QString t) { this->textEdit->setPlainText(t); }
	customTitleBar* getNewTitle() const { return newTitle; }
	customTextEdit* getTextEdit() const { return textEdit->getTextEdit(); }
	inline QUuid getUid(void) { return uid; }
	bool getIsClosing() { return isClosing; }

signals:
//	void editClose(QUuid uid);
	void editClose(QWidget *sender);
	void showMassage(QString massage);
	void checktabified();

public slots:
	void notifyTopLevelChange();

protected:
	void closeEvent(QCloseEvent * event);

private:
	//�ؼ�
	QVBoxLayout *vLayout;
	weiTextedit *textEdit;
	QWidget *dockWidgetContent;

	//�ձ�����
	QWidget *emptyTitle;
	QWidget *defaultTitle;
	customTitleBar *newTitle;

	//GUID
	QUuid uid;

	//�ر�״̬,��Ϊclose����ִ�����ŷ��صģ�������ӹر��еı�־
	bool isClosing;
};

