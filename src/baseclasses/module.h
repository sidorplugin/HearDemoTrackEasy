#ifndef MODULE_H
#define MODULE_H

#include "baseclasses/fetcher.h"
#include "baseclasses/pagesearcher.h"
#include "dataclasses/datainput.h"
#include "dataclasses/moduleparameters.h"

#include <QObject>

// Класс Module - базовый класс-источник. Производит выборку данных с
// определенного ресурса. Метод exec() запускает модуль в работу, при готовности
// результата испускает сигнал ready. Для остановки работы модуля существует
// метод stop().

const int MAX = 22222;

class LinkCreator;

class ModulePrivate;

class Module : public QObject
{
  Q_OBJECT
public:
  enum Mode {
    FetchMode,
    SearchMode
  };

  Module(QObject *parent = 0);
  ~Module() {}

  // Запускает модуль.
  void execute(int mode, const InputPack& input);
  // Останавливает модуль.
  void stop();
  //
  bool isStopped() const;
  // Устанавливает таблицу параметров модуля.
  void setParameters(const ModuleParameters& params);
  // Возвращает таблицу параметров модуля.
  ModuleParameters& parameters();
  // Возвращает режим работы модуля.
  int mode();
  //
  void setFetcher(Fetcher* fetcher);
  void setPageSearcher(PageSearcher* pageSearcher);
  void setLinkCreator(LinkCreator* linkCreator);


signals:
  // Выборка страницы завершена.
  void pageFetched(int, int, const QList<MediaInfo>&);
  // Вся выборка завершена.
  void finished();


private:
  // Стартует выборку со страницы start до страницы end.
  void fetch(const QString& link, int start, int end);

private:
  ModulePrivate* m_d;
};

#endif // MODULE_H
