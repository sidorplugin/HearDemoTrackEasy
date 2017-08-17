#ifndef HARDWAXFETCHER_H
#define HARDWAXFETCHER_H

#include "baseclasses/fetcher.h"

#include <QObject>
#include <QWebElementCollection>

class HardwaxFetcherPrivate;

class HardwaxFetcher : public Fetcher
{
public:
  HardwaxFetcher(QObject* parent = 0);
  ~HardwaxFetcher();

protected slots:
  // Производит выборку.
  void result(bool ok);

private:
  HardwaxFetcherPrivate* p_d;

};

#endif // HARDWAXFETCHER_H
