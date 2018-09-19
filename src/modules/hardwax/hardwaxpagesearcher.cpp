#include "hardwaxpagesearcher.h"

void HardwaxPageSearcher::fetch(QNetworkReply* reply)
{
  QString html = reply->readAll();
  HtmlElement root(html);

  if (reply->error() != QNetworkReply::NoError) {
      qDebug() << "error reply" << reply->errorString();
      return;
  }

  HtmlElement pageElement = root.findAll("div.fleft").at(1);

  if (pageElement.isEmpty()) {
    return;
  }

  QRegExp prepareRx ("[(](\\d+)/(\\d+)[)]");
  QString str = pageElement.toPlainText();
  prepareRx.indexIn(str);
  QString pages = prepareRx.cap();
  m_endPage = pages.section("/", 1).remove(")").toInt();

  reply->deleteLater();
  emit finished();
}




QList<int> HardwaxPageSearcher::getPagesInfo(const QVariantList &params)
{
  QString link = params.at(0).toString();

  load(link.arg("1"));

  // Остается в цикле пока не произведется выборка.
  QEventLoop wait;
  connect(this, SIGNAL(finished()),
          &wait, SLOT(quit()));
  wait.exec();

  QList<int> result;
  result.append(1);
  result.append(m_endPage);
  result.append(m_endPage);
  return result;

}
