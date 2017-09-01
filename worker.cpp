#include "worker.h"
#include "database.h"

//**************************  Worker  *********************************//


Worker::Worker(QObject *parent) : QObject(parent)
{
  qDebug() << "Worker::Worker";
  m_model = Database::getInstance()->model();
  createDownloader();
}

Worker::~Worker()
{
  foreach (Module* module, m_modules) {
      delete module;
  }
}


// Создает модуль.
void Worker::createModule(ModuleFactory *factory)
{
  qDebug() << "Worker::createModule";
  Module* module = new Module;

  module->m_fetcher = factory->createFetcher();
  module->m_pageSearcher = factory->createPageSearcher();
  module->m_linkCreator = factory->createLinkCreator();
  module->setParameters(factory->createParameters());

  // Создает связи.
  connect(module, SIGNAL(ready(QList<AlbumInfo>)),
          this, SLOT(handleTracksFromModule(QList<AlbumInfo>)));

  connect(module, SIGNAL(finished()),
          this, SLOT(slot_onModulesFinished()));

  connect(module, SIGNAL(pageFetched(int, int)),
          this, SIGNAL(signal_pageFetched(int, int)));

  m_modules.insert(module->parameters().data(ModuleParameters::Name).toString(),
                                                                         module);
}


// Создает загрузчик.
void Worker::createDownloader()
{
  qDebug() << "Worker::createDownloader";
  // Создает Downloader.
  m_downloader = new Downloader(this);
  connect(m_downloader, SIGNAL(finished()),
          this, SLOT(slot_onModulesFinished()));
}


// Стартует выборку.
void Worker::slot_fetch(DataInput &input)
{
  qDebug() << "Worker::slot_fetch()";

  // Сохраняет поступившие данные на выборку.
  m_input = input;

  Module* module = m_modules.value(input.data(DataInput::FetchSource).toString());
  module->execute(Module::FetchMode, m_input);

}


// Загружает треки.
void Worker::slot_load(DataInput &input)
{
  qDebug() << "Worker::slot_load()";
  // TODO Mode load.
//  m_downloader->initialize(data.isSingleLoad);

  if (input.data(DataInput::SingleLoad).toBool()) {
    AlbumInfo track = m_model->getTrackInfo(input.data(DataInput::Row).toInt());
    qDebug() << track.toStringList();
    m_downloader->load(track);
  }
  else
    m_downloader->load();
}


// Стартует поиск.
void Worker::slot_search(DataInput &input)
{
  qDebug() << "Worker::slot_search()";
  // Сохраняет поступившие данные на выборку.
  m_input = input;

  // Проверяет в каком модуле необходимо выполнять поиск.
  QString source = input.data(DataInput::SearchSource).toString();
  if (source == "All") {
    QList <Module*> modules = m_modules.values();
    foreach (Module* module, modules) {
      module->execute(Module::SearchMode, m_input);
    }
  }
  else {
    Module* module = m_modules.value(source);
    module->execute(Module::SearchMode, m_input);
  }
}


// Отменяет действие.
void Worker::slot_cancel()
{
  qDebug() << "Worker::slot_cancel()";

  switch (m_state) {
    case MainWindow::SearchingState :
    case MainWindow::FetchingState :
    {
        Module* module =
            m_modules.value(m_input.data(DataInput::FetchSource).toString());
        module->stop();
    }
    break;

    case MainWindow::LoadingState :
        m_downloader->stop();
    break;
    }
}


// Устанавливает состояние программы.
void Worker::slot_setState(int state)
{
  if (m_state != state)
    m_state = state;
}


// По получению сигналов от модулей о завершении работы отправляет сигнал Ui
// об изменении статуса.
void Worker::slot_onModulesFinished()
{
  qDebug() << "Worker::slot_onModulesFinished()";
  Downloader* downloader = qobject_cast<Downloader*>(QObject::sender());
  Module* module = qobject_cast<Module*>(QObject::sender());

  if (downloader)
    emit signal_stateChanged(MainWindow::LoadedState);
  else {
    if (module->mode() == Module::FetchMode) {
      qDebug() << "FetchMode";
      emit signal_stateChanged(MainWindow::FetchedState);
    }
    else {
      qDebug() << "SearchedState";
      emit signal_stateChanged(MainWindow::SearchedState);
    }
  }
}

// Добавляет треки в модель.
void Worker::addTracksToModel(const QList<AlbumInfo> &tracks)
{
  m_model->add(tracks);
}


// Добавляет треки.
void Worker::handleTracksFromModule(const QList<AlbumInfo>& tracks)
{
  qDebug() << "Worker::handleTracksFromModule";

  // Проверяет в каком режиме находиться Worker.
  switch (m_state) {
    // В случае режима выборки добавляет треки в модель.
    case MainWindow::FetchingState :
        addTracksToModel(tracks);
    break;

    // В случае режима поиска испускает сигнал о готовности треков.
    case MainWindow::SearchingState :
      emit signal_ready(tracks);
    break;
  }

}
