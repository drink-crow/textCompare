#include "stdafx.h"
#include "textCompare.h"

textCompare::textCompare(QWidget *parent)
	: QMainWindow(parent)
{
	//ʵ�ֶ�����Է���
	QTranslator qTrans;
	QLocale locale;
	//����ϵͳ�������Զ��л�����
	switch (locale.language())
	{
	case QLocale::Chinese:
		//��ȡqrc��ķ����ļ�
		qTrans.load(":/textcompare_zh.qm");
		qApp->installTranslator(&qTrans);
		break;
	default:
		break;
	}

	existFiles.empty();
	this->setTabPosition(Qt::DockWidgetArea_Mask, QTabWidget::North);
	this->setDocumentMode(true);

	ui.setupUi(this);
	ui.centralWidget->setAcceptDrops(false);
	setAcceptDrops(true);
}


void textCompare::textCompareOpenFile(QStringList &fileNames)
{
	if (fileNames.size() == 0)
	{
		ui.statusBar->showMessage("No files choosen");
		return;
	}

	//���ļ�������Ԥ���������
	ui.centralWidget->hide();

	//�����������µ��ı��༭��
	weiDockWidget* newEditor;
	for (int i = 0; i < fileNames.size(); i++)
	{
		newEditor = new weiDockWidget(this, QUuid::createUuid());
		addDockWidget(Qt::TopDockWidgetArea, newEditor);
		//�����ź����
		//��һ���༭��رպ����¼����Ų����б༭����۵�
		connect(newEditor, SIGNAL(editClose(QWidget *)), this, SLOT(editCloseNotify(QWidget *)));
		connect(newEditor->getNewTitle(), SIGNAL(closeRequest(QWidget *)), this, SLOT(editCloseNotify(QWidget *)));
		connect(newEditor, SIGNAL(showMassage(QString)), this, SLOT(showMassageinStatuBar(QString)));
		connect(newEditor, SIGNAL(checktabified()), this, SLOT(checkEditTabified()));
		connect(newEditor->getTextEdit(), SIGNAL(openFilesSingal(QStringList&)), this, SLOT(textCompareOpenFile(QStringList&)));
		vecDockWidget.push_back(newEditor);

		newEditor->openFile(fileNames[i]);
	}

	//�����߿�
	checkEditTabified();
}

//�����õı༭���ڹر�֪ͨ
void textCompare::editCloseNotify(QWidget *sender)
{
	//ʹ��lambda���ɾ��uidƥ���Ԫ��
	//vecDockWidget.remove_if([uid](weiDockWidget *&T) -> bool { return uid == T->getUid(); });
	sender->close();
	checkEditTabified();
	vecDockWidget.remove((weiDockWidget *)sender);
	//����Ϊ�պ�ָ����ص�Ԥ��������
	if (vecDockWidget.empty())
	{
		ui.centralWidget->show();
	}
}

//���ļ�ѡ����Դ��ļ�
void textCompare::chooseFiletoOpen(void)
{
	//ѡ����ļ�
	QStringList fileNames;
	fileNames = QFileDialog::getOpenFileNames(this, tr("choose files to open"), "");
	if (fileNames.size() == 0)
	{
		ui.statusBar->showMessage("No files choosen");
		return;
	}
	textCompareOpenFile(fileNames);
}

void textCompare::showMassageinStatuBar(QString massge)
{
	ui.statusBar->showMessage(massge);

}

//������еı༭���ڵ�Tab�۵��������������Ӧ���޸�
void textCompare::checkEditTabified()
{
	//Ӧ�ü�����еĴ���
	QList<QDockWidget *> tablist;
	for (auto &a : vecDockWidget)
	{
		tablist.clear();
		tablist = this->tabifiedDockWidgets(a);
		if (tablist.size() == 0)
		{
			//û���۵�
			a->setTitleTaborNot(false);
		}
		else
		{
			//�۵���
			bool allFolatingOrClosing = true;
			for (auto &taba : tablist)
			{
				if (taba->isFloating() || ((weiDockWidget*)taba)->getIsClosing())
					continue;
				allFolatingOrClosing = false;
				break;
			}
			if (allFolatingOrClosing)
			{
				//�۵��Ĵ��ڰ�����һ���ϳɸ�����״̬��ʣ���Ǹ���Ȼ���۵�״̬������Ҫ������е��۵������ǲ��Ƕ��Ǹ�����״̬
				//�����ǹر��еĴ���
				a->setTitleTaborNot(false);
			}
			else
			{
				a->setTitleTaborNot(true);
			}
		}
		a->update();
	}

}

void textCompare::dragEnterEvent(QDragEnterEvent * event)
{
	if (event->mimeData()->hasFormat("text/uri-list"))
		event->acceptProposedAction();
}

void textCompare::dropEvent(QDropEvent * event)
{
	QList<QUrl> urls = event->mimeData()->urls();
	if (urls.isEmpty())
		return;
	QString fileName = urls.first().toLocalFile();
	QStringList fileNameList;
	for (auto &a : urls)
	{
		fileName = a.toLocalFile();
		if (fileName.isEmpty())
			continue;
		fileNameList.push_back(fileName);
	}
	if (fileNameList.isEmpty())
		return;
	textCompareOpenFile(fileNameList);

}
