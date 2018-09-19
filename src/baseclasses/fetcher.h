#ifndef FETCHER_H
#define FETCHER_H

#include "baseclasses/htmlelement.h"
#include "dataclasses/mediainfo.h"

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

// Базовый класс, осуществляющий выборку данных с сайта.
class Fetcher : public QObject
{
  Q_OBJECT
public:
  explicit Fetcher(QObject *parent = 0);
  ~Fetcher();

  void load(const QString& url);
  void stop() { m_isStop = true; }
  QString url() { return m_url; }
  QList <MediaInfo> data() { return m_data; }

  // Возвращает уникальный id строк catalog и label.
  int getUniqueId(const QString &catalog, const QString &label)
  {
    QString digitalPartCatalog;
    QString firstWordLabel = label.split(" ").at(0);
    QRegExp rxDigital ("(\\d+)");
    int pos = rxDigital.indexIn(catalog);
    if (pos > -1)
      digitalPartCatalog = rxDigital.cap();

    // Hardwax id enabled record.
  //  QString prepareString = QString(firstWordLabel + digitalPartCatalog).toLower();
    QString prepareString = QString(catalog + firstWordLabel).toLower();
    // Регулярное выражение - все знаки и пробел.
    QRegExp rx ("[ ,_.;:'%`!-\$<>()&#\^\"\\/]");
    prepareString.remove(rx);

    return qHash(prepareString);
  }

public slots:
  virtual void fetch(QNetworkReply* reply) = 0;

signals:
  void signalLoad(const QString& url);
  void finished();
  void stopped();

protected:
  QNetworkAccessManager* m_manager;
  QString m_url;
  QList <MediaInfo> m_data;
  bool m_isStop;
};

#endif // FETCHER_H
