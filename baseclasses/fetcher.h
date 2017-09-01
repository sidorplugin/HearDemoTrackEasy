#ifndef FETCHER_H
#define FETCHER_H

#include "globaldata.h"
#include "dataclasses/albuminfo.h"

#include <QObject>
#include <QWebPage>
#include <QWebFrame>
#include <QTimer>

// Базовый класс, осуществляющий выборку данных с сайта.

class Fetcher : public QObject
{
  Q_OBJECT
public:
  enum State { Finished,        // Завершен.
               Stoped,          // Остановлен.
               NoElements };    // Нет элементов.

  explicit Fetcher(QObject *parent = 0);
  ~Fetcher();

  // Стартует выборку.
  void start(const QString& url);
  // Останавливает выборку.
  void stop();
  // Загружает параметры выборки.
//  void loadFetchParameters(const ModuleParameters& p);

  // Возвращает url запроса.
  QString url() const;

signals:
  // Выборка окончена.
  void fetched(Fetcher::State);
  void ready(const QList <AlbumInfo>&);

protected slots:
  // Абстрактный метод обрабатывающий полученные данные.
  virtual void result(bool ok) = 0;

private slots:
  void progress(int progress);
  void on_started();
  void on_finished(bool ok);
  void on_timeOut();

protected:
  // Осуществляет паузу.
  void pause(int max);

protected:
  QWebPage m_page;                // Web страница.
  QString m_url;                  // Текущий url запрос.
  bool m_isStop;                  // Остановлена выборка.
  QTimer m_timer;
  int m_delay;                    // Величина задержки между запросами.
  int m_waiting;



};

#endif // FETCHER_H
