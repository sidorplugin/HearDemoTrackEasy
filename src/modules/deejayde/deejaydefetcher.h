#ifndef DEEJAYDEFETCHER_H
#define DEEJAYDEFETCHER_H

#include "baseclasses/fetcher.h"

#include <QDebug>
#include <QObject>
#include <QEventLoop>

class DeejayDeFetcherPrivate;

class DeejayDeFetcher : public Fetcher
{
public:
  DeejayDeFetcher(QObject *parent = 0);
  ~DeejayDeFetcher();

protected slots:
  void fetch(QNetworkReply* reply);

private:
  void handleElement(const HtmlElement &element);

private:
  DeejayDeFetcherPrivate* p_d;

};

#endif // DEEJAYDEFETCHER_H
