#ifndef PAGESEARCHER_H
#define PAGESEARCHER_H

#include "baseclasses/fetcher.h"

#include <QObject>

const int ANCHOR = 20;

class PageSearcher : public Fetcher
{
public:
  enum Page { StartPage,
              EndPage,
              TotalPages };

  PageSearcher();

  virtual QList<int> getPagesInfo(const QVariantList& params) = 0;

private:

};

#endif // PAGESEARCHER_H
