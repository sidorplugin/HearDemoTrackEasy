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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_Preferences
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_Delay;
    QSpinBox *spinBox_Delay;
    QLabel *label;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_Waiting;
    QSpinBox *spinBox_Waiting;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_Loads;
    QSpinBox *spinBox_Loads;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_Root;
    QLineEdit *lineEdit_Root;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Preferences)
    {
        if (Preferences->objectName().isEmpty())
            Preferences->setObjectName(QStringLiteral("Preferences"));
        Preferences->resize(204, 158);
        gridLayout = new QGridLayout(Preferences);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_Delay = new QLabel(Preferences);
        label_Delay->setObjectName(QStringLiteral("label_Delay"));

        horizontalLayout->addWidget(label_Delay);

        spinBox_Delay = new QSpinBox(Preferences);
        spinBox_Delay->setObjectName(QStringLiteral("spinBox_Delay"));
        spinBox_Delay->setMaximum(10);

        horizontalLayout->addWidget(spinBox_Delay);

        label = new QLabel(Preferences);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_Waiting = new QLabel(Preferences);
        label_Waiting->setObjectName(QStringLiteral("label_Waiting"));

        horizontalLayout_3->addWidget(label_Waiting);

        spinBox_Waiting = new QSpinBox(Preferences);
        spinBox_Waiting->setObjectName(QStringLiteral("spinBox_Waiting"));
        spinBox_Waiting->setMinimum(10000);
        spinBox_Waiting->setMaximum(100000);
        spinBox_Waiting->setSingleStep(1000);
        spinBox_Waiting->setValue(15000);

        horizontalLayout_3->addWidget(spinBox_Waiting);

        label_2 = new QLabel(Preferences);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_3->addWidget(label_2);


        gridLayout->addLayout(horizontalLayout_3, 1, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_Loads = new QLabel(Preferences);
        label_Loads->setObjectName(QStringLiteral("label_Loads"));

        horizontalLayout_4->addWidget(label_Loads);

        spinBox_Loads = new QSpinBox(Preferences);
        spinBox_Loads->setObjectName(QStringLiteral("spinBox_Loads"));
        spinBox_Loads->setMinimum(1);
        spinBox_Loads->setMaximum(6);
        spinBox_Loads->setValue(3);

        horizontalLayout_4->addWidget(spinBox_Loads);

        label_3 = new QLabel(Preferences);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_4->addWidget(label_3);


        gridLayout->addLayout(horizontalLayout_4, 2, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_Root = new QLabel(Preferences);
        label_Root->setObjectName(QStringLiteral("label_Root"));

        horizontalLayout_2->addWidget(label_Root);

        lineEdit_Root = new QLineEdit(Preferences);
        lineEdit_Root->setObjectName(QStringLiteral("lineEdit_Root"));

        horizontalLayout_2->addWidget(lineEdit_Root);


        gridLayout->addLayout(horizontalLayout_2, 3, 0, 1, 1);

        buttonBox = new QDialogButtonBox(Preferences);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Save);

        gridLayout->addWidget(buttonBox, 4, 0, 1, 1);


        retranslateUi(Preferences);
        QObject::connect(buttonBox, SIGNAL(accepted()), Preferences, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Preferences, SLOT(reject()));

        QMetaObject::connectSlotsByName(Preferences);
    } // setupUi

    void retranslateUi(QDialog *Preferences)
    {
        Preferences->setWindowTitle(QApplication::translate("Preferences", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270", 0));
        label_Delay->setText(QApplication::translate("Preferences", "Delay :", 0));
        label->setText(QApplication::translate("Preferences", "\321\201\320\265\320\272", 0));
        label_Waiting->setText(QApplication::translate("Preferences", "Waiting :", 0));
        label_2->setText(QApplication::translate("Preferences", "\321\201\320\265\320\272", 0));
        label_Loads->setText(QApplication::translate("Preferences", "Loads :", 0));
        label_3->setText(QApplication::translate("Preferences", "\321\210\321\202", 0));
        label_Root->setText(QApplication::translate("Preferences", "Root :", 0));
#ifndef QT_NO_WHATSTHIS
        lineEdit_Root->setWhatsThis(QApplication::translate("Preferences", "<html><head/><body><p>\320\237\321\203\321\202\321\214 \320\272 \320\277\320\260\320\277\320\272\320\265 \321\201\320\276\321\205\321\200\320\260\320\275\320\265\320\275\320\270\321\217 \321\204\320\260\320\271\320\273\320\276\320\262.</p></body></html>", 0));
#endif // QT_NO_WHATSTHIS
    } // retranslateUi

};

namespace Ui {
    class Preferences: public Ui_Preferences {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PREFERENCESFORM_H
