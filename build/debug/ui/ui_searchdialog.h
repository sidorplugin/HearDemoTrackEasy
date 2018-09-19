/********************************************************************************
** Form generated from reading UI file 'searchdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEARCHDIALOG_H
#define UI_SEARCHDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SearchDialog
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *source;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QComboBox *group;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *text;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SearchDialog)
    {
        if (SearchDialog->objectName().isEmpty())
            SearchDialog->setObjectName(QStringLiteral("SearchDialog"));
        SearchDialog->resize(268, 131);
        SearchDialog->setMinimumSize(QSize(268, 131));
        SearchDialog->setMaximumSize(QSize(268, 131));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images_ui/images/search.png"), QSize(), QIcon::Normal, QIcon::Off);
        SearchDialog->setWindowIcon(icon);
        gridLayout = new QGridLayout(SearchDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(SearchDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(74, 0));
        label->setMaximumSize(QSize(74, 16777215));

        horizontalLayout->addWidget(label);

        source = new QComboBox(SearchDialog);
        source->setObjectName(QStringLiteral("source"));

        horizontalLayout->addWidget(source);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(SearchDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(74, 0));
        label_2->setMaximumSize(QSize(74, 16777215));

        horizontalLayout_2->addWidget(label_2);

        group = new QComboBox(SearchDialog);
        group->setObjectName(QStringLiteral("group"));

        horizontalLayout_2->addWidget(group);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(SearchDialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMinimumSize(QSize(74, 0));
        label_3->setMaximumSize(QSize(74, 16777215));

        horizontalLayout_3->addWidget(label_3);

        text = new QLineEdit(SearchDialog);
        text->setObjectName(QStringLiteral("text"));

        horizontalLayout_3->addWidget(text);


        verticalLayout->addLayout(horizontalLayout_3);

        buttonBox = new QDialogButtonBox(SearchDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(SearchDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), SearchDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SearchDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(SearchDialog);
    } // setupUi

    void retranslateUi(QDialog *SearchDialog)
    {
        SearchDialog->setWindowTitle(QApplication::translate("SearchDialog", "\320\237\320\276\320\270\321\201\320\272", 0));
        label->setText(QApplication::translate("SearchDialog", "\320\230\321\201\321\202\320\276\321\207\320\275\320\270\320\272", 0));
        label_2->setText(QApplication::translate("SearchDialog", "\320\223\321\200\321\203\320\277\320\277\320\260", 0));
        label_3->setText(QApplication::translate("SearchDialog", "\320\242\320\265\320\272\321\201\321\202", 0));
    } // retranslateUi

};

namespace Ui {
    class SearchDialog: public Ui_SearchDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCHDIALOG_H
