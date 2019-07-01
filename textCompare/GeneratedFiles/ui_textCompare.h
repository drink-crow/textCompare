/********************************************************************************
** Form generated from reading UI file 'textCompare.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEXTCOMPARE_H
#define UI_TEXTCOMPARE_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_textCompareClass
{
public:
    QAction *actionOpen;
    QAction *actionClose;
    QAction *actionExit;
    QAction *actionOption;
    QAction *actionSave;
    QAction *actionSave_2;
    QAction *actionSave_All;
    QAction *actionUndo;
    QAction *actionRedo;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_4;
    QSpacerItem *verticalSpacer;
    QLabel *labelOpenTip;
    QHBoxLayout *horizontalLayout;
    QPushButton *openFileButton;
    QSpacerItem *verticalSpacer_2;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuHelp;
    QMenu *menuTool;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *textCompareClass)
    {
        if (textCompareClass->objectName().isEmpty())
            textCompareClass->setObjectName(QStringLiteral("textCompareClass"));
        textCompareClass->resize(600, 800);
        actionOpen = new QAction(textCompareClass);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionClose = new QAction(textCompareClass);
        actionClose->setObjectName(QStringLiteral("actionClose"));
        actionExit = new QAction(textCompareClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionOption = new QAction(textCompareClass);
        actionOption->setObjectName(QStringLiteral("actionOption"));
        actionSave = new QAction(textCompareClass);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionSave_2 = new QAction(textCompareClass);
        actionSave_2->setObjectName(QStringLiteral("actionSave_2"));
        actionSave_All = new QAction(textCompareClass);
        actionSave_All->setObjectName(QStringLiteral("actionSave_All"));
        actionUndo = new QAction(textCompareClass);
        actionUndo->setObjectName(QStringLiteral("actionUndo"));
        actionRedo = new QAction(textCompareClass);
        actionRedo->setObjectName(QStringLiteral("actionRedo"));
        centralWidget = new QWidget(textCompareClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setLayoutDirection(Qt::LeftToRight);
        centralWidget->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        verticalLayout_4 = new QVBoxLayout(centralWidget);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer);

        labelOpenTip = new QLabel(centralWidget);
        labelOpenTip->setObjectName(QStringLiteral("labelOpenTip"));
        labelOpenTip->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(labelOpenTip);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        openFileButton = new QPushButton(centralWidget);
        openFileButton->setObjectName(QStringLiteral("openFileButton"));
        openFileButton->setMaximumSize(QSize(100, 50));

        horizontalLayout->addWidget(openFileButton);


        verticalLayout_4->addLayout(horizontalLayout);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_2);

        textCompareClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(textCompareClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 23));
        menuBar->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuFile->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QStringLiteral("menuEdit"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        menuHelp->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        menuTool = new QMenu(menuBar);
        menuTool->setObjectName(QStringLiteral("menuTool"));
        menuTool->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        textCompareClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(textCompareClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mainToolBar->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        textCompareClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(textCompareClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        statusBar->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        textCompareClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuTool->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionClose);
        menuFile->addSeparator();
        menuFile->addAction(actionSave);
        menuFile->addAction(actionSave_2);
        menuFile->addAction(actionSave_All);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuEdit->addAction(actionUndo);
        menuEdit->addAction(actionRedo);
        menuTool->addAction(actionOption);

        retranslateUi(textCompareClass);
        QObject::connect(actionOpen, SIGNAL(triggered()), textCompareClass, SLOT(chooseFiletoOpen()));
        QObject::connect(openFileButton, SIGNAL(clicked()), textCompareClass, SLOT(chooseFiletoOpen()));

        QMetaObject::connectSlotsByName(textCompareClass);
    } // setupUi

    void retranslateUi(QMainWindow *textCompareClass)
    {
        textCompareClass->setWindowTitle(QApplication::translate("textCompareClass", "textCompare", Q_NULLPTR));
        actionOpen->setText(QApplication::translate("textCompareClass", "Open", Q_NULLPTR));
        actionOpen->setShortcut(QApplication::translate("textCompareClass", "Ctrl+O", Q_NULLPTR));
        actionClose->setText(QApplication::translate("textCompareClass", "Close", Q_NULLPTR));
        actionClose->setShortcut(QApplication::translate("textCompareClass", "Ctrl+C", Q_NULLPTR));
        actionExit->setText(QApplication::translate("textCompareClass", "Exit", Q_NULLPTR));
        actionExit->setShortcut(QApplication::translate("textCompareClass", "Ctrl+E", Q_NULLPTR));
        actionOption->setText(QApplication::translate("textCompareClass", "Option", Q_NULLPTR));
        actionSave->setText(QApplication::translate("textCompareClass", "Save", Q_NULLPTR));
        actionSave_2->setText(QApplication::translate("textCompareClass", "Save", Q_NULLPTR));
        actionSave_All->setText(QApplication::translate("textCompareClass", "Save All", Q_NULLPTR));
        actionUndo->setText(QApplication::translate("textCompareClass", "Undo", Q_NULLPTR));
        actionRedo->setText(QApplication::translate("textCompareClass", "Redo", Q_NULLPTR));
        labelOpenTip->setText(QApplication::translate("textCompareClass", "please drap files into window to open", Q_NULLPTR));
        openFileButton->setText(QApplication::translate("textCompareClass", "Open Files", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("textCompareClass", "File", Q_NULLPTR));
        menuEdit->setTitle(QApplication::translate("textCompareClass", "Edit", Q_NULLPTR));
        menuHelp->setTitle(QApplication::translate("textCompareClass", "Help", Q_NULLPTR));
        menuTool->setTitle(QApplication::translate("textCompareClass", "Tool", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class textCompareClass: public Ui_textCompareClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEXTCOMPARE_H
