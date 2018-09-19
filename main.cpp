#include "mainwindow.h"
#include "logger.h"
#include "dataclasses/mediainfo.h"

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

  gLogger() << note;
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    gLogger().makeLog("main", "log.log", false);
//    qInstallMessageHandler(logMessageHandler);

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


    MainWindow mainWindow;
    mainWindow.show();

    return a.exec();
}
