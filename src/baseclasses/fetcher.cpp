#include "baseclasses/fetcher.h"

Fetcher::Fetcher(QObject *parent) : QObject(parent)
{
  m_manager = new QNetworkAccessManager(this);
  connect(m_manager, &QNetworkAccessManager::finished, [=] (QNetworkReply* reply) {
      int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
      // Проверяет статус полученного ответа.
      switch (statusCode) {
        case 301:
        case 302:
        case 307:
        {  // Имеется редирект ссылка.
          qDebug() << "301 302 307 redirect";
          QString redirectUrl =
              reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl().toString();
          load(redirectUrl);
          break;
        }
        case 200:
        {
          qDebug() << "200 Ok";
          fetch(reply);
          break;
        }
      }
  });
}

Fetcher::~Fetcher()
{
}


// Загружает страницу с данным url.
void Fetcher::load(const QString& url)
{
  qDebug() << "Fetcher::load(" << url << ")";
  m_url = url;
  m_manager->get(QNetworkRequest(QUrl(url)));
}
