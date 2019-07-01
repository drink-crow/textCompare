#include "stdafx.h"
#include "customLineBrowser.h"


customLineBrowser::customLineBrowser(QWidget *parent)
	: QTextBrowser(parent)
{
}


customLineBrowser::~customLineBrowser()
{
}

void customLineBrowser::setLineNum(int Num)
{
	if (doc.isEmpty())
	{
		for (int i = 1; i <= Num; i++)
		{
			doc += QString::number(i) + "\n";
		}
	}
	else if (Num > lineCount)
	{
		for (int i = lineCount + 1; i <= Num; i++)
		{
			doc += QString::number(i) + "\n";
		}
	}
	else if (Num < lineCount)
	{
		QString t;
		for (int i = Num + 1; i <= lineCount; i++)
		{
			t += QString::number(i) + "\n";
		}
		doc.chop(t.length());
	}
	else
	{
		return;
	}

	lineCount = Num;
	this->setPlainText(doc);
	this->selectAll();
	this->setAlignment(Qt::AlignRight);
	this->moveCursor(QTextCursor::Start);
}
