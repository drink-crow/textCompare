#include "stdafx.h"
#include "textCompare.h"

textCompare::textCompare(QWidget *parent)
	: QMainWindow(parent)
{
	//实现多国语言翻译
	QTranslator qTrans;
	QLocale locale;
	//根据系统的语言自动切换语言
	switch (locale.language())
	{
	case QLocale::Chinese:
		//读取qrc里的翻译文件
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

	//打开文件后隐藏预设的主窗口
	ui.centralWidget->hide();

	//创建并保存新的文本编辑器
	weiDockWidget* newEditor;
	for (int i = 0; i < fileNames.size(); i++)
	{
		newEditor = new weiDockWidget(this, QUuid::createUuid());
		addDockWidget(Qt::TopDockWidgetArea, newEditor);
		//连接信号与槽
		//当一个编辑框关闭后，重新检查和排布所有编辑框的折叠
		connect(newEditor, SIGNAL(editClose(QWidget *)), this, SLOT(editCloseNotify(QWidget *)));
		connect(newEditor->getNewTitle(), SIGNAL(closeRequest(QWidget *)), this, SLOT(editCloseNotify(QWidget *)));
		connect(newEditor, SIGNAL(showMassage(QString)), this, SLOT(showMassageinStatuBar(QString)));
		connect(newEditor, SIGNAL(checktabified()), this, SLOT(checkEditTabified()));
		connect(newEditor->getTextEdit(), SIGNAL(openFilesSingal(QStringList&)), this, SLOT(textCompareOpenFile(QStringList&)));
		vecDockWidget.push_back(newEditor);

		newEditor->openFile(fileNames[i]);
	}

	//调整边框
	checkEditTabified();
}

//供调用的编辑窗口关闭通知
void textCompare::editCloseNotify(QWidget *sender)
{
	//使用lambda语句删除uid匹配的元素
	//vecDockWidget.remove_if([uid](weiDockWidget *&T) -> bool { return uid == T->getUid(); });
	sender->close();
	checkEditTabified();
	vecDockWidget.remove((weiDockWidget *)sender);
	//容器为空后恢复隐藏的预设主窗口
	if (vecDockWidget.empty())
	{
		ui.centralWidget->show();
	}
}

//打开文件选择框以打开文件
void textCompare::chooseFiletoOpen(void)
{
	//选择打开文件
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

//检查所有的编辑窗口的Tab折叠情况，并作出对应的修改
void textCompare::checkEditTabified()
{
	//应该检查所有的窗口
	QList<QDockWidget *> tablist;
	for (auto &a : vecDockWidget)
	{
		tablist.clear();
		tablist = this->tabifiedDockWidgets(a);
		if (tablist.size() == 0)
		{
			//没有折叠
			a->setTitleTaborNot(false);
		}
		else
		{
			//折叠了
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
				//折叠的窗口把其中一个拖成浮动的状态，剩下那个任然算折叠状态，所以要检查所有的折叠窗口是不是都是浮动的状态
				//或者是关闭中的窗口
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
