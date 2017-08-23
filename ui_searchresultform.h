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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SearchResultForm
{
public:
    QWidget *widget;
    QGridLayout *gridLayout;
    QTableView *tableView;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_AddTracks;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_Cancel;

    void setupUi(QWidget *SearchResultForm)
    {
        if (SearchResultForm->objectName().isEmpty())
            SearchResultForm->setObjectName(QStringLiteral("SearchResultForm"));
        SearchResultForm->resize(400, 300);
        widget = new QWidget(SearchResultForm);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 10, 381, 281));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        tableView = new QTableView(widget);
        tableView->setObjectName(QStringLiteral("tableView"));

        gridLayout->addWidget(tableView, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButton_AddTracks = new QPushButton(widget);
        pushButton_AddTracks->setObjectName(QStringLiteral("pushButton_AddTracks"));

        horizontalLayout->addWidget(pushButton_AddTracks);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_Cancel = new QPushButton(widget);
        pushButton_Cancel->setObjectName(QStringLiteral("pushButton_Cancel"));

        horizontalLayout->addWidget(pushButton_Cancel);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);


        retranslateUi(SearchResultForm);

        QMetaObject::connectSlotsByName(SearchResultForm);
    } // setupUi

    void retranslateUi(QWidget *SearchResultForm)
    {
        SearchResultForm->setWindowTitle(QApplication::translate("SearchResultForm", "\320\240\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202\321\213 \320\277\320\276\320\270\321\201\320\272\320\260", 0));
        pushButton_AddTracks->setText(QApplication::translate("SearchResultForm", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", 0));
        pushButton_Cancel->setText(QApplication::translate("SearchResultForm", "\320\236\321\202\320\274\320\265\320\275\320\260", 0));
    } // retranslateUi

};

namespace Ui {
    class SearchResultForm: public Ui_SearchResultForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCHRESULTFORM_H
