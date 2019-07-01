/********************************************************************************
** Form generated from reading UI file 'Widget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QComboBox *comboBox;
    QComboBox *comboBox_3;
    QTextEdit *textEdit;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QCheckBox *checkBox;
    QCheckBox *checkBox_4;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_10;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox_5;
    QCheckBox *checkBox_6;
    QCheckBox *checkBox_7;
    QCheckBox *checkBox_8;
    QCheckBox *checkBox_9;
    QCheckBox *checkBox_11;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QStringLiteral("Form"));
        Form->resize(367, 394);
        label = new QLabel(Form);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 10, 54, 22));
        label_2 = new QLabel(Form);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 50, 54, 22));
        label_3 = new QLabel(Form);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 90, 54, 22));
        comboBox = new QComboBox(Form);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(40, 10, 181, 22));
        comboBox->setEditable(true);
        comboBox_3 = new QComboBox(Form);
        comboBox_3->setObjectName(QStringLiteral("comboBox_3"));
        comboBox_3->setGeometry(QRect(40, 50, 181, 22));
        comboBox_3->setEditable(true);
        textEdit = new QTextEdit(Form);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(40, 90, 311, 51));
        pushButton = new QPushButton(Form);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(280, 10, 75, 22));
        pushButton_2 = new QPushButton(Form);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(280, 50, 75, 22));
        groupBox = new QGroupBox(Form);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 160, 341, 231));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        checkBox = new QCheckBox(groupBox);
        checkBox->setObjectName(QStringLiteral("checkBox"));

        gridLayout->addWidget(checkBox, 0, 0, 1, 1);

        checkBox_4 = new QCheckBox(groupBox);
        checkBox_4->setObjectName(QStringLiteral("checkBox_4"));

        gridLayout->addWidget(checkBox_4, 0, 2, 1, 1);

        checkBox_2 = new QCheckBox(groupBox);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));

        gridLayout->addWidget(checkBox_2, 0, 1, 1, 1);

        checkBox_10 = new QCheckBox(groupBox);
        checkBox_10->setObjectName(QStringLiteral("checkBox_10"));

        gridLayout->addWidget(checkBox_10, 3, 1, 1, 1);

        checkBox_3 = new QCheckBox(groupBox);
        checkBox_3->setObjectName(QStringLiteral("checkBox_3"));

        gridLayout->addWidget(checkBox_3, 1, 0, 1, 1);

        checkBox_5 = new QCheckBox(groupBox);
        checkBox_5->setObjectName(QStringLiteral("checkBox_5"));

        gridLayout->addWidget(checkBox_5, 1, 1, 1, 1);

        checkBox_6 = new QCheckBox(groupBox);
        checkBox_6->setObjectName(QStringLiteral("checkBox_6"));

        gridLayout->addWidget(checkBox_6, 1, 2, 1, 1);

        checkBox_7 = new QCheckBox(groupBox);
        checkBox_7->setObjectName(QStringLiteral("checkBox_7"));

        gridLayout->addWidget(checkBox_7, 2, 0, 1, 1);

        checkBox_8 = new QCheckBox(groupBox);
        checkBox_8->setObjectName(QStringLiteral("checkBox_8"));

        gridLayout->addWidget(checkBox_8, 2, 1, 1, 1);

        checkBox_9 = new QCheckBox(groupBox);
        checkBox_9->setObjectName(QStringLiteral("checkBox_9"));

        gridLayout->addWidget(checkBox_9, 3, 0, 1, 1);

        checkBox_11 = new QCheckBox(groupBox);
        checkBox_11->setObjectName(QStringLiteral("checkBox_11"));

        gridLayout->addWidget(checkBox_11, 2, 2, 1, 1);


        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("Form", "\346\212\200\345\270\210", Q_NULLPTR));
        label_2->setText(QApplication::translate("Form", "\347\255\211\347\272\247", Q_NULLPTR));
        label_3->setText(QApplication::translate("Form", "\345\244\207\346\263\250", Q_NULLPTR));
        pushButton->setText(QApplication::translate("Form", "\347\241\256\350\256\244", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("Form", "\345\217\226\346\266\210", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("Form", "\345\216\237\345\233\240", Q_NULLPTR));
        checkBox->setText(QApplication::translate("Form", "\346\221\204\345\275\261\344\275\223\344\275\215", Q_NULLPTR));
        checkBox_4->setText(QApplication::translate("Form", "\347\211\207\345\206\205\344\274\252\345\275\261", Q_NULLPTR));
        checkBox_2->setText(QApplication::translate("Form", "\347\211\271\346\256\212\344\275\223\344\275\215", Q_NULLPTR));
        checkBox_10->setText(QApplication::translate("Form", "\346\202\243\350\200\205\344\270\215\350\203\275\351\205\215\345\220\210", Q_NULLPTR));
        checkBox_3->setText(QApplication::translate("Form", "\346\212\225\347\205\247\350\247\206\351\207\216", Q_NULLPTR));
        checkBox_5->setText(QApplication::translate("Form", "\345\233\276\345\203\217\346\240\207\350\257\206", Q_NULLPTR));
        checkBox_6->setText(QApplication::translate("Form", "\346\233\235\345\205\211\345\217\202\346\225\260", Q_NULLPTR));
        checkBox_7->setText(QApplication::translate("Form", "\345\233\276\345\203\217\345\261\202\346\254\241", Q_NULLPTR));
        checkBox_8->setText(QApplication::translate("Form", "\345\233\276\345\203\217\345\257\271\346\257\224", Q_NULLPTR));
        checkBox_9->setText(QApplication::translate("Form", "\346\221\204\345\275\261\351\203\250\344\275\215\351\224\231\350\257\257", Q_NULLPTR));
        checkBox_11->setText(QApplication::translate("Form", "\350\256\276\345\244\207\345\216\237\345\233\240", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
