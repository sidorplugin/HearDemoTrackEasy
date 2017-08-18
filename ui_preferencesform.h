/********************************************************************************
** Form generated from reading UI file 'preferencesform.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PREFERENCESFORM_H
#define UI_PREFERENCESFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Preferences
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLabel *label_Delay;
    QLineEdit *lineEdit_Delay;
    QLabel *label_Root;
    QLineEdit *lineEdit_Root;
    QLabel *label_Waiting;
    QLineEdit *lineEdit_Waiting;
    QLabel *label_Loads;
    QLineEdit *lineEdit_Loads;

    void setupUi(QDialog *Preferences)
    {
        if (Preferences->objectName().isEmpty())
            Preferences->setObjectName(QStringLiteral("Preferences"));
        Preferences->resize(241, 159);
        buttonBox = new QDialogButtonBox(Preferences);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(40, 120, 161, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        layoutWidget = new QWidget(Preferences);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 221, 100));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_Delay = new QLabel(layoutWidget);
        label_Delay->setObjectName(QStringLiteral("label_Delay"));

        gridLayout->addWidget(label_Delay, 0, 0, 1, 1);

        lineEdit_Delay = new QLineEdit(layoutWidget);
        lineEdit_Delay->setObjectName(QStringLiteral("lineEdit_Delay"));

        gridLayout->addWidget(lineEdit_Delay, 0, 1, 1, 1);

        label_Root = new QLabel(layoutWidget);
        label_Root->setObjectName(QStringLiteral("label_Root"));

        gridLayout->addWidget(label_Root, 1, 0, 1, 1);

        lineEdit_Root = new QLineEdit(layoutWidget);
        lineEdit_Root->setObjectName(QStringLiteral("lineEdit_Root"));

        gridLayout->addWidget(lineEdit_Root, 1, 1, 1, 1);

        label_Waiting = new QLabel(layoutWidget);
        label_Waiting->setObjectName(QStringLiteral("label_Waiting"));

        gridLayout->addWidget(label_Waiting, 2, 0, 1, 1);

        lineEdit_Waiting = new QLineEdit(layoutWidget);
        lineEdit_Waiting->setObjectName(QStringLiteral("lineEdit_Waiting"));

        gridLayout->addWidget(lineEdit_Waiting, 2, 1, 1, 1);

        label_Loads = new QLabel(layoutWidget);
        label_Loads->setObjectName(QStringLiteral("label_Loads"));

        gridLayout->addWidget(label_Loads, 3, 0, 1, 1);

        lineEdit_Loads = new QLineEdit(layoutWidget);
        lineEdit_Loads->setObjectName(QStringLiteral("lineEdit_Loads"));

        gridLayout->addWidget(lineEdit_Loads, 3, 1, 1, 1);


        retranslateUi(Preferences);
        QObject::connect(buttonBox, SIGNAL(accepted()), Preferences, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Preferences, SLOT(reject()));

        QMetaObject::connectSlotsByName(Preferences);
    } // setupUi

    void retranslateUi(QDialog *Preferences)
    {
        Preferences->setWindowTitle(QApplication::translate("Preferences", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270", 0));
        label_Delay->setText(QApplication::translate("Preferences", "Delay :", 0));
        label_Root->setText(QApplication::translate("Preferences", "Root :", 0));
        label_Waiting->setText(QApplication::translate("Preferences", "Waiting :", 0));
        label_Loads->setText(QApplication::translate("Preferences", "Loads :", 0));
    } // retranslateUi

};

namespace Ui {
    class Preferences: public Ui_Preferences {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PREFERENCESFORM_H
