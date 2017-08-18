/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_Clear;
    QAction *action_Delete;
    QAction *action_FailedLoads;
    QAction *action_Fetch;
    QAction *action_Load;
    QAction *action_Cancel;
    QAction *action_Preferences;
    QAction *action_Exit;
    QAction *action_Info;
    QAction *action_ShowControl;
    QAction *action_Search;
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QDockWidget *dockWidgetPlay;
    QWidget *dockWidgetContents_3;
    QDockWidget *dockWidgetParameters;
    QWidget *dockWidgetContents;
    QDockWidget *dockWidgetDbView;
    QWidget *dockWidgetContents_13;
    QDockWidget *dockWidgetSearch;
    QWidget *dockWidgetContents_2;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;
    QMenu *menu_4;
    QMenu *menu_5;
    QStatusBar *statusBar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(946, 674);
        QFont font;
        font.setPointSize(8);
        font.setKerning(true);
        MainWindow->setFont(font);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images_ui/images/deejayDeFavicon.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setAnimated(false);
        MainWindow->setTabShape(QTabWidget::Rounded);
        MainWindow->setDockOptions(QMainWindow::AllowNestedDocks|QMainWindow::AllowTabbedDocks);
        MainWindow->setUnifiedTitleAndToolBarOnMac(false);
        action_Clear = new QAction(MainWindow);
        action_Clear->setObjectName(QStringLiteral("action_Clear"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images_ui/images/clear.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Clear->setIcon(icon1);
        action_Delete = new QAction(MainWindow);
        action_Delete->setObjectName(QStringLiteral("action_Delete"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/images_ui/images/delete.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Delete->setIcon(icon2);
        action_FailedLoads = new QAction(MainWindow);
        action_FailedLoads->setObjectName(QStringLiteral("action_FailedLoads"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/images_ui/images/failFace.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_FailedLoads->setIcon(icon3);
        action_Fetch = new QAction(MainWindow);
        action_Fetch->setObjectName(QStringLiteral("action_Fetch"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/images_ui/images/fetch.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Fetch->setIcon(icon4);
        action_Load = new QAction(MainWindow);
        action_Load->setObjectName(QStringLiteral("action_Load"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/images_ui/images/download.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Load->setIcon(icon5);
        action_Cancel = new QAction(MainWindow);
        action_Cancel->setObjectName(QStringLiteral("action_Cancel"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/images_ui/images/cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Cancel->setIcon(icon6);
        action_Preferences = new QAction(MainWindow);
        action_Preferences->setObjectName(QStringLiteral("action_Preferences"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/images_ui/images/preferences.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Preferences->setIcon(icon7);
        action_Exit = new QAction(MainWindow);
        action_Exit->setObjectName(QStringLiteral("action_Exit"));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/images_ui/images/exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Exit->setIcon(icon8);
        action_Info = new QAction(MainWindow);
        action_Info->setObjectName(QStringLiteral("action_Info"));
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/images_ui/images/information.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Info->setIcon(icon9);
        action_ShowControl = new QAction(MainWindow);
        action_ShowControl->setObjectName(QStringLiteral("action_ShowControl"));
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/images_ui/images/controller.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_ShowControl->setIcon(icon10);
        action_Search = new QAction(MainWindow);
        action_Search->setObjectName(QStringLiteral("action_Search"));
        QIcon icon11;
        icon11.addFile(QStringLiteral(":/images_ui/images/search.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Search->setIcon(icon11);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        dockWidgetPlay = new QDockWidget(centralWidget);
        dockWidgetPlay->setObjectName(QStringLiteral("dockWidgetPlay"));
        dockWidgetPlay->setMinimumSize(QSize(280, 130));
        dockWidgetPlay->setMaximumSize(QSize(280, 130));
        dockWidgetPlay->setFeatures(QDockWidget::DockWidgetClosable);
        dockWidgetPlay->setAllowedAreas(Qt::LeftDockWidgetArea);
        dockWidgetContents_3 = new QWidget();
        dockWidgetContents_3->setObjectName(QStringLiteral("dockWidgetContents_3"));
        dockWidgetPlay->setWidget(dockWidgetContents_3);

        gridLayout_2->addWidget(dockWidgetPlay, 3, 0, 1, 1);

        dockWidgetParameters = new QDockWidget(centralWidget);
        dockWidgetParameters->setObjectName(QStringLiteral("dockWidgetParameters"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(dockWidgetParameters->sizePolicy().hasHeightForWidth());
        dockWidgetParameters->setSizePolicy(sizePolicy);
        dockWidgetParameters->setMinimumSize(QSize(280, 180));
        dockWidgetParameters->setMaximumSize(QSize(280, 180));
        dockWidgetParameters->setFeatures(QDockWidget::DockWidgetClosable);
        dockWidgetParameters->setAllowedAreas(Qt::LeftDockWidgetArea);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        dockWidgetParameters->setWidget(dockWidgetContents);

        gridLayout_2->addWidget(dockWidgetParameters, 0, 0, 1, 1);

        dockWidgetDbView = new QDockWidget(centralWidget);
        dockWidgetDbView->setObjectName(QStringLiteral("dockWidgetDbView"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(dockWidgetDbView->sizePolicy().hasHeightForWidth());
        dockWidgetDbView->setSizePolicy(sizePolicy1);
        dockWidgetDbView->setMinimumSize(QSize(642, 542));
        dockWidgetDbView->setFeatures(QDockWidget::NoDockWidgetFeatures);
        dockWidgetDbView->setAllowedAreas(Qt::RightDockWidgetArea);
        dockWidgetContents_13 = new QWidget();
        dockWidgetContents_13->setObjectName(QStringLiteral("dockWidgetContents_13"));
        dockWidgetDbView->setWidget(dockWidgetContents_13);

        gridLayout_2->addWidget(dockWidgetDbView, 0, 1, 4, 1);

        dockWidgetSearch = new QDockWidget(centralWidget);
        dockWidgetSearch->setObjectName(QStringLiteral("dockWidgetSearch"));
        dockWidgetSearch->setMinimumSize(QSize(280, 180));
        dockWidgetSearch->setMaximumSize(QSize(280, 180));
        dockWidgetSearch->setFeatures(QDockWidget::DockWidgetClosable);
        dockWidgetSearch->setAllowedAreas(Qt::LeftDockWidgetArea);
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QStringLiteral("dockWidgetContents_2"));
        dockWidgetSearch->setWidget(dockWidgetContents_2);

        gridLayout_2->addWidget(dockWidgetSearch, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 946, 21));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QStringLiteral("menu_2"));
        menu_3 = new QMenu(menuBar);
        menu_3->setObjectName(QStringLiteral("menu_3"));
        menu_4 = new QMenu(menuBar);
        menu_4->setObjectName(QStringLiteral("menu_4"));
        menu_5 = new QMenu(menuBar);
        menu_5->setObjectName(QStringLiteral("menu_5"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        statusBar->setEnabled(true);
        QFont font1;
        font1.setPointSize(8);
        statusBar->setFont(font1);
        statusBar->setAutoFillBackground(false);
        MainWindow->setStatusBar(statusBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(toolBar->sizePolicy().hasHeightForWidth());
        toolBar->setSizePolicy(sizePolicy2);
        toolBar->setMinimumSize(QSize(0, 0));
        toolBar->setSizeIncrement(QSize(0, 0));
        QFont font2;
        font2.setKerning(true);
        toolBar->setFont(font2);
        toolBar->setMovable(false);
        toolBar->setIconSize(QSize(48, 48));
        toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        toolBar->setFloatable(true);
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menuBar->addAction(menu_2->menuAction());
        menuBar->addAction(menu_5->menuAction());
        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_4->menuAction());
        menuBar->addAction(menu_3->menuAction());
        menu->addAction(action_Fetch);
        menu->addAction(action_Load);
        menu->addAction(action_Search);
        menu->addAction(action_Cancel);
        menu->addSeparator();
        menu->addAction(action_Clear);
        menu->addAction(action_Delete);
        menu_2->addAction(action_Exit);
        menu_3->addAction(action_Info);
        menu_4->addAction(action_Preferences);
        menu_5->addAction(action_ShowControl);
        toolBar->addAction(action_Fetch);
        toolBar->addAction(action_Load);
        toolBar->addAction(action_Search);
        toolBar->addAction(action_Cancel);
        toolBar->addSeparator();
        toolBar->addAction(action_Preferences);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Hear Demo Track Easy", 0));
        action_Clear->setText(QApplication::translate("MainWindow", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214 \320\221\320\224", 0));
        action_Delete->setText(QApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \321\201\321\202\321\200\320\276\320\272\321\203", 0));
#ifndef QT_NO_TOOLTIP
        action_Delete->setToolTip(QApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \321\201\321\202\321\200\320\276\320\272\321\203", 0));
#endif // QT_NO_TOOLTIP
        action_FailedLoads->setText(QApplication::translate("MainWindow", "\320\235\320\265\321\203\320\264\320\260\321\207\320\275\320\260\321\217 \320\267\320\260\320\263\321\200\321\203\320\267\320\272\320\260...", 0));
        action_Fetch->setText(QApplication::translate("MainWindow", "\320\222\321\213\320\261\320\276\321\200\320\272\320\260", 0));
        action_Load->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\272\320\260", 0));
        action_Cancel->setText(QApplication::translate("MainWindow", "\320\236\321\202\320\274\320\265\320\275\320\260", 0));
        action_Preferences->setText(QApplication::translate("MainWindow", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270", 0));
#ifndef QT_NO_TOOLTIP
        action_Preferences->setToolTip(QApplication::translate("MainWindow", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270", 0));
#endif // QT_NO_TOOLTIP
        action_Exit->setText(QApplication::translate("MainWindow", "\320\222\321\213\321\205\320\276\320\264", 0));
        action_Info->setText(QApplication::translate("MainWindow", "\320\241\320\277\321\200\320\260\320\262\320\272\320\260", 0));
        action_ShowControl->setText(QApplication::translate("MainWindow", "\320\237\320\276\320\272\320\260\320\267\320\260\321\202\321\214 \320\277\320\260\320\275\320\265\320\273\321\214 \321\203\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\321\217", 0));
        action_Search->setText(QApplication::translate("MainWindow", "\320\237\320\276\320\270\321\201\320\272", 0));
        dockWidgetPlay->setWindowTitle(QApplication::translate("MainWindow", "\320\237\320\273\320\265\320\265\321\200", 0));
        dockWidgetParameters->setWindowTitle(QApplication::translate("MainWindow", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213", 0));
        dockWidgetDbView->setWindowTitle(QApplication::translate("MainWindow", "\320\221\320\260\320\267\320\260 \321\202\321\200\320\265\320\272\320\276\320\262", 0));
        dockWidgetSearch->setWindowTitle(QApplication::translate("MainWindow", "\320\237\320\276\320\270\321\201\320\272", 0));
        menu->setTitle(QApplication::translate("MainWindow", "\320\224\320\265\320\271\321\201\321\202\320\262\320\270\321\217", 0));
        menu_2->setTitle(QApplication::translate("MainWindow", "\320\244\320\260\320\271\320\273", 0));
        menu_3->setTitle(QApplication::translate("MainWindow", "\320\241\320\277\321\200\320\260\320\262\320\272\320\260", 0));
        menu_4->setTitle(QApplication::translate("MainWindow", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213", 0));
        menu_5->setTitle(QApplication::translate("MainWindow", "\320\222\320\270\320\264", 0));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
