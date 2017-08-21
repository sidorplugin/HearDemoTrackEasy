#include "mainwindow.h"
#include "globaldata.h"
#include "worker.h"
#include "dataclasses/trackinfo.h"
#include "modules/deejayde/deejaydemodulefactory.h"
#include "modules/juno/junomodulefactory.h"
#include "modules/hardwax/hardwaxmodulefactory.h"

#include <QApplication>
#include <QStyleFactory>
#include <QObject>
#include <QThread>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qRegisterMetaType<TrackInfo>("TrackInfo");
    qRegisterMetaType<DataInput>("DataInput");

//    QFile file(":/styles/style/darkstyle.qss");
//    file.open(QFile::ReadOnly);
//    QString styleSheet = QLatin1String(file.readAll());
//    a.setStyleSheet(styleSheet);
//    file.close();

    a.setStyleSheet("QProgressBar {"
                      "border: 1px solid transparent;"
                      "text-align: center;"
                    "}"

                    "QProgressBar::chunk {"
                      "background-color: #facd95;"
                    "}"

                    "QTableView {"
                      "selection-background-color: #ababab;"
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

    // Запрос на получение информации о проигрываемом треке.
    QObject::connect(&mainWindow, SIGNAL(signal_play(int)),
                     worker, SLOT(slot_play(int)));

    // Запрос на удаление трека.
    QObject::connect(&mainWindow, SIGNAL(signal_removeTrack(int)),
                     worker, SLOT(slot_removeTrack(int)));

    // Запрос на очищение базы треков.
    QObject::connect(&mainWindow, SIGNAL(signal_clearDatabase()),
                     worker, SLOT(slot_clearDatabase()));

    // Запрос на отмену операции.
    QObject::connect(&mainWindow, SIGNAL(signal_cancel()),
                     worker, SLOT(slot_cancel()));

    // Запрос на копирование ссылки.
    QObject::connect(&mainWindow, SIGNAL(signal_copyLink(int)),
                     worker, SLOT(slot_copyLink(int)));

    // Запрос на копирование названия трека.
    QObject::connect(&mainWindow, SIGNAL(signal_copyTitle(int)),
                     worker, SLOT(slot_copyTitle(int)));

    // Сигнал об изменении состояния программы.
    QObject::connect(&mainWindow, SIGNAL(signal_stateChanged(int)),
                     worker, SLOT(slot_setState(int)));

    // Signals To Mainwindow -----------------------------------------------
    // Запрос на проигрывание трека.
    QObject::connect(worker, SIGNAL(signal_play(TrackInfo&)),
                     &mainWindow, SLOT(slot_play(TrackInfo&)));

    // При изменении состояния программы со стороны worker'а вносит изменения
    // в графический интерфейс.
    QObject::connect(worker, SIGNAL(signal_stateChanged(int)),
                     &mainWindow, SLOT(slot_updateUI(int)));

    // По окончании выборки страницы отображает изменения в графическом интерфейсе.
    QObject::connect(worker, SIGNAL(signal_pageFetched(int, int)),
                     &mainWindow, SLOT(slot_pageFetched(int, int)));


//    workerThread.start();

    return a.exec();
}
