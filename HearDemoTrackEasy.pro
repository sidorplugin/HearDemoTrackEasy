#-------------------------------------------------
#
# Project created by QtCreator 2017-01-08T09:17:40
#
#-------------------------------------------------

QT += core gui network multimedia sql xml concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HearDemoTrackEasy
TEMPLATE = app

INCLUDEPATH += src

DEPENDPATH += src

SOURCES += main.cpp\
    src/mainwindow.cpp \
    src/modules/deejayde/deejaydefetcher.cpp \
    src/modules/deejayde/deejaydealbumfetcher.cpp \
    src/modules/deejayde/deejaydepagesearcher.cpp \
    src/modules/deejayde/tabledates.cpp \
    src/modules/hardwax/hardwaxfetcher.cpp \
    src/modules/hardwax/hardwaxpagesearcher.cpp \
    src/modules/juno/junopagesearcher.cpp \
    src/modules/juno/junofetcher.cpp \
    src/modules/deejayde/deejaydelinkcreator.cpp \
    src/downloader/downloader.cpp \
    src/downloader/idtagcreator.cpp \
    src/downloader/downloadhandler.cpp \
    src/downloader/saver.cpp \
    src/baseclasses/module.cpp \
    src/baseclasses/fetcher.cpp \
    src/widgets/waitingwidget/waitingwidget.cpp \
    src/widgets/dbviewwidget/dbviewwidget.cpp \
    src/widgets/dbviewwidget/dbviewitemdelegate.cpp \
    src/widgets/playerwidget/playerwidget.cpp \
    src/database.cpp \
    src/worker.cpp \
    src/dataclasses/moduleparameters.cpp \
    src/modules/hardwax/hardwaxlinkcreator.cpp \
    src/modules/juno/junolinkcreator.cpp \
    src/preferences.cpp \
    src/model.cpp \
    src/dataclasses/mediainfo.cpp \
    src/widgets/coverwidget/coverwidget.cpp \
    src/widgets/dbviewwidget/filterlineedit.cpp \
    src/widgets/dbviewwidget/filtertableheader.cpp \
    src/logger.cpp \
    src/fetchdialog.cpp \
    src/searchdialog.cpp \
    src/forms/searchresultmodel.cpp \
    src/forms/searchresultform.cpp \
    src/baseclasses/htmlelement.cpp

HEADERS  += src/mainwindow.h \
    src/modules/deejayde/deejaydefetcher.h \
    src/modules/deejayde/deejaydealbumfetcher.h \
    src/modules/deejayde/deejaydepagesearcher.h \
    src/modules/deejayde/tabledates.h \
    src/modules/hardwax/hardwaxfetcher.h \
    src/modules/hardwax/hardwaxpagesearcher.h \
    src/modules/juno/junopagesearcher.h \
    src/modules/juno/junofetcher.h \
    src/modules/deejayde/deejaydemodulefactory.h \
    src/modules/hardwax/hardwaxmodulefactory.h \
    src/modules/juno/junomodulefactory.h \
    src/modules/deejayde/deejaydelinkcreator.h \
    src/downloader/idtagcreator.h \
    src/downloader/downloader.h \
    src/downloader/downloadhandler.h \
    src/downloader/saver.h \
    src/baseclasses/module.h \
    src/baseclasses/fetcher.h \
    src/baseclasses/modulefactory.h \
    src/baseclasses/linkcreator.h \
    src/widgets/waitingwidget/waitingwidget.h \
    src/widgets/dbviewwidget/dbviewwidget.h \
    src/widgets/dbviewwidget/dbviewitemdelegate.h \
    src/widgets/playerwidget/playerwidget.h \
    src/dataclasses/datainput.h \
    src/database.h \
    src/worker.h \
    src/baseclasses/pagesearcher.h \
    src/dataclasses/moduleparameters.h \
    src/modules/hardwax/hardwaxlinkcreator.h \
    src/modules/juno/junolinkcreator.h \
    src/preferences.h \
    src/model.h \
    src/dataclasses/mediainfo.h \
    src/widgets/coverwidget/coverwidget.h \
    src/widgets/dbviewwidget/filterlineedit.h \
    src/widgets/dbviewwidget/filtertableheader.h \
    src/logger.h \
    src/fetchdialog.h \
    src/searchdialog.h \
    src/forms/searchresultmodel.h \
    src/forms/searchresultform.h \
    src/baseclasses/htmlelement.h


FORMS += src/ui/mainwindow.ui \
    src/ui/playerwidgetform.ui \
    src/ui/preferencesform.ui \
    src/ui/searchresultform.ui \
    src/ui/coverwidget.ui \
    src/ui/fetchdialog.ui \
    src/ui/searchdialog.ui \

RC_FILE = rcc/hdte.rc

RESOURCES += \
    src/resources/resources.qrc

include(common.pri)

QMAKE_CXXFLAGS += -std=c++11
