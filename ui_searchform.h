/********************************************************************************
** Form generated from reading UI file 'searchform.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEARCHFORM_H
#define UI_SEARCHFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SearchWidgetForm
{
public:
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QComboBox *comboBox_Source;
    QComboBox *comboBox_Group;
    QLineEdit *lineEdit;
    QPushButton *pushButton;

    void setupUi(QWidget *SearchWidgetForm)
    {
        if (SearchWidgetForm->objectName().isEmpty())
            SearchWidgetForm->setObjectName(QStringLiteral("SearchWidgetForm"));
        SearchWidgetForm->resize(280, 79);
        SearchWidgetForm->setMinimumSize(QSize(280, 0));
        SearchWidgetForm->setMaximumSize(QSize(280, 16777215));
        SearchWidgetForm->setStyleSheet(QStringLiteral(""));
        gridLayout_2 = new QGridLayout(SearchWidgetForm);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        groupBox = new QGroupBox(SearchWidgetForm);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        comboBox_Source = new QComboBox(groupBox);
        comboBox_Source->setObjectName(QStringLiteral("comboBox_Source"));
        comboBox_Source->setMinimumSize(QSize(0, 22));

        horizontalLayout->addWidget(comboBox_Source);

        comboBox_Group = new QComboBox(groupBox);
        comboBox_Group->setObjectName(QStringLiteral("comboBox_Group"));
        comboBox_Group->setMinimumSize(QSize(0, 22));

        horizontalLayout->addWidget(comboBox_Group);


        verticalLayout->addLayout(horizontalLayout);

        lineEdit = new QLineEdit(groupBox);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setMinimumSize(QSize(0, 31));
        QFont font;
        font.setPointSize(10);
        lineEdit->setFont(font);
        lineEdit->setStyleSheet(QStringLiteral("border: 1px solid gray"));

        verticalLayout->addWidget(lineEdit);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setMinimumSize(QSize(55, 55));
        pushButton->setMaximumSize(QSize(55, 55));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images_ui/images/search.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton->setIcon(icon);
        pushButton->setIconSize(QSize(36, 36));

        gridLayout->addWidget(pushButton, 0, 1, 1, 1);


        gridLayout_2->addWidget(groupBox, 0, 0, 1, 1);


        retranslateUi(SearchWidgetForm);

        QMetaObject::connectSlotsByName(SearchWidgetForm);
    } // setupUi

    void retranslateUi(QWidget *SearchWidgetForm)
    {
        SearchWidgetForm->setWindowTitle(QApplication::translate("SearchWidgetForm", "Form", 0));
        groupBox->setTitle(QString());
        pushButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SearchWidgetForm: public Ui_SearchWidgetForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCHFORM_H
