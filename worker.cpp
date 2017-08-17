#include <QClipboard>

#include "worker.h"
#include "database.h"

//**************************  Worker  *********************************//


Worker::Worker(QObject *parent) : QObject(parent)
{
  qDebug() << "Worker::Worker";
  m_model = Database::getInstance()->model();
  createDownloader();
  GlobalData::getInstance()->readGlobalSettings();
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
  module->m_albumFetcher = factory->createAlbumFetcher();
  module->m_pageSearcher = factory->createPageSearcher();
  module->m_linkCreator = factory->createLinkCreator();
  module->setParameters(factory->createParameters());

  // Создает связи.
  connect(module, SIGNAL(ready(QList<TrackInfo>)),
          this, SLOT(addTracksToModel(QList<TrackInfo>)));

  connect(module, SIGNAL(finished()),
          this, SLOT(slot_onModulesFinished()));

  connect(module, SIGNAL(pageFetched(int, int)),
          this, SIGNAL(signal_pageFetched(int, int)));

  m_modules.insert(module->parameters().name(), module);
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
void Worker::slot_fetch(const DataInput &data)
{
  qDebug() << "Worker::slot_fetch()";

  // Сохраняет поступившие данные на выборку.
  m_data = data;

  Module* module = m_modules.value(m_data.source);
  module->execute(Module::FetchMode, m_data);

}


// Загружает треки.
void Worker::slot_load(const DataInput &data)
{
  qDebug() << "Worker::slot_load()";
  // TODO Mode load.
//  m_downloader->initialize(data.isSingleLoad);

  if (data.isSingleLoad) {
    TrackInfo track = m_model->getTrackInfo(data.row);
    qDebug() << track.toStringList();
    m_downloader->load(track);
  }
  else
    m_downloader->load();
}


// Проигрывает трек.
void Worker::slot_play(int row)
{
  qDebug() << "Worker::slot_play()";
  TrackInfo track = m_model->getTrackInfo(row);
  emit signal_play(track);
}

// Стартует поиск.
void Worker::slot_search(const DataInput &data)
{
  qDebug() << "Worker::slot_search()";
}


// Отменяет действие.
void Worker::slot_cancel()
{
  qDebug() << "Worker::slot_cancel()";

  switch (m_state) {
    case MainWindow::FetchingState :
    {
        Module* module = m_modules.value(m_data.source);
        module->stop();
    }
    break;

    case MainWindow::LoadingState :
        m_downloader->stop();
    break;
    }
}


// Удаляет трек из базы.
void Worker::slot_removeTrack(int row)
{
  TrackInfo track = m_model->getTrackInfo(row);
  m_model->remove(track);
}


// Очищает базу треков.
void Worker::slot_clearDatabase()
{
    m_model->remove();
}


// Копирует ссылку трека в буфер.
void Worker::slot_copyLink(int row)
{
    TrackInfo track = m_model->getTrackInfo(row);
    QString bufferText = track.data(TrackInfo::Link).toString();
    QApplication::clipboard()->setText(bufferText);
}


// Копирует название трека в буфер.
void Worker::slot_copyTitle(int row)
{
  TrackInfo track = m_model->getTrackInfo(row);
  QString artist = track.data(TrackInfo::AlbumArtist).toString();
  QString title = track.data(TrackInfo::Title).toString();
  QString bufferText = artist + " - " + title;
  QApplication::clipboard()->setText(bufferText);
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
  Downloader* downloader = qobject_cast<Downloader*>(QObject::sender());

  if (downloader)
    emit signal_stateChanged(MainWindow::LoadedState);
  else
    emit signal_stateChanged(MainWindow::FetchedState);
}


// Добавляет треки в модель.
void Worker::addTracksToModel(const QList<TrackInfo>& tracks)
{
  qDebug() << "Worker::addTracksToModel";
  m_model->add(tracks);
}
