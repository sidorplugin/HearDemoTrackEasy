#include "model.h"
#include "worker.h"
#include "database.h"
#include "modules/deejayde/deejaydemodulefactory.h"
#include "modules/juno/junomodulefactory.h"
#include "modules/hardwax/hardwaxmodulefactory.h"

//*************************  WorkerPrivate  ****************************//
class WorkerPrivate
{
public:
  QHash <QString, Module*> modules;
  Downloader* downloader;
  Model* model;
  InputPack input;
};


//**************************  Worker  *********************************//


Worker::Worker() : m_d(new WorkerPrivate)
{
  qDebug() << "Worker::Worker";
  initialize();
}

Worker::~Worker()
{
  foreach (Module* module, m_d->modules) {
      delete module;
    }
}


void Worker::createModule(ModuleFactory *factory)
{
  qDebug() << "Worker::createModule";
  Module* module = new Module;

  module->setFetcher(factory->createFetcher());
  module->setPageSearcher(factory->createPageSearcher());
  module->setLinkCreator(factory->createLinkCreator());
  module->setParameters(factory->createParameters());

  connect(module, SIGNAL(finished()), this, SIGNAL(finished()));

  connect(module, &Module::pageFetched, [=] (int count, int total, const QList<MediaInfo>& data) {
      emit ready(count, total, data);
  });

  m_d->modules.insert(module->parameters().data(ModuleParameters::Name).toString(),
                   module);
}


void Worker::execute(int mode, const InputPack &input)
{
  qDebug() << "Worker::execute()";

  m_d->input = input;

  Module* module;
  switch (mode) {
    case Module::FetchMode:
    {
      module = m_d->modules.value(m_d->input.fetchPack.source);
      module->execute(mode, m_d->input);
    }
    break;

    case Module::SearchMode:
    {
      // Проверяет в каком модуле необходимо выполнять поиск.
      QString source = m_d->input.searchPack.source;
      if (source == "All") {
          QList <Module*> modules = m_d->modules.values();
          foreach (Module* m, modules) {
              m->execute(mode, m_d->input);
            }
      }
      else {
          module = m_d->modules.value(source);
          module->execute(mode, m_d->input);
      }
    }
    break;
    }
}

void Worker::initialize()
{
  m_d->model = Database::getInstance()->model();

  // Создает модули.
  DeejayDeModuleFactory dFactory;
  HardwaxModuleFactory hFactory;
  JunoModuleFactory jFactory;

  createModule(&dFactory);
  createModule(&hFactory);
  createModule(&jFactory);

  createDownloader();
}


void Worker::createDownloader()
{
  qDebug() << "Worker::createDownloader";

  m_d->downloader = new Downloader(this);
  connect(m_d->downloader, SIGNAL(finished()), this, SIGNAL(loaded()));
}


// Загружает все треки или один трек в строке row.
void Worker::load(int row, bool single)
{
  qDebug() << "Worker::load()";

  QSettings settings("settings.ini", QSettings::IniFormat);
  QString root = settings.value("Root").toString();
  int delay = settings.value("Delay").toInt();
  int loads = settings.value("Loads").toInt();

  m_d->downloader->initialize(root, delay, loads, single);

  if (single) {
    MediaInfo media = m_d->model->mediaInfo(row);
    m_d->downloader->load(media);
  }
  else
    m_d->downloader->load();
}


void Worker::cancel(int state)
{
  qDebug() << "Worker::cancel()";

  switch (state) {
    case MainWindow::SearchState :
    case MainWindow::FetchState :
    {
        Module* module = m_d->modules.value(m_d->input.fetchPack.source);
        module->stop();
    }
    break;

    case MainWindow::LoadState :
        m_d->downloader->stop();
    break;
    }
}

MediaInfo Worker::getMediaInfo(int row)
{
  m_d->model->mediaInfo(row);
}

void Worker::enableFixReport()
{
  m_d->model->fixReport();
}

void Worker::addToModel(const QList<MediaInfo> &media)
{
  m_d->model->add(media);
}

void Worker::removeFromModel(int row)
{
  MediaInfo media = m_d->model->mediaInfo(row);
  m_d->model->remove(media);
}

void Worker::clearModel()
{
  m_d->model->remove();
}

QString Worker::report() const
{
  return m_d->model->report();
}

QHash<QString, Module *> Worker::modules() const
{
  return m_d->modules;
}

int Worker::countAddedTracks() const
{
  return m_d->model->countAddedTracks();
}
