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
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CoverWidget
{
public:
    QGridLayout *gridLayout;
    QLabel *cover1;
    QLabel *cover2;
    QFrame *line;

    void setupUi(QWidget *CoverWidget)
    {
        if (CoverWidget->objectName().isEmpty())
            CoverWidget->setObjectName(QStringLiteral("CoverWidget"));
        CoverWidget->resize(140, 70);
        CoverWidget->setMinimumSize(QSize(140, 70));
        CoverWidget->setMaximumSize(QSize(140, 70));
        gridLayout = new QGridLayout(CoverWidget);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        cover1 = new QLabel(CoverWidget);
        cover1->setObjectName(QStringLiteral("cover1"));
        cover1->setMinimumSize(QSize(70, 70));
        cover1->setMaximumSize(QSize(70, 70));

        gridLayout->addWidget(cover1, 0, 0, 1, 1);

        cover2 = new QLabel(CoverWidget);
        cover2->setObjectName(QStringLiteral("cover2"));
        cover2->setMinimumSize(QSize(70, 70));
        cover2->setMaximumSize(QSize(70, 70));

        gridLayout->addWidget(cover2, 0, 2, 1, 1);

        line = new QFrame(CoverWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 0, 1, 1, 1);


        retranslateUi(CoverWidget);

        QMetaObject::connectSlotsByName(CoverWidget);
    } // setupUi

    void retranslateUi(QWidget *CoverWidget)
    {
        CoverWidget->setWindowTitle(QApplication::translate("CoverWidget", "Form", 0));
        cover1->setText(QString());
        cover2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class CoverWidget: public Ui_CoverWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COVERWIDGET_H
