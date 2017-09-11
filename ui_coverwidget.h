/********************************************************************************
** Form generated from reading UI file 'coverwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COVERWIDGET_H
#define UI_COVERWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CoverWidget
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout_2;
    QLabel *label_Image1;
    QLabel *label_Image2;

    void setupUi(QWidget *CoverWidget)
    {
        if (CoverWidget->objectName().isEmpty())
            CoverWidget->setObjectName(QStringLiteral("CoverWidget"));
        CoverWidget->resize(286, 142);
        gridLayout = new QGridLayout(CoverWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setHorizontalSpacing(0);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        groupBox = new QGroupBox(CoverWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_3 = new QGridLayout(groupBox);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setHorizontalSpacing(0);
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_Image1 = new QLabel(groupBox);
        label_Image1->setObjectName(QStringLiteral("label_Image1"));
        label_Image1->setMinimumSize(QSize(138, 138));

        gridLayout_2->addWidget(label_Image1, 0, 0, 1, 1);

        label_Image2 = new QLabel(groupBox);
        label_Image2->setObjectName(QStringLiteral("label_Image2"));
        label_Image2->setMinimumSize(QSize(138, 138));

        gridLayout_2->addWidget(label_Image2, 0, 1, 1, 1);


        gridLayout_3->addLayout(gridLayout_2, 0, 0, 1, 1);


        gridLayout->addWidget(groupBox, 0, 0, 1, 1);


        retranslateUi(CoverWidget);

        QMetaObject::connectSlotsByName(CoverWidget);
    } // setupUi

    void retranslateUi(QWidget *CoverWidget)
    {
        CoverWidget->setWindowTitle(QApplication::translate("CoverWidget", "Form", 0));
        groupBox->setTitle(QString());
        label_Image1->setText(QString());
        label_Image2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class CoverWidget: public Ui_CoverWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COVERWIDGET_H
