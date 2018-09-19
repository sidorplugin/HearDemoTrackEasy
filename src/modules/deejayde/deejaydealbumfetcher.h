#ifndef DEEJAYDEALBUMFETCHER_H
#define DEEJAYDEALBUMFETCHER_H

#include "baseclasses/fetcher.h"

#include <QObject>

class DeejayDeAlbumFetcherPrivate;

class DeejayDeAlbumFetcher : public Fetcher
{
public:
  DeejayDeAlbumFetcher(QObject *parent = 0);
  ~DeejayDeAlbumFetcher();

  // Возвращает информацию об альбоме.
  MediaInfo getFetchedMedia() const;
  void setDateGroup(const QDate& date);

protected slots:
    void fetch(QNetworkReply* reply);

private:
  // Возвращает треклист.
  QVariantHash getTrackList(int id, const HtmlElement& element,
                           const QString& params = QString());

private:
  DeejayDeAlbumFetcherPrivate* p_d;  
  QString m_genre;

};

#endif // DEEJAYDEALBUMFETCHER_H
