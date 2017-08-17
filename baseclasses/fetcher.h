#ifndef FETCHER_H
#define FETCHER_H

#include "globaldata.h"
#include "dataclasses/trackinfo.h"

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
  // Возвращает url запроса.
  QString url() const;
  // Устанавливает жанр. Необходим для заполнения выбранных данных значением genre.
  // Для дальнейшего скачивания на диск необходим фиксированный параметр жанра,
  // участвует в пути сохранения.
  void setGenre(const QString& genre);

signals:
  // Выборка окончена.
  void fetched(Fetcher::State);
  void ready(const QList <TrackInfo>&);

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
  QString m_genre;
  bool m_isStop;                  // Остановлена выборка.
  QTimer m_timer;
  int m_delay;                    // Величина задержки между запросами.
  int m_waiting;



};

#endif // FETCHER_H
