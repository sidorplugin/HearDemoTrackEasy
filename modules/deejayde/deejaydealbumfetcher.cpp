#include "deejaydealbumfetcher.h"

#include <QWebElementCollection>

//*************************  DeejayDeAlbumFetcherPrivate  ****************************//

class DeejayDeAlbumFetcherPrivate
{
public:
  MediaInfo media;

public:
  // Возвращает ссылки на изображения релиза.
  QString getImages(const QWebElement &element);
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
  // Возвращает уникальный id строк catalog и label.
  int getUniqueId(const QString& catalog, const QString& label);
};



// Возвращает ссылки на изображения релиза.
QString DeejayDeAlbumFetcherPrivate::getImages(const QWebElement &element)
{
  QString result;
  QString baseAddress = "http://www.deejay.de";


  QWebElement imageElement_1 = element.findFirst("div.img.allbig.img1 a.noMod");
  QWebElement imageElement_2 = element.findFirst("div.img.allbig.img2 a.noMod");

  if (imageElement_1.isNull()) {
    imageElement_1 = element.findFirst("div.img.img1 a.noMod");
    return baseAddress + imageElement_1.attribute("href");
  }

  QString link1 = imageElement_1.attribute("href");
  QString link2 = imageElement_2.attribute("href");

  if (validateLinkImage(link1)) {
    result = baseAddress + link1 + ";" + baseAddress + link2;
    return result;
  }
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
QString DeejayDeAlbumFetcherPrivate::getTitleTrack(const QWebElement &element)
{
  QString title = element.toInnerXml();
  return title.replace("&amp;", "&");
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
  return styleElement.toInnerXml();
}


// Возвращает уникальный id строк catalog и label.
int DeejayDeAlbumFetcherPrivate::getUniqueId(const QString& catalog,
                                        const QString& label)
{
  QString firstWordLabel = label.split(" ").at(0);
  QString prepareString = QString(catalog + firstWordLabel).toLower();
  // Регулярное выражение - все знаки и пробел.
  QRegExp rx ("[ ,_.;:'%`!-\$<>()&#\^\"\\/]");
  prepareString.remove(rx);

  return qHash(prepareString);
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
MediaInfo DeejayDeAlbumFetcher::getFetchedMedia() const
{
  return p_d->media;
}


// Производит выборку.
void DeejayDeAlbumFetcher::result(bool ok)
{
  p_d->media.clear();

  QWebElement contentElement =
      m_page.mainFrame()->findFirstElement("article.single_product");

  // Считывает адрес на картинку (необходим для получения адреса на трек).
  QString images = p_d->getImages(contentElement);
  if (images.isEmpty()) {
    emit fetched(Fetcher::NoElements);
    return;
  }

  QString artist = p_d->getArtist(contentElement);
  QString title = p_d->getTitleRelease(contentElement);  
  QString style = p_d->getStyle(contentElement);
  QString catalog = p_d->getCatalog(contentElement);
  QString label = p_d->getLabel(contentElement);
  int id = p_d->getUniqueId(catalog, label);
  QDate date = p_d->getDate(contentElement);

  // Определяет треклист релиза.
  QVariantHash tracks = getTrackList(id, QWebElement(), images.split(";").at(0));
  if (tracks.isEmpty()) {
    emit fetched(Fetcher::NoElements);
    return;
  }

  p_d->media.setData(MediaInfo::Id_Album, id);
  p_d->media.setData(MediaInfo::Artist, artist);
  p_d->media.setData(MediaInfo::Title_Album, title);
  p_d->media.setData(MediaInfo::Style, style);
  p_d->media.setData(MediaInfo::Catalog, catalog);
  p_d->media.setData(MediaInfo::Label, label);
  p_d->media.setData(MediaInfo::Date, date);
  p_d->media.setData(MediaInfo::Images, images);
  p_d->media.setData(MediaInfo::Link_Album, url());
  p_d->media.setData(MediaInfo::Source, "DeejayDe");
  p_d->media.setData(MediaInfo::Tracks, tracks);

  emit fetched(Fetcher::Finished);
}


// Возвращает треклист.
QVariantHash DeejayDeAlbumFetcher::getTrackList(int id, const QWebElement &element,
                                               const QString& params)
{
  QVariantHash result;

  QWebElementCollection tracksCollection =
              m_page.mainFrame()->findAllElements("a.track");
  if (tracksCollection.count() == 0)
    return QVariantHash();

  int idTrack = id;
  foreach (QWebElement trackElement, tracksCollection) {
    QString link = p_d->getLinkTrack(trackElement, params);
    QString title = p_d->getTitleTrack(trackElement.findFirst("h5"));
    result.insert(QString::number(idTrack++), QStringList() << title << link);
  }

  return result;
}
