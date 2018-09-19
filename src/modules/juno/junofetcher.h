#ifndef JUNOFETCHER_H
#define JUNOFETCHER_H

#include "baseclasses/fetcher.h"

#include <QObject>

class JunoFetcherPrivate;

class JunoFetcher : public Fetcher
{
public:
  JunoFetcher(QObject *parent = 0);
  ~JunoFetcher();

protected slots:
  void fetch(QNetworkReply* reply);

private:
  void handleElement(const HtmlElement &element);

private:
  JunoFetcherPrivate* p_d;

};

#endif // JUNOFETCHER_H
