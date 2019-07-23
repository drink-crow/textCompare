/********************************************************************************
** Form generated from reading UI file 'weiTextedit.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WEITEXTEDIT_H
#define UI_WEITEXTEDIT_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>
#include <customlinebrowser.h>
#include <customtextedit.h>
#include <modifycolorwidget.h>

QT_BEGIN_NAMESPACE

class Ui_mainWidget
{
public:
    QHBoxLayout *horizontalLayout;
    customLineBrowser *lineBrowser;
    modifyColorWidget *modifyColor;
    customTextEdit *textEdit;

    void setupUi(QWidget *mainWidget)
    {
        if (mainWidget->objectName().isEmpty())
            mainWidget->setObjectName(QStringLiteral("mainWidget"));
        mainWidget->resize(847, 501);
        mainWidget->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        horizontalLayout = new QHBoxLayout(mainWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        lineBrowser = new customLineBrowser(mainWidget);
        lineBrowser->setObjectName(QStringLiteral("lineBrowser"));
        lineBrowser->setEnabled(false);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineBrowser->sizePolicy().hasHeightForWidth());
        lineBrowser->setSizePolicy(sizePolicy);
        lineBrowser->setMaximumSize(QSize(35, 16777215));
        lineBrowser->setContextMenuPolicy(Qt::DefaultContextMenu);
        lineBrowser->setLayoutDirection(Qt::LeftToRight);
        lineBrowser->setFrameShape(QFrame::NoFrame);
        lineBrowser->setFrameShadow(QFrame::Plain);
        lineBrowser->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        lineBrowser->setAutoFormatting(QTextEdit::AutoAll);
        lineBrowser->setTabChangesFocus(false);
        lineBrowser->setLineWrapMode(QTextEdit::NoWrap);

        horizontalLayout->addWidget(lineBrowser);

        modifyColor = new modifyColorWidget(mainWidget);
        modifyColor->setObjectName(QStringLiteral("modifyColor"));
        modifyColor->setEnabled(false);
        modifyColor->setMaximumSize(QSize(12, 16777215));
        modifyColor->setFrameShape(QFrame::NoFrame);
        modifyColor->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        modifyColor->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        modifyColor->setLineWrapMode(QTextEdit::NoWrap);

        horizontalLayout->addWidget(modifyColor);

        textEdit = new customTextEdit(mainWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));

        horizontalLayout->addWidget(textEdit);


        retranslateUi(mainWidget);

        QMetaObject::connectSlotsByName(mainWidget);
    } // setupUi

    void retranslateUi(QWidget *mainWidget)
    {
        mainWidget->setWindowTitle(QApplication::translate("mainWidget", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class mainWidget: public Ui_mainWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WEITEXTEDIT_H
