#pragma once
#include <qtextbrowser.h>

class customLineBrowser :
	public QTextBrowser
{
public:
	customLineBrowser(QWidget *parent = Q_NULLPTR);
	~customLineBrowser();

	//设置显示的行号
	void setLineNum(int Num);
private:
	QString doc;
	int lineCount;

};

