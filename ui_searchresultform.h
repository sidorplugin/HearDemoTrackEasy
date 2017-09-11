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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SearchResultForm
{
public:
    QTableView *tableView;
    QCheckBox *checkBox;
    QPushButton *pushButton_AddTracks;
    QPushButton *pushButton_Cancel;

    void setupUi(QWidget *SearchResultForm)
    {
        if (SearchResultForm->objectName().isEmpty())
            SearchResultForm->setObjectName(QStringLiteral("SearchResultForm"));
        SearchResultForm->resize(787, 648);
        SearchResultForm->setMinimumSize(QSize(787, 648));
        SearchResultForm->setMaximumSize(QSize(787, 648));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images_ui/images/search.png"), QSize(), QIcon::Normal, QIcon::Off);
        SearchResultForm->setWindowIcon(icon);
        tableView = new QTableView(SearchResultForm);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(9, 9, 771, 601));
        tableView->setMinimumSize(QSize(0, 0));
        checkBox = new QCheckBox(SearchResultForm);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(9, 619, 94, 17));
        pushButton_AddTracks = new QPushButton(SearchResultForm);
        pushButton_AddTracks->setObjectName(QStringLiteral("pushButton_AddTracks"));
        pushButton_AddTracks->setGeometry(QRect(109, 616, 75, 23));
        pushButton_Cancel = new QPushButton(SearchResultForm);
        pushButton_Cancel->setObjectName(QStringLiteral("pushButton_Cancel"));
        pushButton_Cancel->setGeometry(QRect(703, 616, 75, 23));

        retranslateUi(SearchResultForm);

        QMetaObject::connectSlotsByName(SearchResultForm);
    } // setupUi

    void retranslateUi(QWidget *SearchResultForm)
    {
        SearchResultForm->setWindowTitle(QApplication::translate("SearchResultForm", "\320\240\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202\321\213 \320\277\320\276\320\270\321\201\320\272\320\260", 0));
        checkBox->setText(QApplication::translate("SearchResultForm", "\320\222\321\213\320\264\320\265\320\273\320\270\321\202\321\214 \320\262\321\201\320\265", 0));
        pushButton_AddTracks->setText(QApplication::translate("SearchResultForm", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", 0));
        pushButton_Cancel->setText(QApplication::translate("SearchResultForm", "\320\236\321\202\320\274\320\265\320\275\320\260", 0));
    } // retranslateUi

};

namespace Ui {
    class SearchResultForm: public Ui_SearchResultForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCHRESULTFORM_H
