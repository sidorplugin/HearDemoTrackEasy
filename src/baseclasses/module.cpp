#include "baseclasses/module.h"
#include "baseclasses/linkcreator.h"

#include <QEventLoop>
#include <QDebug>

/*************************  ModulePrivate  **********************************/
class ModulePrivate
{
public:
  ModuleParameters parameters;
  QList <MediaInfo> data;
  Fetcher* fetcher;
  PageSearcher* pageSearcher;
  LinkCreator* linkCreator;

  int count;
  int total;
  int mode;
  bool isStopped;
  bool isPageSearched;
};

//**************************  Module  **************************************//

Module::Module(QObject *parent) : m_d(new ModulePrivate)
{

}

void Module::execute(int mode, const InputPack& input)
{
  qDebug() << "Module::execute";

  m_d->mode = mode;
  m_d->isPageSearched = false;
  m_d->isStopped = false;

  connect(m_d->fetcher, &Fetcher::stopped, [=] () {
      m_d->isStopped = true;
  });

  QString link = m_d->linkCreator->create(mode, input, parameters());
  int start;
  int end;
  switch (mode) {
    case Module::FetchMode:
    {
      QVariantList searchParameters;
      searchParameters.push_back(link);
      searchParameters.push_back(input.fetchPack.dateStart);
      searchParameters.push_back(input.fetchPack.dateEnd);


      QList<int> pagesInfo = m_d->pageSearcher->getPagesInfo(searchParameters);
      if (pagesInfo.isEmpty())
        return;

      m_d->total = pagesInfo.at(PageSearcher::TotalPages);

      start = pagesInfo.at(PageSearcher::StartPage);
      end = pagesInfo.at(PageSearcher::EndPage);
    }
    break;

    case Module::SearchMode:
    {
        start = 1;
        end = MAX;
    }
    break;

  }

  m_d->isPageSearched = true;
  // Стартует выборку.
  fetch(link, start, end);

  emit finished();
}


void Module::stop()
{
  m_d->isPageSearched ? m_d->fetcher->stop() : m_d->pageSearcher->stop();
}


bool Module::isStopped() const
{
    return m_d->isStopped;
}


void Module::setParameters(const ModuleParameters& params)
{
  m_d->parameters = params;
}


ModuleParameters& Module::parameters()
{
  return m_d->parameters;
}


int Module::mode()
{
  return m_d->mode;
}

void Module::setFetcher(Fetcher *fetcher)
{
  m_d->fetcher = fetcher;
}

void Module::setPageSearcher(PageSearcher *pageSearcher)
{
  m_d->pageSearcher = pageSearcher;
}

void Module::setLinkCreator(LinkCreator *linkCreator)
{
  m_d->linkCreator = linkCreator;
}


void Module::fetch(const QString& link, int start, int end)
{
  qDebug() << "Module::fetch( " <<  start << " - " << end << ")";
  int page = start;
  m_d->count = 1;

  while (!m_d->isStopped) {
    if (page > end)
      break;
    m_d->fetcher->load(link.arg(QString::number(page)));
    // Остается в цикле пока не произведется выборка.
    QEventLoop wait;
    connect(m_d->fetcher, SIGNAL(finished()),
            &wait, SLOT(quit()));
    wait.exec();

    page++;
    emit pageFetched(m_d->count, m_d->total, m_d->fetcher->data());
    m_d->count++;
  }
}
