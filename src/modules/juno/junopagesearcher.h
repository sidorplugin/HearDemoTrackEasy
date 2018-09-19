#ifndef JUNOPAGESEARCHER_H
#define JUNOPAGESEARCHER_H

#include "baseclasses/pagesearcher.h"

#include <QObject>
#include <QDebug>
#include <QEventLoop>

class JunoPageSearcher : public PageSearcher
{
public:
  QList<int> getPagesInfo(const QVariantList &params);


protected slots:
  void fetch(QNetworkReply* reply);

private:
  int m_endPage;

};

#endif // JUNOPAGESEARCHER_H
