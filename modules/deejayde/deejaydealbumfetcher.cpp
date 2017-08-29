#include "deejaydealbumfetcher.h"

#include <QWebElementCollection>

//*************************  DeejayDeAlbumFetcherPrivate  ****************************//

class DeejayDeAlbumFetcherPrivate
{
public:
  QList <TrackInfo> trackInfoList;

public:
  // Возвращает ссылку на изображение релиза.
  QString getLinkImage(const QWebElement &element);
  // Возвращает true если ссылка правильная.
  bool validateLinkImage(const QString& link);
  // Возвращает ссылку на трек.
  QString getLinkTrack(const QWebElement &element,
                       const QString& params = QString());
  // Возвращает название трека.
  QString getTitle(const QWebElement &element);
  // Возвращает артиста.
  QString getArtist(const QWebElement &element);
  // Возвращает название релиза.
  QString getTitleRelease(const QWebElement &element);
  // Возвращает лэйбл.
  QString getLabel(const QWebElement &element);
  // Возвращает номер по каталогу.
  QString getCatalog(const QWebElement &element);
  // Возвращает дату релиза.
  QDate getDate(const QWebElement &element);
  // Возвращает стиль релиза.
  QString getStyle(const QWebElement &element);
};

// Возвращает ссылку на изображение релиза.
QString DeejayDeAlbumFetcherPrivate::getLinkImage(const QWebElement &element)
{
  QWebElement linkElement = element.findFirst("div.img.allbig.img1 a.noMod");
  if (linkElement.isNull())
    linkElement = element.findFirst("div.img.img1 a.noMod");

  QString href = linkElement.attribute("href");
  if (validateLinkImage(href))
    return href;
  else
    return QString();
}


// Возвращает ссылку на трек.
QString DeejayDeAlbumFetcherPrivate::getLinkTrack(const QWebElement &element,
                                                  const QString &params)
{
  QString href = "http://www.deejay.de/" + element.attribute("href");
  QString symbol = href.section("_", -1);
  QString result = "http://www.deejay.de/streamit/" + params.section("/", -3).
          replace(QString(".jpg"), symbol + QString(".mp3"));
  return result;
}


// Возвращает название трека.
QString DeejayDeAlbumFetcherPrivate::getTitle(const QWebElement &element)
{
  QString innerXml = element.toInnerXml();
  // Очищает строку от ненужных символов.
  QRegExp rx ("(<b>|</b>|<em>|</em>|<h5>|</h5>|&nbsp;|<strong>|</strong>)");
  QStringList list = innerXml.split(rx, QString::SkipEmptyParts);

  QString total;
  foreach(QString part, list) {
      total += part;
  }
  QString titleTrack = total.replace(QString(":"), QString("_"));

  return titleTrack.replace("&amp;", "&");
}


QString DeejayDeAlbumFetcherPrivate::getArtist(const QWebElement &element)
{
  QWebElement artistElement = element.findFirst("div.artist h1");
  return artistElement.toInnerXml().replace("&amp;", "&");
}


QString DeejayDeAlbumFetcherPrivate::getTitleRelease(const QWebElement &element)
{
  QWebElement titleElement = element.findFirst("div.title h1");
  return titleElement.toInnerXml().replace("&amp;", "&");
}


QString DeejayDeAlbumFetcherPrivate::getLabel(const QWebElement &element)
{
  QWebElement labelElement = element.findFirst("div.label h3");
  return labelElement.toInnerXml().replace("&amp;", "&");
}


QString DeejayDeAlbumFetcherPrivate::getCatalog(const QWebElement &element)
{
  QWebElement labelElement = element.findFirst("div.label h1");
  return labelElement.toInnerXml().replace("&amp;", "&");
}


bool DeejayDeAlbumFetcherPrivate::validateLinkImage(const QString &link)
{
  // Если путь к изображению не подходящий.
  if (link.section("/", -3).isEmpty()) {
    qDebug() << "linkImage validate false";
    return false;
  }

  return true;
}


// Возвращает дату релиза.
QDate DeejayDeAlbumFetcherPrivate::getDate(const QWebElement &element)
{
  QWebElement dateElement = element.findFirst("span.date");
  QString dateString = dateElement.toPlainText();
  QRegExp rx ("(\\d+).(\\d+).(\\d+)");
  int pos = rx.indexIn(dateString);
  QString date = rx.cap(0);

  return QDate::fromString(date, "dd.MM.yyyy");
}


// Возвращает стиль релиза.
QString DeejayDeAlbumFetcherPrivate::getStyle(const QWebElement &element)
{
  QWebElement styleElement = element.findFirst("div.styles a.main em");
  return styleElement.toPlainText();
}


//**************************  DeejayDeAlbumFetcher  *********************************//

DeejayDeAlbumFetcher::DeejayDeAlbumFetcher(QObject *parent)
{
  p_d = new DeejayDeAlbumFetcherPrivate;
}

DeejayDeAlbumFetcher::~DeejayDeAlbumFetcher()
{
  delete p_d;
}


// Возвращает список с выбранной информацией о треках.
QList<TrackInfo> DeejayDeAlbumFetcher::getFetchedTrackInfoList() const
{
  return p_d->trackInfoList;
}


// Производит выборку.
void DeejayDeAlbumFetcher::result(bool ok)
{
  p_d->trackInfoList.clear();

  QWebElement contentElement =
      m_page.mainFrame()->findFirstElement("article.single_product");

  // Считывает адрес на картинку (необходим для получения адреса на трек).
  QString linkImage = p_d->getLinkImage(contentElement);
  if (linkImage.isEmpty()) {
    emit fetched(Fetcher::NoElements);
    return;
  }

  QDate date = p_d->getDate(contentElement);
  QString artist = p_d->getArtist(contentElement);
  QString album = p_d->getTitleRelease(contentElement);
  QString label = p_d->getLabel(contentElement);
  QString catalog = p_d->getCatalog(contentElement);
  QString style = p_d->getStyle(contentElement);

  // Определяет треклист релиза.
  QStringList trackList = getTrackList(QWebElement(), linkImage);
  if (trackList.isEmpty()) {
    emit fetched(Fetcher::NoElements);
    return;
  }

  for(int i = 0; i < trackList.size(); i = i + 2) {
      TrackInfo track;
      track.setData(TrackInfo::LinkTrack, trackList.at(i));
      track.setData(TrackInfo::Title, trackList.at(i + 1));
      track.setData(TrackInfo::Style, style);
      track.setData(TrackInfo::Artist, artist);
      track.setData(TrackInfo::Album, album);
      track.setData(TrackInfo::Catalog, catalog);
      track.setData(TrackInfo::Label, label);
      track.setData(TrackInfo::Date, date);
      track.setData(TrackInfo::LinkImage, linkImage);
      track.setData(TrackInfo::Source, "DeejayDe");

      p_d->trackInfoList.push_back(track);
  }

  emit fetched(Fetcher::Finished);
}


// Возвращает треклист.
QStringList DeejayDeAlbumFetcher::getTrackList(const QWebElement &element,
                                               const QString& params)
{
  QStringList result;
  QStringList list;

  QWebElementCollection tracksCollection =
              m_page.mainFrame()->findAllElements("a.track");
  if (tracksCollection.count() == 0)
    return QStringList();

  foreach (QWebElement trackElement, tracksCollection) {
    QString hrefMp3 = p_d->getLinkTrack(trackElement, params);
    QString titleTrack = p_d->getTitle(trackElement);
    list << hrefMp3 << titleTrack;
    result << list;
    list.clear();
  }

  return result;
}
