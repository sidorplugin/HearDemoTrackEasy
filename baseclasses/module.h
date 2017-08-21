#ifndef MODULE_H
#define MODULE_H

#include "baseclasses/fetcher.h"
#include "baseclasses/pagesearcher.h"
#include "dataclasses/datainput.h"

#include <QObject>

// Класс Module - базовый класс-источник. Производит выборку данных с
// определенного ресурса. Метод exec() запускает модуль в работу, при готовности
// результата испускает сигнал ready. Для остановки работы модуля существует
// метод stop().

class LinkCreator;

class Module : public QObject
{
  Q_OBJECT
public:
  enum Mode { FetchMode, SearchMode };

  Module(QObject *parent = 0) {}
  ~Module() {}

  // Запускает модуль.
  void execute(Module::Mode mode, DataInput& input);
  // Останавливает модуль.
  void stop();
  // Устанавливает таблицу параметров модуля.
  void setParameters(const ModuleParameters& params);
  // Возвращает таблицу параметров модуля.
  ModuleParameters parameters();


signals:
  // Выборка страницы завершена.
  void pageFetched(int, int);
  // Вся выборка завершена.
  void finished();
  // Ответ с данными.
  void ready(const QList <TrackInfo>&);
  // Остановлен.
  void stoped();

private slots:
  // Обработка сигнала парсера pageFetched.
  void on_fetched(Fetcher::State state);


public:
  Fetcher* m_fetcher;            // Парсер.
  Fetcher* m_albumFetcher;       // Парсер альбома.
  PageSearcher* m_pageSearcher;  // Поисковик страниц.
  LinkCreator* m_linkCreator;    // Создатель ссылок.

private:
  // Стартует выборку со страницы start до страницы end.
  void fetch(const QString& link, int start, int end);

protected:
  //TODO перепроверить необходимость.
  QString m_href;             // Строка запроса.
  int m_count;                // Текущая страница выборки.
  int m_total;                // Общее число страниц для выборки.
  bool m_isStoped;            // Остановлен?

private:
  ModuleParameters m_parameters;
};

#endif // MODULE_H
