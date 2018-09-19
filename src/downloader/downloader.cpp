#include "downloader.h"
#include "database.h"

Downloader::Downloader(QObject *parent) : QObject(parent),
                                          m_stop(false),
                                          m_indexNextLoad(0),
                                          m_handler(new DownloadHandler),
                                          m_saver(new Saver),
                                          m_model(Database::getInstance()->model())
{
  // Когда приходит ответ от "Обработчика" с загруженными сырыми данными,
  // отправляет данные для сохранения "Хранителю".
  connect(m_handler, SIGNAL(readyReply(QString, QNetworkReply*)),
          this, SLOT(on_readyReply(QString, QNetworkReply*)));

  // Когда приходит ответ от "Обработчика" об изменении прогреса в загрузке,
  // изменяет значения в соответствующих полях БД.
  connect(m_handler, SIGNAL(downloadProgress(QString, qint64, qint64)),
          this, SLOT(on_downloadProgress(QString, qint64, qint64)));

  // Когда приходит ответ от "Хранителя" об успешном сохранении файла,
  // отправляет запрос о загруженности.
  connect(m_saver, SIGNAL(saved(MediaInfo&)),
          this, SLOT(on_saved(MediaInfo&)));

}


// Инициализация.
void Downloader::initialize(const QString &root, int delay,
                            int count, bool isSingleLoad)
{
  m_countConcurrentLoads = count;
  m_delay = delay;
  m_root = root;
  m_singleLoad = isSingleLoad;
}


// Закачивает все треки в БД.
void Downloader::load()
{
  qDebug() << "Downloader::loadAll";

  m_stop = false;
  if (m_countConcurrentLoads <= m_model->rowCount()) {
      for (int i = 0; i < m_countConcurrentLoads; i++) {
          MediaInfo media = m_model->mediaInfo(i);
          load(media);
      }
  }
  else {
      MediaInfo media = m_model->mediaInfo(m_indexNextLoad);
      load(media);
  }
}


// Закачивает трек.
void Downloader::load(MediaInfo &media)
{
  qDebug() << "Downloader::load(MediaInfo)";

  // Сохраняет инфо о треке в таблице.
  m_mediaData.insert(media.data(MediaInfo::Link_Track).toString(), media);
  // Отправляет задание "Обработчику".
  m_handler->load(media.data(MediaInfo::Link_Track).toString());

  m_mutex.lock();
  m_indexNextLoad++;
  m_mutex.unlock();
}


// Останавливает закачивание.
void Downloader::stop()
{
  qDebug() << "Downloader::stop()";

  // Устанавливает флаг останова в true
  m_stop = true;
  // Останавливает Обработчик.
  m_handler->stop();
}


// Управляет прогрессом закачки.
void Downloader::on_downloadProgress(const QString& href,
                                     qint64 bytesReceived,
                                     qint64 bytesTotal)
{
  int percent = (bytesReceived * 100) / bytesTotal;
  m_model->setProgress(href, percent);
}


// Слот-реакция на сигнал от "Обработчика" о готовности ответа.
// Получает данные из ответа и сохраняет на диск.
void Downloader::on_readyReply(const QString &href, QNetworkReply* reply)
{
  qDebug() << "Downloader::on_readyReply()" << href;

  // Получает данные из ответа.
  QByteArray byteData = reply->readAll();

  // Получает данные о треке по ссылке href.
  MediaInfo media = m_mediaData.take(href);

  // Сохраняет данные.
  m_saver->save(byteData, media, m_root);
}


// Слот-реакция на сигнал от "Сохранителя" об успешности сохранения.
void Downloader::on_saved(MediaInfo &media)
{
   qDebug() << "Downloader::on_saved()" << media.data(MediaInfo::Link_Track).toString();
   // Проверяет модель на возможно большее количество элементов.
   // (QAbstractItemModel->rowCount() возвращает 256 элементов, если в модели
   // больше элементов необходимо использовать fetchMore()).
   if (m_model->canFetchMore())
       m_model->fetchMore();
   // Проверяет модель на наличие треков.
   if (m_indexNextLoad <= m_model->rowCount() && !m_singleLoad && !m_stop) {
       MediaInfo m = m_model->mediaInfo(m_indexNextLoad);
       load(m);
   }
   else {
       finished();
   }
}


// Запускает паузу.
void Downloader::pause(int max)
{
  if (max == 0)
    return;

  int num = 3 + qrand() % (max - 3);
  qDebug() << "pause = " << num;

  QEventLoop wait;
  QTimer::singleShot(num * 1000, &wait, SLOT(quit()));
  wait.exec();
}
