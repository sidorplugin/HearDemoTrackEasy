/********************************************************************************
** Form generated from reading UI file 'playerwidgetform.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLAYERWIDGETFORM_H
#define UI_PLAYERWIDGETFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlayerWidgetForm
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QToolButton *previous;
    QToolButton *play;
    QToolButton *pause;
    QToolButton *stop;
    QToolButton *next;
    QSlider *rewind;
    QSlider *volume;
    QLabel *info;

    void setupUi(QWidget *PlayerWidgetForm)
    {
        if (PlayerWidgetForm->objectName().isEmpty())
            PlayerWidgetForm->setObjectName(QStringLiteral("PlayerWidgetForm"));
        PlayerWidgetForm->resize(221, 70);
        PlayerWidgetForm->setMinimumSize(QSize(221, 70));
        PlayerWidgetForm->setMaximumSize(QSize(221, 70));
        layoutWidget = new QWidget(PlayerWidgetForm);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(12, 32, 181, 32));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        previous = new QToolButton(layoutWidget);
        previous->setObjectName(QStringLiteral("previous"));
        previous->setMinimumSize(QSize(0, 0));
        previous->setMaximumSize(QSize(30, 30));
        previous->setStyleSheet(QLatin1String("border-top: 3px transparent;\n"
"border-bottom: 3px transparent;\n"
"border-right: 3px transparent;\n"
"border-left: 3px transparent;"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images_ui/images/player_start.png"), QSize(), QIcon::Normal, QIcon::Off);
        previous->setIcon(icon);
        previous->setIconSize(QSize(36, 36));

        horizontalLayout->addWidget(previous);

        play = new QToolButton(layoutWidget);
        play->setObjectName(QStringLiteral("play"));
        play->setMinimumSize(QSize(0, 0));
        play->setMaximumSize(QSize(30, 30));
        play->setStyleSheet(QLatin1String("border-top: 3px transparent;\n"
"border-bottom: 3px transparent;\n"
"border-right: 3px transparent;\n"
"border-left: 3px transparent;"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images_ui/images/player_play.png"), QSize(), QIcon::Normal, QIcon::Off);
        play->setIcon(icon1);
        play->setIconSize(QSize(36, 36));

        horizontalLayout->addWidget(play);

        pause = new QToolButton(layoutWidget);
        pause->setObjectName(QStringLiteral("pause"));
        pause->setMinimumSize(QSize(0, 0));
        pause->setMaximumSize(QSize(30, 30));
        pause->setStyleSheet(QLatin1String("border-top: 3px transparent;\n"
"border-bottom: 3px transparent;\n"
"border-right: 3px transparent;\n"
"border-left: 3px transparent;\n"
""));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/images_ui/images/player_pause.png"), QSize(), QIcon::Normal, QIcon::Off);
        pause->setIcon(icon2);
        pause->setIconSize(QSize(36, 36));
        pause->setCheckable(false);
        pause->setAutoRaise(false);

        horizontalLayout->addWidget(pause);

        stop = new QToolButton(layoutWidget);
        stop->setObjectName(QStringLiteral("stop"));
        stop->setMaximumSize(QSize(30, 30));
        stop->setStyleSheet(QLatin1String("border-top: transparent;\n"
"border-bottom: transparent;\n"
"border-right: transparent;\n"
"border-left: transparent;\n"
""));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/images_ui/images/player_stop.png"), QSize(), QIcon::Normal, QIcon::Off);
        stop->setIcon(icon3);
        stop->setIconSize(QSize(36, 36));

        horizontalLayout->addWidget(stop);

        next = new QToolButton(layoutWidget);
        next->setObjectName(QStringLiteral("next"));
        next->setMinimumSize(QSize(0, 0));
        next->setMaximumSize(QSize(30, 30));
        next->setStyleSheet(QLatin1String("border-top: 3px transparent;\n"
"border-bottom: 3px transparent;\n"
"border-right: 3px transparent;\n"
"border-left: 3px transparent;\n"
"hovered: true;"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/images_ui/images/player_end.png"), QSize(), QIcon::Normal, QIcon::Off);
        next->setIcon(icon4);
        next->setIconSize(QSize(36, 36));

        horizontalLayout->addWidget(next);

        rewind = new QSlider(PlayerWidgetForm);
        rewind->setObjectName(QStringLiteral("rewind"));
        rewind->setGeometry(QRect(12, 22, 181, 10));
        rewind->setMinimumSize(QSize(181, 10));
        rewind->setMaximumSize(QSize(181, 10));
        rewind->setStyleSheet(QLatin1String("QSlider::groove:horizontal {\n"
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
        rewind->setOrientation(Qt::Horizontal);
        rewind->setTickPosition(QSlider::NoTicks);
        volume = new QSlider(PlayerWidgetForm);
        volume->setObjectName(QStringLiteral("volume"));
        volume->setGeometry(QRect(201, 22, 10, 40));
        volume->setMinimumSize(QSize(10, 40));
        volume->setMaximumSize(QSize(10, 40));
        volume->setStyleSheet(QLatin1String("QSlider::groove:vertical {\n"
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
        volume->setValue(50);
        volume->setOrientation(Qt::Vertical);
        volume->setTickPosition(QSlider::NoTicks);
        info = new QLabel(PlayerWidgetForm);
        info->setObjectName(QStringLiteral("info"));
        info->setGeometry(QRect(12, 7, 181, 15));
        info->setMinimumSize(QSize(181, 15));
        info->setMaximumSize(QSize(181, 15));

        retranslateUi(PlayerWidgetForm);

        QMetaObject::connectSlotsByName(PlayerWidgetForm);
    } // setupUi

    void retranslateUi(QWidget *PlayerWidgetForm)
    {
        PlayerWidgetForm->setWindowTitle(QString());
#ifndef QT_NO_TOOLTIP
        previous->setToolTip(QApplication::translate("PlayerWidgetForm", "Prev (Ctrl+Z)", 0));
#endif // QT_NO_TOOLTIP
        previous->setText(QString());
        previous->setShortcut(QApplication::translate("PlayerWidgetForm", "Z", 0));
#ifndef QT_NO_TOOLTIP
        play->setToolTip(QApplication::translate("PlayerWidgetForm", "Play (Ctrl+X)", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_ACCESSIBILITY
        play->setAccessibleDescription(QString());
#endif // QT_NO_ACCESSIBILITY
        play->setText(QString());
        play->setShortcut(QApplication::translate("PlayerWidgetForm", "X", 0));
#ifndef QT_NO_TOOLTIP
        pause->setToolTip(QApplication::translate("PlayerWidgetForm", "Pause (Ctrl+C)", 0));
#endif // QT_NO_TOOLTIP
        pause->setText(QString());
        pause->setShortcut(QApplication::translate("PlayerWidgetForm", "C", 0));
#ifndef QT_NO_TOOLTIP
        stop->setToolTip(QApplication::translate("PlayerWidgetForm", "Stop (Ctrl+V)", 0));
#endif // QT_NO_TOOLTIP
        stop->setText(QApplication::translate("PlayerWidgetForm", "...", 0));
        stop->setShortcut(QApplication::translate("PlayerWidgetForm", "V", 0));
#ifndef QT_NO_TOOLTIP
        next->setToolTip(QApplication::translate("PlayerWidgetForm", "Next (Ctrl+B)", 0));
#endif // QT_NO_TOOLTIP
        next->setText(QString());
        next->setShortcut(QApplication::translate("PlayerWidgetForm", "B", 0));
        info->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class PlayerWidgetForm: public Ui_PlayerWidgetForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAYERWIDGETFORM_H
