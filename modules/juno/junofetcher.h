#ifndef JUNOFETCHER_H
#define JUNOFETCHER_H

#include "baseclasses/fetcher.h"

#include <QObject>
#include <QWebElementCollection>

class JunoFetcherPrivate;

class JunoFetcher : public Fetcher
{
public:
  JunoFetcher(QObject *parent = 0);
  ~JunoFetcher();

protected slots:
  // Производит выборку.
  void result(bool ok);

private:
  void handleElement(const QWebElement &element);

private:
  JunoFetcherPrivate* p_d;

};

#endif // JUNOFETCHER_H
