#include "downloader.h"
#include "database.h"

Downloader::Downloader(QObject *parent) : QObject(parent),
                                          m_isStoped(false),
                                          m_isStarted(false),
                                          m_indexNextTrack(0)
{
  // Создает экземпляры объектов Обработчик,Cохранитель и БД.
  m_handler = new DownloadHandler;
  m_saver = new Saver;
  m_model = Database::getInstance()->model();

  // Когда приходит ответ от "Обработчика" с загруженными сырыми данными,
  // отправляет данные для сохранения "Хранителю".
  connect(m_handler, SIGNAL(readyReply(QString, QNetworkReply*)),
          this, SLOT(on_readyReply(QString, QNetworkReply*)));

  // Когда приходит ответ от "Обработчика" об изменении прогреса в загрузке,
  // изменяет значения в соответствующих полях БД.
  connect(m_handler, SIGNAL(downloadProgress(QString, qint64, qint64)),
          this, SLOT(on_downloadProgress(QString, qint64, qint64)));

  // Когда приходит ответ от "Хранителя" об успешном сохранении файла,
  // отправляет запрос в БД на удаление записи.
  connect(m_saver, SIGNAL(saved(TrackInfo&)),
          this, SLOT(on_saved(TrackInfo&)));

}


// Инициализация.
void Downloader::initialize(const QString &root, int delay,
                            int count, bool isSingleLoad)
{
  m_countTasksInLoad = count;
  m_delay = delay;
  m_root = root;
  m_isSingleLoad = isSingleLoad;
}


// Закачивает все треки в БД.
void Downloader::load()
{
  qDebug() << "Downloader::loadAll";

  // Пока в БД не пуста или процесс не остановлен пользователем, закачивает треки.
  while (!m_model->isEmpty() && !m_isStoped) {
    // Если закачивание только началось отправляет Обработчику
    // m_countTasksInLoad задач.
    if (!m_isStarted) {
        m_isStarted = true;
        // Передает m_countTasksInLoad задач на исполнение "Обработчику".
        for (int i = 0; i < m_countTasksInLoad; i++) {
            // TODO найти трек по i getTrackInfo(i). => load(track).
            TrackInfo track = m_model->getTrackInfo(i);
            load(track);
        }
    }
    // Иначе, отправляет Обработчику очередную m_indexNextTrack задачу.
    else {
        TrackInfo track = m_model->getTrackInfo(m_indexNextTrack);
        load(track);
    }

    // Не выходит из QEventLoop пока не получит сигнал о завершении задачи.
    QEventLoop wait;
    connect(this, SIGNAL(loaded()),
            &wait, SLOT(quit()));
    wait.exec();
  }

  emit finished();
}


// Закачивает трек.
void Downloader::load(TrackInfo &track)
{
  qDebug() << "Downloader::load(TrackInfo)"
           << track.data(TrackInfo::Title).toString();

  // Сохраняет инфо о треке в таблице.
  m_tracksData.insert(track.data(TrackInfo::Link).toString(), track);
  // Отправляет задание "Обработчику".
  m_handler->load(track.data(TrackInfo::Link).toString());
  // Увеличивает индекс на 1, указывающий на следующую запись для загрузки.
  m_indexNextTrack++;

  if (m_isSingleLoad)
      emit finished();
}



// Останавливает закачивание.
void Downloader::stop()
{
  qDebug() << "Downloader::stop()";

  // Устанавливает флаг останова в true и флаг старта в false.
  m_isStoped = true;
  m_isStarted = false;
  // Останавливает Обработчик.
  m_handler->stop();

}


// Управляет прогрессом закачки.
void Downloader::on_downloadProgress(const QString& href,
                                     qint64 bytesReceived,
                                     qint64 bytesTotal)
{
  qDebug() << "Downloader::on_downloadProgress()" << href;

  int percent = (bytesReceived * 100) / bytesTotal;
  qDebug() << "progress = " << percent;

  m_model->setProgress(href, percent);
}


// Слот-реакция на сигнал от "Обработчика" о готовности ответа. Снабжает
// полученный reply данными о треке и путем сохранения, далее передает
// "Сохранителю" для сохранения на диск.
void Downloader::on_readyReply(const QString &href, QNetworkReply* reply)
{
  qDebug() << "Downloader::on_readyReply()" << href;

  // Вычленяет данные из ответа.
  QByteArray byteData = reply->readAll();

  // Получает данные о треке по ссылке href.
  TrackInfo trackData = m_tracksData.take(href);

  // Передает "Сохранителю" данные для сохранения на диск.
  m_saver->save(byteData, trackData, m_root);

}


// Слот-реакция на сигнал от "Сохранителя" об успешности сохранения.
void Downloader::on_saved(TrackInfo &track)
{
  qDebug() << "Downloader::on_saved()" << track.data(TrackInfo::Link).toString();

  // Удаляет из БД запись.
  m_model->remove(track);

  // Уменьшает на 1 индекс, указывающий на следующий загружаемый трек в БД.
  m_indexNextTrack--;

  emit loaded();
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