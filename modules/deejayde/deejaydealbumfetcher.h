#ifndef DEEJAYDEALBUMFETCHER_H
#define DEEJAYDEALBUMFETCHER_H

#include "baseclasses/fetcher.h"

#include <QObject>
#include <QWebElement>

class DeejayDeAlbumFetcherPrivate;

class DeejayDeAlbumFetcher : public Fetcher
{
public:
  DeejayDeAlbumFetcher(QObject *parent = 0);
  ~DeejayDeAlbumFetcher();

  // Возвращает информацию об альбоме.
  AlbumInfo getFetchedAlbum() const;

protected slots:
  // Производит выборку.
  void result(bool ok);

private:
  // Возвращает треклист.
  QVariantHash getTrackList(const QWebElement& element,
                           const QString& params = QString());

private:
  DeejayDeAlbumFetcherPrivate* p_d;  
  QString m_genre;

};

#endif // DEEJAYDEALBUMFETCHER_H
