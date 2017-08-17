#include "hardwaxpagesearcher.h"

void HardwaxPageSearcher::result(bool ok)
{
  QWebElement pageElement = m_page.mainFrame()->findFirstElement("div#headline");

  if (pageElement.isNull()) {
    emit fetched(Fetcher::NoElements);
    return;
  }

  QRegExp prepareRx ("[(]|[)]");
  QString str = pageElement.toPlainText();
  m_endPage = str.section(prepareRx, 1, 1).section("/", 1).toInt();

  emit fetched(Fetcher::Finished);
}




QList<int> HardwaxPageSearcher::getPagesInfo(const QVariantList &params)
{
  QString link = params.at(0).toString();

  start(link + "1");

  // Остается в цикле пока не произведется выборка.
  QEventLoop wait;
  connect(this, SIGNAL(fetched(Fetcher::State)),
          &wait, SLOT(quit()));
  wait.exec();

  QList<int> result;
  result[PageSearcher::StartPage] = 1;
  result[PageSearcher::EndPage] = m_endPage;
  result[PageSearcher::TotalPages] = m_endPage;
  return result;

}
