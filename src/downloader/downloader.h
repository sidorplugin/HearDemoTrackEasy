#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include "downloader/idtagcreator.h"
#include "model.h"
#include "downloader/downloadhandler.h"
#include "downloader/saver.h"

#include <QObject>
#include <QNetworkReply>
#include <QTimer>
#include <QEventLoop>
#include <QHash>
#include <QMutex>


// Класс загрузчик. Загружает все файлы из БД или отдельно взятые.
// Поочередно передает их "Обработчику", затем полученные
// данные передает "Хранителю" для сохранения на диск, затем посылает запрос
// в БД для удаления загруженной записи.

class Downloader : public QObject
{
  Q_OBJECT
public:
  explicit Downloader(QObject *parent = 0);

  // Инициализация.
  void initialize(const QString& root, int delay, int count, bool isSingleLoad);
  // Закачивает все треки в БД.
  void load();
  // Закачивает трек.
  void load(MediaInfo& media);
  // Останавливает закачивание.
  void stop();

signals:
  // Все загрузки завершены.
  void finished();


private slots:
  // Слот-реакция на сигнал от "Обработчика" о готовности ответа.
  // Получает данные из ответа и сохраняет на диск.
  void on_readyReply(const QString& href, QNetworkReply* reply);

  // Слот-реакция на сигнал от "Сохранителя" об успешности сохранения.
  void on_saved(MediaInfo &media);

  // Управляет прогрессом закачки.
  void on_downloadProgress(const QString& href,
                           qint64 bytesReceived,
                           qint64 bytesTotal);

private:
  // Запускает паузу.
  void pause(int max);


private:
  DownloadHandler* m_handler;
  Saver* m_saver;
  Model* m_model;

  QHash <QString, MediaInfo> m_mediaData;
  QHash <QString, QNetworkReply*> m_replies;
  QString m_root;                              // Корневой каталог.
  int m_countConcurrentLoads;                  // Количество одновременных загрузок.
  int m_indexNextLoad;                         // Индекс следующей загрузки.
  int m_delay;                                 // Задержка между запросами.
  bool m_stop;                                 // Остановлена загрузка?
  bool m_singleLoad;                           // Одиночная загрузка?
  QMutex m_mutex;

};

#endif // DOWNLOADER_H
