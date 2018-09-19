/********************************************************************************
** Form generated from reading UI file 'searchresultform.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEARCHRESULTFORM_H
#define UI_SEARCHRESULTFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SearchResultForm
{
public:
    QWidget *widget;
    QGridLayout *gridLayout;
    QTableView *table;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QCheckBox *checkAll;
    QCheckBox *report;
    QSpacerItem *horizontalSpacer;
    QPushButton *add;
    QPushButton *cancel;

    void setupUi(QWidget *SearchResultForm)
    {
        if (SearchResultForm->objectName().isEmpty())
            SearchResultForm->setObjectName(QStringLiteral("SearchResultForm"));
        SearchResultForm->setWindowModality(Qt::ApplicationModal);
        SearchResultForm->resize(640, 420);
        SearchResultForm->setMinimumSize(QSize(640, 420));
        SearchResultForm->setMaximumSize(QSize(640, 420));
        widget = new QWidget(SearchResultForm);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 10, 621, 401));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        table = new QTableView(widget);
        table->setObjectName(QStringLiteral("table"));
        table->setMinimumSize(QSize(0, 0));

        gridLayout->addWidget(table, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        checkAll = new QCheckBox(widget);
        checkAll->setObjectName(QStringLiteral("checkAll"));
        checkAll->setMaximumSize(QSize(100, 16777215));

        verticalLayout->addWidget(checkAll);

        report = new QCheckBox(widget);
        report->setObjectName(QStringLiteral("report"));
        report->setMaximumSize(QSize(100, 16777215));

        verticalLayout->addWidget(report);


        horizontalLayout->addLayout(verticalLayout);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        add = new QPushButton(widget);
        add->setObjectName(QStringLiteral("add"));
        add->setMaximumSize(QSize(70, 16777215));

        horizontalLayout->addWidget(add);

        cancel = new QPushButton(widget);
        cancel->setObjectName(QStringLiteral("cancel"));
        cancel->setMaximumSize(QSize(70, 16777215));

        horizontalLayout->addWidget(cancel);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);


        retranslateUi(SearchResultForm);

        QMetaObject::connectSlotsByName(SearchResultForm);
    } // setupUi

    void retranslateUi(QWidget *SearchResultForm)
    {
        SearchResultForm->setWindowTitle(QApplication::translate("SearchResultForm", "\320\240\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202\321\213 \320\277\320\276\320\270\321\201\320\272\320\260", 0));
        checkAll->setText(QApplication::translate("SearchResultForm", "\320\222\321\213\320\264\320\265\320\273\320\270\321\202\321\214 \320\262\321\201\320\265", 0));
        report->setText(QApplication::translate("SearchResultForm", "\320\236\321\202\321\207\320\265\321\202", 0));
        add->setText(QApplication::translate("SearchResultForm", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", 0));
        cancel->setText(QApplication::translate("SearchResultForm", "\320\236\321\202\320\274\320\265\320\275\320\260", 0));
    } // retranslateUi

};

namespace Ui {
    class SearchResultForm: public Ui_SearchResultForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCHRESULTFORM_H
