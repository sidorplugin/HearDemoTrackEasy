#-------------------------------------------------
#
# Project created by QtCreator 2017-01-08T09:17:40
#
#-------------------------------------------------

QT       += core gui network webkitwidgets multimedia sql xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HearDemoTrackEasy
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    modules/deejayde/deejaydefetcher.cpp \
    modules/deejayde/deejaydealbumfetcher.cpp \
    modules/deejayde/deejaydepagesearcher.cpp \
    modules/deejayde/tabledates.cpp \
    modules/hardwax/hardwaxfetcher.cpp \
    modules/hardwax/hardwaxpagesearcher.cpp \
    modules/juno/junopagesearcher.cpp \
    modules/juno/junofetcher.cpp \
    modules/deejayde/deejaydelinkcreator.cpp \
    downloader/downloader.cpp \
    downloader/idtagcreator.cpp \
    downloader/downloadhandler.cpp \
    downloader/saver.cpp \
    baseclasses/module.cpp \
    baseclasses/fetcher.cpp \
    widgets/waitingwidget/waitingwidget.cpp \
    widgets/fetchparameterswidget/fetchparametersitemdelegate.cpp \
    widgets/fetchparameterswidget/fetchparameterswidget.cpp \
    widgets/dbviewwidget/dbviewwidget.cpp \
    widgets/dbviewwidget/dbviewitemdelegate.cpp \
    widgets/dbviewwidget/dbviewmodel.cpp \
    widgets/playerwidget/playerwidget.cpp \
    widgets/playerwidget/runningstring.cpp \
    dataclasses/trackinfo.cpp \
    database.cpp \
    worker.cpp \
    baseclasses/pagesearcher.cpp \
    globaldata.cpp \
    dataclasses/moduleparameters.cpp \
    modules/hardwax/hardwaxlinkcreator.cpp \
    modules/juno/junolinkcreator.cpp \
    widgets/fetchparameterswidget/fetchparametersmodel.cpp

HEADERS  += mainwindow.h \
    modules/deejayde/deejaydefetcher.h \
    modules/deejayde/deejaydealbumfetcher.h \
    modules/deejayde/deejaydepagesearcher.h \
    modules/deejayde/tabledates.h \
    modules/hardwax/hardwaxfetcher.h \
    modules/hardwax/hardwaxpagesearcher.h \
    modules/juno/junopagesearcher.h \
    modules/juno/junofetcher.h \
    modules/deejayde/deejaydemodulefactory.h \
    modules/hardwax/hardwaxmodulefactory.h \
    modules/juno/junomodulefactory.h \
    modules/deejayde/deejaydelinkcreator.h \
    downloader/idtagcreator.h \
    downloader/downloader.h \
    downloader/downloadhandler.h \
    downloader/saver.h \
    baseclasses/module.h \
    baseclasses/fetcher.h \
    baseclasses/modulefactory.h \
    baseclasses/linkcreator.h \
    widgets/waitingwidget/waitingwidget.h \
    widgets/fetchparameterswidget/fetchparametersitemdelegate.h \
    widgets/fetchparameterswidget/fetchparameterswidget.h \
    widgets/dbviewwidget/dbviewwidget.h \
    widgets/dbviewwidget/dbviewitemdelegate.h \
    widgets/dbviewwidget/dbviewmodel.h \
    widgets/playerwidget/playerwidget.h \
    widgets/playerwidget/runningstring.h \
    dataclasses/datainput.h \
    dataclasses/trackinfo.h \
    database.h \
    worker.h \
    baseclasses/pagesearcher.h \
    globaldata.h \
    dataclasses/moduleparameters.h \
    modules/hardwax/hardwaxlinkcreator.h \
    modules/juno/junolinkcreator.h \
    widgets/fetchparameterswidget/fetchparametersmodel.h

FORMS    += mainwindow.ui \
    widgets/playerwidget/playerwidgetform.ui

RESOURCES += \
    resources/resources.qrc