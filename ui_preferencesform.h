/********************************************************************************
** Form generated from reading UI file 'preferencesform.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
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
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Preferences
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLabel *label_Loads;
    QLabel *label_Delay;
    QLineEdit *lineEdit_Root;
    QLabel *label_Root;
    QLabel *label_Waiting;
    QSpinBox *spinBox_Delay;
    QSpinBox *spinBox_Waiting;
    QSpinBox *spinBox_Loads;

    void setupUi(QDialog *Preferences)
    {
        if (Preferences->objectName().isEmpty())
            Preferences->setObjectName(QStringLiteral("Preferences"));
        Preferences->resize(204, 158);
        buttonBox = new QDialogButtonBox(Preferences);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(20, 120, 161, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Save);
        layoutWidget = new QWidget(Preferences);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 184, 100));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_Loads = new QLabel(layoutWidget);
        label_Loads->setObjectName(QStringLiteral("label_Loads"));

        gridLayout->addWidget(label_Loads, 3, 0, 1, 1);

        label_Delay = new QLabel(layoutWidget);
        label_Delay->setObjectName(QStringLiteral("label_Delay"));

        gridLayout->addWidget(label_Delay, 0, 0, 1, 1);

        lineEdit_Root = new QLineEdit(layoutWidget);
        lineEdit_Root->setObjectName(QStringLiteral("lineEdit_Root"));

        gridLayout->addWidget(lineEdit_Root, 1, 1, 1, 1);

        label_Root = new QLabel(layoutWidget);
        label_Root->setObjectName(QStringLiteral("label_Root"));

        gridLayout->addWidget(label_Root, 1, 0, 1, 1);

        label_Waiting = new QLabel(layoutWidget);
        label_Waiting->setObjectName(QStringLiteral("label_Waiting"));

        gridLayout->addWidget(label_Waiting, 2, 0, 1, 1);

        spinBox_Delay = new QSpinBox(layoutWidget);
        spinBox_Delay->setObjectName(QStringLiteral("spinBox_Delay"));
        spinBox_Delay->setMaximum(10);

        gridLayout->addWidget(spinBox_Delay, 0, 1, 1, 1);

        spinBox_Waiting = new QSpinBox(layoutWidget);
        spinBox_Waiting->setObjectName(QStringLiteral("spinBox_Waiting"));
        spinBox_Waiting->setMinimum(10000);
        spinBox_Waiting->setMaximum(50000);
        spinBox_Waiting->setSingleStep(1000);
        spinBox_Waiting->setValue(15000);

        gridLayout->addWidget(spinBox_Waiting, 2, 1, 1, 1);

        spinBox_Loads = new QSpinBox(layoutWidget);
        spinBox_Loads->setObjectName(QStringLiteral("spinBox_Loads"));
        spinBox_Loads->setMinimum(1);
        spinBox_Loads->setMaximum(6);
        spinBox_Loads->setValue(3);

        gridLayout->addWidget(spinBox_Loads, 3, 1, 1, 1);


        retranslateUi(Preferences);
        QObject::connect(buttonBox, SIGNAL(accepted()), Preferences, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Preferences, SLOT(reject()));

        QMetaObject::connectSlotsByName(Preferences);
    } // setupUi

    void retranslateUi(QDialog *Preferences)
    {
        Preferences->setWindowTitle(QApplication::translate("Preferences", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270", 0));
        label_Loads->setText(QApplication::translate("Preferences", "Loads :", 0));
        label_Delay->setText(QApplication::translate("Preferences", "Delay :", 0));
#ifndef QT_NO_WHATSTHIS
        lineEdit_Root->setWhatsThis(QApplication::translate("Preferences", "<html><head/><body><p>\320\237\321\203\321\202\321\214 \320\272 \320\277\320\260\320\277\320\272\320\265 \321\201\320\276\321\205\321\200\320\260\320\275\320\265\320\275\320\270\321\217 \321\204\320\260\320\271\320\273\320\276\320\262.</p></body></html>", 0));
#endif // QT_NO_WHATSTHIS
        label_Root->setText(QApplication::translate("Preferences", "Root :", 0));
        label_Waiting->setText(QApplication::translate("Preferences", "Waiting :", 0));
    } // retranslateUi

};

namespace Ui {
    class Preferences: public Ui_Preferences {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PREFERENCESFORM_H
