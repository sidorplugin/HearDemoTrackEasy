#include "downloadhandler.h"

DownloadHandler::DownloadHandler()
{
  m_isStoped = false;

  m_networkManager = new QNetworkAccessManager();
  m_mapper = new QSignalMapper;

  connect(m_mapper, SIGNAL(mapped(QString)),
          this, SLOT(on_finished(QString)));
}


// Загружает файл с данным href.
void DownloadHandler::load(const QString &href)
{
  qDebug() << "DownloadHandler::load()";

  m_isStoped = false;

  QNetworkReply* reply = m_networkManager->get(QNetworkRequest(QUrl(href)));

  connect(reply, SIGNAL(downloadProgress(qint64,qint64)),
          this, SLOT(on_downloadProgress(qint64,qint64)));

  connect(reply, SIGNAL(finished()), m_mapper, SLOT(map()));

  m_repliesTable.insert(href, reply);

  m_mapper->setMapping(reply, href);
}


// Останавливает загрузку файлов.
void DownloadHandler::stop()
{
  m_isStoped = true;

  // Проходит по всем reply, останавливает их и помечает на удаление.
  QHashIterator <QString, QNetworkReply*> i(m_repliesTable);
  while (i.hasNext()) {
      i.next();
      QNetworkReply* reply = i.value();
      reply->abort();
      reply->deleteLater();
  }
}


// Слот. По завершению загрузки отправляет результат.
void DownloadHandler::on_finished(const QString& href)
{
  qDebug() << "DownloadHandler::on_finished()" << href;

  if (m_isStoped)
    return;

  QNetworkReply* reply = m_repliesTable.take(href);

  if (!reply)
    return;

  int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

  // Проверяет статус полученного ответа.
  switch (statusCode) {
    case 301:
    case 302:
    case 307: {  // Имеется редирект ссылка.
      qDebug() << "301 302 307 redirect";
      // Извлекает редирект ссылку из reply.
      QUrl redirectUrl = reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();
      QString redirectHref = redirectUrl.toString();

      // Сохраняет редирект ссылку в таблицу соответствия с изначальным href.
      m_redirectHrefTable.insert(redirectHref, href);

      // Производит загрузку по редирект ссылке.
      load(redirectHref);
      break;
    }

    case 200: {   // Успешная загрузка.
      qDebug() << "200 ok";

      // Извлекает редирект ссылку из таблицы.
      QString originalHref = m_redirectHrefTable.take(href);
      qDebug() << originalHref;

      // Оповещает о готовности результата.
      if (!originalHref.isEmpty())
        emit readyReply(originalHref, reply);
      else
        emit readyReply(href, reply);

      break;
    }

    case 404: {  // Трек не найден.
      qDebug() << "404 track not found";

      // Удаляет ссылку из таблицы редиректов.
      m_redirectHrefTable.remove(href);

      // Посылает сигнал об ошибке.
      emit error(href);

      // Ставит ответ в очередь на удаление.
      reply->deleteLater();
      break;
    }

  }
}


// Слот. Оповещает о прогрессе в закачке.
void DownloadHandler::on_downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
  QString href;

  if (m_isStoped)
    return;

  QNetworkReply* reply = qobject_cast<QNetworkReply*>(QObject::sender());

  if (reply) {
      href = m_repliesTable.key(reply);

      // Проверяет ссылку является ли она редиректом.
      QString originalHref = m_redirectHrefTable.value(href);
      if (originalHref.isEmpty())
        emit downloadProgress(href, bytesReceived, bytesTotal);
      else
        emit downloadProgress(originalHref, bytesReceived, bytesTotal);
  }
}

