#ifndef DEEJAYDEFETCHER_H
#define DEEJAYDEFETCHER_H

#include "baseclasses/fetcher.h"
#include "deejaydealbumfetcher.h"

#include <QDebug>
#include <QObject>
#include <QWebElementCollection>
#include <QEventLoop>

class DeejayDeFetcherPrivate;

class DeejayDeFetcher : public Fetcher
{
public:
  DeejayDeFetcher(QObject *parent = 0);
  ~DeejayDeFetcher();

  void setAlbumFetcher(DeejayDeAlbumFetcher* fetcher);
  void setGenre(const QString& genre) { m_genre = genre; }

protected slots:
  void result(bool ok);

private:
  void handleElement(const QWebElement &element);

private:
  DeejayDeFetcherPrivate* p_d;
  QString m_genre;

};

#endif // DEEJAYDEFETCHER_H
