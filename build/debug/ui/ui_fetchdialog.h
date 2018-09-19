/********************************************************************************
** Form generated from reading UI file 'fetchdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FETCHDIALOG_H
#define UI_FETCHDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_FetchDialog
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_source;
    QComboBox *source;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_begin;
    QDateEdit *dateStart;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_end;
    QDateEdit *dateEnd;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_style;
    QComboBox *style;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_period;
    QComboBox *period;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_filter;
    QComboBox *filter;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *FetchDialog)
    {
        if (FetchDialog->objectName().isEmpty())
            FetchDialog->setObjectName(QStringLiteral("FetchDialog"));
        FetchDialog->resize(223, 227);
        FetchDialog->setMinimumSize(QSize(223, 227));
        FetchDialog->setMaximumSize(QSize(223, 227));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images_ui/images/fetch.png"), QSize(), QIcon::Normal, QIcon::Off);
        FetchDialog->setWindowIcon(icon);
        FetchDialog->setModal(true);
        gridLayout = new QGridLayout(FetchDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_source = new QLabel(FetchDialog);
        label_source->setObjectName(QStringLiteral("label_source"));
        label_source->setMaximumSize(QSize(74, 16777215));

        horizontalLayout->addWidget(label_source);

        source = new QComboBox(FetchDialog);
        source->setObjectName(QStringLiteral("source"));

        horizontalLayout->addWidget(source);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_begin = new QLabel(FetchDialog);
        label_begin->setObjectName(QStringLiteral("label_begin"));
        label_begin->setMaximumSize(QSize(74, 16777215));

        horizontalLayout_2->addWidget(label_begin);

        dateStart = new QDateEdit(FetchDialog);
        dateStart->setObjectName(QStringLiteral("dateStart"));
        dateStart->setCalendarPopup(true);

        horizontalLayout_2->addWidget(dateStart);


        gridLayout->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_end = new QLabel(FetchDialog);
        label_end->setObjectName(QStringLiteral("label_end"));
        label_end->setMaximumSize(QSize(74, 16777215));

        horizontalLayout_3->addWidget(label_end);

        dateEnd = new QDateEdit(FetchDialog);
        dateEnd->setObjectName(QStringLiteral("dateEnd"));
        dateEnd->setCalendarPopup(true);

        horizontalLayout_3->addWidget(dateEnd);


        gridLayout->addLayout(horizontalLayout_3, 2, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_style = new QLabel(FetchDialog);
        label_style->setObjectName(QStringLiteral("label_style"));
        label_style->setMaximumSize(QSize(74, 16777215));

        horizontalLayout_4->addWidget(label_style);

        style = new QComboBox(FetchDialog);
        style->setObjectName(QStringLiteral("style"));

        horizontalLayout_4->addWidget(style);


        gridLayout->addLayout(horizontalLayout_4, 3, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_period = new QLabel(FetchDialog);
        label_period->setObjectName(QStringLiteral("label_period"));
        label_period->setMaximumSize(QSize(74, 16777215));

        horizontalLayout_5->addWidget(label_period);

        period = new QComboBox(FetchDialog);
        period->setObjectName(QStringLiteral("period"));

        horizontalLayout_5->addWidget(period);


        gridLayout->addLayout(horizontalLayout_5, 4, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_filter = new QLabel(FetchDialog);
        label_filter->setObjectName(QStringLiteral("label_filter"));
        label_filter->setMaximumSize(QSize(74, 16777215));

        horizontalLayout_6->addWidget(label_filter);

        filter = new QComboBox(FetchDialog);
        filter->setObjectName(QStringLiteral("filter"));

        horizontalLayout_6->addWidget(filter);


        gridLayout->addLayout(horizontalLayout_6, 5, 0, 1, 1);

        buttonBox = new QDialogButtonBox(FetchDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 6, 0, 1, 1);


        retranslateUi(FetchDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), FetchDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), FetchDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(FetchDialog);
    } // setupUi

    void retranslateUi(QDialog *FetchDialog)
    {
        FetchDialog->setWindowTitle(QApplication::translate("FetchDialog", "\320\222\321\213\320\261\320\276\321\200\320\272\320\260", 0));
        label_source->setText(QApplication::translate("FetchDialog", "\320\230\321\201\321\202\320\276\321\207\320\275\320\270\320\272:", 0));
        label_begin->setText(QApplication::translate("FetchDialog", "\320\235\320\260\321\207\320\260\320\273\320\276:", 0));
        label_end->setText(QApplication::translate("FetchDialog", "\320\232\320\276\320\275\320\265\321\206:", 0));
        label_style->setText(QApplication::translate("FetchDialog", "\320\226\320\260\320\275\321\200:", 0));
        label_period->setText(QApplication::translate("FetchDialog", "\320\237\320\265\321\200\320\270\320\276\320\264:", 0));
        label_filter->setText(QApplication::translate("FetchDialog", "\320\244\320\270\320\273\321\214\321\202\321\200:", 0));
    } // retranslateUi

};

namespace Ui {
    class FetchDialog: public Ui_FetchDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FETCHDIALOG_H
