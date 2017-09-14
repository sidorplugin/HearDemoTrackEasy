#include "mainwindow.h"
#include "logger.h"
#include "globaldata.h"
#include "worker.h"
#include "dataclasses/mediainfo.h"
#include "modules/deejayde/deejaydemodulefactory.h"
#include "modules/juno/junomodulefactory.h"
#include "modules/hardwax/hardwaxmodulefactory.h"

#include <QApplication>
#include <QStyleFactory>
#include <QObject>
#include <QThread>
#include <QDebug>


void logMessageHandler(QtMsgType type,
                       const QMessageLogContext &context,
                       const QString &msg)
{
  QString note = QString("[%1]%2\n").
    arg(QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss")).arg(msg);

  switch (type){
      case QtDebugMsg:
          gLogger() << note;
      break;

      case QtWarningMsg:
          gLogger() << note;
      break;

      case QtCriticalMsg:
          gLogger() << note;
      break;

      case QtFatalMsg:
          gLogger() << note;
      break;
   }
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qRegisterMetaType<MediaInfo>("MediaInfo");
    qRegisterMetaType<DataInput>("DataInput");

    gLogger().makeLog("main", "log.log", false);
    qInstallMessageHandler(logMessageHandler);

//    QFile file(":/styles/style/darkstyle.qss");
//    file.open(QFile::ReadOnly);
//    QString styleSheet = QLatin1String(file.readAll());
//    a.setStyleSheet(styleSheet);
//    file.close();

    a.setStyleSheet("QProgressBar {"
                      "border: 1px solid transparent;"
                      "text-align: left;"
                    "}"

                    "QProgressBar:selected { background: #ababab;}"

                    "QProgressBar::chunk {"
                      "background-color: #facd95;"
                    "}"

                    "QTableView {"
                      "selection-background-color: #ababab;"
                      "selection-color: black;"
                    "}"

                   );


//    QThread workerThread;

    GlobalData::getInstance()->readGlobalSettings();
    GlobalData::getInstance()->readFromXmlFile(":/data/data/deejayDe_module.xml");
    GlobalData::getInstance()->readFromXmlFile(":/data/data/hardwax_module.xml");
    GlobalData::getInstance()->readFromXmlFile(":/data/data/juno_module.xml");

    // Создает интерфейс пользователя UI.
    MainWindow mainWindow;
    mainWindow.show();

    // Создает рабочий компонент.
    Worker* worker = new Worker;

    // Создает фабрики модулей.
    DeejayDeModuleFactory dFactory;
    HardwaxModuleFactory hFactory;
    JunoModuleFactory jFactory;

    // Создает модули.
    worker->createModule(&dFactory);
    worker->createModule(&hFactory);
    worker->createModule(&jFactory);

//    worker->moveToThread(&workerThread);
//    QObject::connect(&workerThread, SIGNAL(finished()),
//                     worker, SLOT(deleteLater()));

//    QObject::connect(qApp, SIGNAL(lastWindowClosed()),
//                     worker, SLOT(quit()));

    // Устанавливает соединения мастера и UI.

    // Signals To Worker ---------------------------------------------------
    // Запрос на выборку данных.
    QObject::connect(&mainWindow, SIGNAL(signal_fetch(DataInput&)),
                     worker, SLOT(slot_fetch(DataInput&)));

    // Запрос на загрузку данных.
    QObject::connect(&mainWindow, SIGNAL(signal_load(DataInput&)),
                     worker, SLOT(slot_load(DataInput&)));

    // Запрос на поиск данных.
    QObject::connect(&mainWindow, SIGNAL(signal_search(DataInput&)),
                     worker, SLOT(slot_search(DataInput&)));

    // Запрос на отмену операции.
    QObject::connect(&mainWindow, SIGNAL(signal_cancel()),
                     worker, SLOT(slot_cancel()));

    // Сигнал об изменении состояния программы.
    QObject::connect(&mainWindow, SIGNAL(signal_stateChanged(int)),
                     worker, SLOT(slot_setState(int)));

    // Сигнал от ui о готовности выбранных треков для добавления в просмотрщик треков.
    QObject::connect(&mainWindow, SIGNAL(signal_ready(QList<MediaInfo>)),
                     worker, SLOT(addTracksToModel(QList<MediaInfo>)));

    // Signals To Mainwindow -----------------------------------------------

    // При изменении состояния программы со стороны worker'а вносит изменения
    // в графический интерфейс.
    QObject::connect(worker, SIGNAL(signal_stateChanged(int)),
                     &mainWindow, SLOT(slot_updateUI(int)));

    // По окончании выборки страницы отображает изменения в графическом интерфейсе.
    QObject::connect(worker, SIGNAL(signal_pageFetched(int, int)),
                     &mainWindow, SLOT(slot_pageFetched(int, int)));

    // При поиске по готовности списка треков передает в интерфейс список.
    QObject::connect(worker, SIGNAL(signal_ready(QList<MediaInfo>)),
                     &mainWindow, SLOT(slot_addTracks(QList<MediaInfo>)));


//    workerThread.start();


    return a.exec();
}
