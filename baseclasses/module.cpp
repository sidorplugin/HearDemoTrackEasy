#include "baseclasses/module.h"
#include "baseclasses/linkcreator.h"
#include "globaldata.h"

#include <QEventLoop>

//**************************  Module  *********************************//

// Запускает модуль.
void Module::execute(Module::Mode mode, const DataInput &data)
{
  qDebug() << "Module::execute";

  connect(m_fetcher, SIGNAL(ready(QList<TrackInfo>)),
          this, SIGNAL(ready(QList<TrackInfo>)));

  switch (mode) {
    case Module::FetchMode:
    {
      // Инициализация компонентов и подготовка данных.
      m_fetcher->setGenre(data.genre);

      // Проверяет есть ли в модуле элемент albumFetcher.
      if (m_albumFetcher) {
          m_albumFetcher->setGenre(data.genre);
        }

      // Возвращает ссылку для выборки.
      QString link = m_linkCreator->create(mode, data, parameters());

      QVariantList searchParameters;
      searchParameters.push_back(link);
      searchParameters.push_back(data.dateStart);
      searchParameters.push_back(data.dateEnd);

      QList<int> pagesInfo = m_pageSearcher->getPagesInfo(searchParameters);
      if (pagesInfo.isEmpty())
        return;

      // Сохраняет значение общего числа страниц для выборки.
      m_total = pagesInfo.at(PageSearcher::TotalPages);

      // Стартует выборку.
      fetch(link, pagesInfo.at(PageSearcher::StartPage),
            pagesInfo.at(PageSearcher::EndPage));

      emit finished();
    }
    break;

    case Module::SearchMode:
    {

    }
    break;
  }

}


// Останавливает модуль.
void Module::stop()
{
  // TODO Завершать в зависимости кто находится в работе.
  m_fetcher->stop();
  m_pageSearcher->stop();
}


// Устанавливает таблицу параметров модуля.
void Module::setParameters(const ModuleParameters& params)
{
  m_parameters = params;
  qDebug() << m_parameters.toStringList();
}


// Возвращает таблицу параметров модуля.
ModuleParameters Module::parameters()
{
  return m_parameters;
}


// Стартует выборку со страницы start до страницы end.
void Module::fetch(const QString& link, int start, int end)
{
  qDebug() << "Module::fetch( " <<  start << " - " << end << ")";
  int page = start;
  m_count = 1;

  while (!m_isStoped) {
    if (page > end)
      break;
    m_fetcher->start(link + QString::number(page));
    // Остается в цикле пока не произведется выборка.
    QEventLoop wait;
    connect(m_fetcher, SIGNAL(fetched(Fetcher::State)),
            &wait, SLOT(quit()));
    wait.exec();

    page++;
    m_count++;
  }
}


// Обработка сигнала парсера pageFetched.
void Module::on_fetched(Fetcher::State state)
{
  // 3 состояния выборщика:
  // 1 - удачно завершенная выборка страницы
  // 2 - нет элементов
  // 3 - остановлено
  switch (state) {
    case Fetcher::Finished :
      emit pageFetched(m_count, m_total);
    break;
    case Fetcher::NoElements :
    case Fetcher::Stoped :
      m_isStoped = true;
      emit stoped();
    break;
  }

}
