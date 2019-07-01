/********************************************************************************
** Form generated from reading UI file 'customTitle.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CUSTOMTITLE_H
#define UI_CUSTOMTITLE_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *vTabWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *topTitle;
    QSpacerItem *horizontalSpacer_2;
    QFrame *line;
    QHBoxLayout *titleLayout;
    QSpacerItem *horizontalSpacer;
    QToolButton *minButton;
    QToolButton *maxButton;
    QToolButton *closeButton;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QStringLiteral("Form"));
        Form->resize(814, 42);
        Form->setMaximumSize(QSize(16777215, 16777215));
        Form->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        verticalLayout = new QVBoxLayout(Form);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        vTabWidget = new QWidget(Form);
        vTabWidget->setObjectName(QStringLiteral("vTabWidget"));
        vTabWidget->setMaximumSize(QSize(16777215, 20));
        verticalLayout_2 = new QVBoxLayout(vTabWidget);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        topTitle = new QLabel(vTabWidget);
        topTitle->setObjectName(QStringLiteral("topTitle"));
        topTitle->setMaximumSize(QSize(16777215, 19));
        topTitle->setFrameShape(QFrame::NoFrame);
        topTitle->setText(QStringLiteral("TextLabel"));

        horizontalLayout->addWidget(topTitle);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout);

        line = new QFrame(vTabWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setMaximumSize(QSize(16777215, 1));
        line->setFrameShadow(QFrame::Raised);
        line->setFrameShape(QFrame::HLine);

        verticalLayout_2->addWidget(line);


        verticalLayout->addWidget(vTabWidget);

        titleLayout = new QHBoxLayout();
        titleLayout->setSpacing(0);
        titleLayout->setObjectName(QStringLiteral("titleLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        titleLayout->addItem(horizontalSpacer);

        minButton = new QToolButton(Form);
        minButton->setObjectName(QStringLiteral("minButton"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(minButton->sizePolicy().hasHeightForWidth());
        minButton->setSizePolicy(sizePolicy);

        titleLayout->addWidget(minButton);

        maxButton = new QToolButton(Form);
        maxButton->setObjectName(QStringLiteral("maxButton"));
        sizePolicy.setHeightForWidth(maxButton->sizePolicy().hasHeightForWidth());
        maxButton->setSizePolicy(sizePolicy);

        titleLayout->addWidget(maxButton);

        closeButton = new QToolButton(Form);
        closeButton->setObjectName(QStringLiteral("closeButton"));
        sizePolicy.setHeightForWidth(closeButton->sizePolicy().hasHeightForWidth());
        closeButton->setSizePolicy(sizePolicy);

        titleLayout->addWidget(closeButton);


        verticalLayout->addLayout(titleLayout);


        retranslateUi(Form);
        QObject::connect(closeButton, SIGNAL(clicked()), Form, SLOT(emitCloseToParent()));
        QObject::connect(maxButton, SIGNAL(clicked()), Form, SLOT(emitMaxToParent()));
        QObject::connect(minButton, SIGNAL(clicked()), Form, SLOT(emitMinToParent()));

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", Q_NULLPTR));
        minButton->setText(QApplication::translate("Form", "...", Q_NULLPTR));
        maxButton->setText(QApplication::translate("Form", "...", Q_NULLPTR));
        closeButton->setText(QApplication::translate("Form", "...", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUSTOMTITLE_H
