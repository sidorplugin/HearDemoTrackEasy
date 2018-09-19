#include "junopagesearcher.h"

void JunoPageSearcher::fetch(QNetworkReply* reply)
{
  QString html = reply->readAll();
  HtmlElement root(html);

  if (reply->error() != QNetworkReply::NoError) {
      qDebug() << "error reply" << reply->errorString();
      return;
  }

  HtmlElement pageElement = root.findFirst("div.col-12 col-lg-4 text-center text-lg-left");

  if (pageElement.isEmpty()) {
    return;
  }

  QRegExp prepareRx ("of[ 1-999]");
  QString str = pageElement.toPlainText();
  m_endPage = str.section(prepareRx, -1, -1).toInt();

  reply->deleteLater();
  emit finished();
}



QList<int> JunoPageSearcher::getPagesInfo(const QVariantList &params)
{
  QString link = params.at(0).toString();

  load(link.arg("1"));

  // Остается в цикле пока не произведется выборка.
  QEventLoop wait;
  connect(this, SIGNAL(finished()), &wait, SLOT(quit()));
  wait.exec();

  QList<int> result;
  result << 1 << m_endPage << m_endPage;

  return result;
}
