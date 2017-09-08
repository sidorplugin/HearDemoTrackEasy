#include "deejaydealbumfetcher.h"

#include <QWebElementCollection>

//*************************  DeejayDeAlbumFetcherPrivate  ****************************//

class DeejayDeAlbumFetcherPrivate
{
public:
  MediaInfo album;

public:
  // Возвращает ссылки на изображения релиза.
  QStringList getImages(const QWebElement &element);
  // Возвращает true если ссылка правильная.
  bool validateLinkImage(const QString& link);
  // Возвращает ссылку на трек.
  QString getLinkTrack(const QWebElement &element,
                       const QString& params = QString());
  // Возвращает название трека.
  QString getTitleTrack(const QWebElement &element);
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



// Возвращает ссылки на изображения релиза.
QStringList DeejayDeAlbumFetcherPrivate::getImages(const QWebElement &element)
{
  QStringList result;

  QWebElement imageElement_1 = element.findFirst("div.img.allbig.img1 a.noMod");
  QWebElement imageElement_2 = element.findFirst("div.img.allbig.img2 a.noMod");

  if (imageElement_1.isNull())
    imageElement_1 = element.findFirst("div.img.img1 a.noMod");

  QString link1 = imageElement_1.attribute("href");
  QString link2 = imageElement_2.attribute("href");

  if (validateLinkImage(link1)) {
    result << link1 << link2;
    return result;
  }
  else
    return QStringList();
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
QString DeejayDeAlbumFetcherPrivate::getTitleTrack(const QWebElement &element)
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


// Возвращает информацию об альбоме.
MediaInfo DeejayDeAlbumFetcher::getFetchedAlbum() const
{
  return p_d->album;
}


// Производит выборку.
void DeejayDeAlbumFetcher::result(bool ok)
{
  p_d->album.clear();

  QWebElement contentElement =
      m_page.mainFrame()->findFirstElement("article.single_product");

  // Считывает адрес на картинку (необходим для получения адреса на трек).
  QStringList images = p_d->getImages(contentElement);
  if (images.isEmpty()) {
    emit fetched(Fetcher::NoElements);
    return;
  }

  QString artist = p_d->getArtist(contentElement);
  QString title = p_d->getTitleRelease(contentElement);
  int id = qHash(artist + title);
  QString style = p_d->getStyle(contentElement);
  QString catalog = p_d->getCatalog(contentElement);
  QString label = p_d->getLabel(contentElement);
  QDate date = p_d->getDate(contentElement);

  // Определяет треклист релиза.
  QVariantHash tracks = getTrackList(QWebElement(), images.at(0));
  if (tracks.isEmpty()) {
    emit fetched(Fetcher::NoElements);
    return;
  }

  p_d->album.setData(MediaInfo::Id, id);
  p_d->album.setData(MediaInfo::Artist, artist);
  p_d->album.setData(MediaInfo::Title, title);
  p_d->album.setData(MediaInfo::Style, style);
  p_d->album.setData(MediaInfo::Catalog, catalog);
  p_d->album.setData(MediaInfo::Label, label);
  p_d->album.setData(MediaInfo::Date, date);
  p_d->album.setData(MediaInfo::Images, images);
  p_d->album.setData(MediaInfo::Tracks, tracks);
  p_d->album.setData(MediaInfo::Source, "DeejayDe");

  emit fetched(Fetcher::Finished);
}


// Возвращает треклист.
QVariantHash DeejayDeAlbumFetcher::getTrackList(const QWebElement &element,
                                               const QString& params)
{
  QVariantHash result;

  QWebElementCollection tracksCollection =
              m_page.mainFrame()->findAllElements("a.track");
  if (tracksCollection.count() == 0)
    return QVariantHash();

  foreach (QWebElement trackElement, tracksCollection) {
    QString link = p_d->getLinkTrack(trackElement, params);
    QString title = p_d->getTitleTrack(trackElement);
    result.insert(title, link);
  }

  return result;
}
