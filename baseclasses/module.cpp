#include "baseclasses/module.h"
#include "baseclasses/linkcreator.h"
#include "globaldata.h"

#include <QEventLoop>

//**************************  Module  *********************************//

// Запускает модуль.
void Module::execute(Module::Mode mode, DataInput &input)
{
  qDebug() << "Module::execute";

  m_mode = mode;

  connect(m_fetcher, SIGNAL(ready(QList<TrackInfo>)),
          this, SIGNAL(ready(QList<TrackInfo>)));

  connect(m_fetcher, SIGNAL(fetched(Fetcher::State)),
          this, SLOT(on_fetched(Fetcher::State)));

  // Возвращает ссылку для выборки.
  QString link = m_linkCreator->create(mode, input, parameters());
  qDebug() << link;
  int start;
  int end;
  switch (mode) {
    case Module::FetchMode:
    {
      QVariantList searchParameters;
      searchParameters.push_back(link);
      searchParameters.push_back(input.data(DataInput::DateStart).toDate());
      searchParameters.push_back(input.data(DataInput::DateEnd).toDate());

      QList<int> pagesInfo = m_pageSearcher->getPagesInfo(searchParameters);
      if (pagesInfo.isEmpty())
        return;

      // Сохраняет значение общего числа страниц для выборки.
      m_total = pagesInfo.at(PageSearcher::TotalPages);

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
  // Стартует выборку.
  fetch(link, start, end);

  emit finished();
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
}


// Возвращает таблицу параметров модуля.
ModuleParameters& Module::parameters()
{
  return m_parameters;
}


// Возвращает режим работы модуля.
int Module::mode()
{
  return m_mode;
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
    m_fetcher->start(link.arg(QString::number(page)));
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
    break;
  }

}
