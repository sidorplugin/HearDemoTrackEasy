/********************************************************************************
** Form generated from reading UI file 'playerwidgetform.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLAYERWIDGETFORM_H
#define UI_PLAYERWIDGETFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlayerWidgetForm
{
public:
    QGridLayout *gridLayout_2;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label_TrackInfo;
    QSlider *slider_Rewind;
    QHBoxLayout *horizontalLayout;
    QToolButton *toolButton_Previous;
    QToolButton *toolButton_Play;
    QToolButton *toolButton_Pause;
    QToolButton *toolButton_Stop;
    QToolButton *toolButton_Next;
    QSlider *slider_Volume;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *PlayerWidgetForm)
    {
        if (PlayerWidgetForm->objectName().isEmpty())
            PlayerWidgetForm->setObjectName(QStringLiteral("PlayerWidgetForm"));
        PlayerWidgetForm->resize(286, 113);
        gridLayout_2 = new QGridLayout(PlayerWidgetForm);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalSpacer = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 0, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 1, 0, 1, 1);

        groupBox = new QGroupBox(PlayerWidgetForm);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setStyleSheet(QLatin1String("background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #E0E0E0, stop: 1 #FFFFFF);\n"
"    border: 2px solid gray;\n"
"    border-radius: 4px;\n"
""));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(6, 6, 6, 6);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_TrackInfo = new QLabel(groupBox);
        label_TrackInfo->setObjectName(QStringLiteral("label_TrackInfo"));
        label_TrackInfo->setMinimumSize(QSize(250, 20));
        label_TrackInfo->setMaximumSize(QSize(250, 20));

        verticalLayout->addWidget(label_TrackInfo);

        slider_Rewind = new QSlider(groupBox);
        slider_Rewind->setObjectName(QStringLiteral("slider_Rewind"));
        slider_Rewind->setMinimumSize(QSize(250, 20));
        slider_Rewind->setMaximumSize(QSize(250, 20));
        slider_Rewind->setStyleSheet(QLatin1String("QSlider::groove:horizontal {\n"
"	background: red;\n"
"    position: absolute;\n"
"}\n"
"\n"
"QSlider::handle:horizontal {\n"
"	height: 1px;\n"
"    background: #545454;\n"
"    margin: 0 -3px;\n"
"}\n"
"\n"
"QSlider::add-page:horizontal {\n"
"	background: #facd95;\n"
"}\n"
"\n"
"QSlider::sub-page:horizontal {\n"
"	background: #8b8b8b;\n"
"}"));
        slider_Rewind->setOrientation(Qt::Horizontal);
        slider_Rewind->setTickPosition(QSlider::NoTicks);

        verticalLayout->addWidget(slider_Rewind);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        toolButton_Previous = new QToolButton(groupBox);
        toolButton_Previous->setObjectName(QStringLiteral("toolButton_Previous"));
        toolButton_Previous->setMinimumSize(QSize(0, 0));
        toolButton_Previous->setMaximumSize(QSize(40, 40));
        toolButton_Previous->setStyleSheet(QLatin1String("border-top: 3px transparent;\n"
"border-bottom: 3px transparent;\n"
"border-right: 3px transparent;\n"
"border-left: 3px transparent;"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images_ui/images/player_start.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_Previous->setIcon(icon);
        toolButton_Previous->setIconSize(QSize(36, 36));

        horizontalLayout->addWidget(toolButton_Previous);

        toolButton_Play = new QToolButton(groupBox);
        toolButton_Play->setObjectName(QStringLiteral("toolButton_Play"));
        toolButton_Play->setMinimumSize(QSize(0, 0));
        toolButton_Play->setMaximumSize(QSize(40, 40));
        toolButton_Play->setStyleSheet(QLatin1String("border-top: 3px transparent;\n"
"border-bottom: 3px transparent;\n"
"border-right: 3px transparent;\n"
"border-left: 3px transparent;"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images_ui/images/player_play.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_Play->setIcon(icon1);
        toolButton_Play->setIconSize(QSize(36, 36));

        horizontalLayout->addWidget(toolButton_Play);

        toolButton_Pause = new QToolButton(groupBox);
        toolButton_Pause->setObjectName(QStringLiteral("toolButton_Pause"));
        toolButton_Pause->setMinimumSize(QSize(0, 0));
        toolButton_Pause->setMaximumSize(QSize(40, 40));
        toolButton_Pause->setStyleSheet(QLatin1String("border-top: 3px transparent;\n"
"border-bottom: 3px transparent;\n"
"border-right: 3px transparent;\n"
"border-left: 3px transparent;\n"
""));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/images_ui/images/player_pause.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_Pause->setIcon(icon2);
        toolButton_Pause->setIconSize(QSize(36, 36));
        toolButton_Pause->setCheckable(false);
        toolButton_Pause->setAutoRaise(false);

        horizontalLayout->addWidget(toolButton_Pause);

        toolButton_Stop = new QToolButton(groupBox);
        toolButton_Stop->setObjectName(QStringLiteral("toolButton_Stop"));
        toolButton_Stop->setMaximumSize(QSize(40, 40));
        toolButton_Stop->setStyleSheet(QLatin1String("border-top: transparent;\n"
"border-bottom: transparent;\n"
"border-right: transparent;\n"
"border-left: transparent;\n"
""));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/images_ui/images/player_stop.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_Stop->setIcon(icon3);
        toolButton_Stop->setIconSize(QSize(36, 36));

        horizontalLayout->addWidget(toolButton_Stop);

        toolButton_Next = new QToolButton(groupBox);
        toolButton_Next->setObjectName(QStringLiteral("toolButton_Next"));
        toolButton_Next->setMinimumSize(QSize(0, 0));
        toolButton_Next->setMaximumSize(QSize(40, 40));
        toolButton_Next->setStyleSheet(QLatin1String("border-top: 3px transparent;\n"
"border-bottom: 3px transparent;\n"
"border-right: 3px transparent;\n"
"border-left: 3px transparent;\n"
"hovered: true;"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/images_ui/images/player_end.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_Next->setIcon(icon4);
        toolButton_Next->setIconSize(QSize(36, 36));

        horizontalLayout->addWidget(toolButton_Next);


        verticalLayout->addLayout(horizontalLayout);


        horizontalLayout_2->addLayout(verticalLayout);

        slider_Volume = new QSlider(groupBox);
        slider_Volume->setObjectName(QStringLiteral("slider_Volume"));
        slider_Volume->setMinimumSize(QSize(0, 90));
        slider_Volume->setMaximumSize(QSize(10, 90));
        slider_Volume->setStyleSheet(QLatin1String("QSlider::groove:vertical {\n"
"         background: black;\n"
"         position: absolute;        \n"
"}\n"
"\n"
"QSlider::handle:vertical {\n"
"       height: 7px;\n"
"       background: #545454;\n"
"}\n"
"\n"
"QSlider::add-page:vertical {\n"
"	background: #8b8b8b;\n"
"}\n"
"\n"
"QSlider::sub-page:vertical {\n"
"	background: #facd95;\n"
"}"));
        slider_Volume->setValue(50);
        slider_Volume->setOrientation(Qt::Vertical);
        slider_Volume->setTickPosition(QSlider::NoTicks);

        horizontalLayout_2->addWidget(slider_Volume);


        gridLayout->addLayout(horizontalLayout_2, 0, 0, 1, 1);


        gridLayout_2->addWidget(groupBox, 1, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(1, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 1, 2, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 1, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 2, 1, 1, 1);


        retranslateUi(PlayerWidgetForm);

        QMetaObject::connectSlotsByName(PlayerWidgetForm);
    } // setupUi

    void retranslateUi(QWidget *PlayerWidgetForm)
    {
        PlayerWidgetForm->setWindowTitle(QString());
        groupBox->setTitle(QString());
        label_TrackInfo->setText(QString());
        toolButton_Previous->setText(QString());
        toolButton_Previous->setShortcut(QApplication::translate("PlayerWidgetForm", "Z", 0));
        toolButton_Play->setText(QString());
        toolButton_Play->setShortcut(QApplication::translate("PlayerWidgetForm", "X", 0));
        toolButton_Pause->setText(QString());
        toolButton_Pause->setShortcut(QApplication::translate("PlayerWidgetForm", "C", 0));
        toolButton_Stop->setText(QApplication::translate("PlayerWidgetForm", "...", 0));
        toolButton_Stop->setShortcut(QApplication::translate("PlayerWidgetForm", "V", 0));
        toolButton_Next->setText(QString());
        toolButton_Next->setShortcut(QApplication::translate("PlayerWidgetForm", "B", 0));
    } // retranslateUi

};

namespace Ui {
    class PlayerWidgetForm: public Ui_PlayerWidgetForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAYERWIDGETFORM_H
