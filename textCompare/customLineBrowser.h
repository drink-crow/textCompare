#pragma once
#include <qtextbrowser.h>

class customLineBrowser :
	public QTextBrowser
{
public:
	customLineBrowser(QWidget *parent = Q_NULLPTR);
	~customLineBrowser();

	//������ʾ���к�
	void setLineNum(int Num);
private:
	QString doc;
	int lineCount;

};

