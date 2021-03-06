#ifndef HARDWAXPAGESEARCHER_H
#define HARDWAXPAGESEARCHER_H

#include "baseclasses/pagesearcher.h"

#include <QObject>
#include <QDebug>
#include <QEventLoop>

class HardwaxPageSearcher : public PageSearcher
{
public:
  QList<int> getPagesInfo(const QVariantList &params);

protected slots:
  void fetch(QNetworkReply* reply);

private:
  int m_endPage;

};

#endif // HARDWAXPAGESEARCHER_H
