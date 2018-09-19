#include "deejaydealbumfetcher.h"

//*************************  DeejayDeAlbumFetcherPrivate  ****************************//

class DeejayDeAlbumFetcherPrivate
{
public:
  MediaInfo media;
  QDate dateGroup;

public:
  // Возвращает ссылки на изображения релиза.
  QString getImages(const HtmlElement &element);
  // Возвращает true если ссылка правильная.
  bool validateLinkImage(const QString& link);
  // Возвращает ссылку на трек.
  QString getLinkTrack(const HtmlElement &element,
                       const QString& params = QString());
  // Возвращает название трека.
  QString getTitleTrack(const HtmlElement &element);
  // Возвращает артиста.
  QString getArtist(const HtmlElement &element);
  // Возвращает название релиза.
  QString getTitleRelease(const HtmlElement &element);
  // Возвращает лэйбл.
  QString getLabel(const HtmlElement &element);
  // Возвращает номер по каталогу.
  QString getCatalog(const HtmlElement &element);
  // Возвращает дату релиза.
  QDate getDate(const HtmlElement &element);
  // Возвращает стиль релиза.
  QString getStyle(const HtmlElement &element);
};



// Возвращает ссылки на изображения релиза.
QString DeejayDeAlbumFetcherPrivate::getImages(const HtmlElement &element)
{
  QString result;
  QString baseAddress = "https://www.deejay.de";


  HtmlElement imageElement_1 = element.findFirst("div.img allbig img1"); //"div.img.allbig.img1 a.noMod"
  imageElement_1 = imageElement_1.findFirst("a.noMod");
  HtmlElement imageElement_2 = element.findFirst("div.img allbig img2"); //"div.img.allbig.img2 a.noMod"
  imageElement_2 = imageElement_2.findFirst("a.noMod");

  if (imageElement_1.isEmpty()) {
    imageElement_1 = element.findFirst("div.img img1"); // "div.img.img1 a.noMod"
    imageElement_1 = imageElement_1.findFirst("a.noMod");
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
QString DeejayDeAlbumFetcherPrivate::getLinkTrack(const HtmlElement &element,
                                                  const QString &params)
{
  QString href = "http://www.deejay.de/" + element.attribute("href");
  QString symbol = href.section("_", -1);
  QString result = "http://www.deejay.de/streamit/" + params.section("/", -3).
          replace(QString(".jpg"), symbol + QString(".mp3"));
  return result;
}


// Возвращает название трека.
QString DeejayDeAlbumFetcherPrivate::getTitleTrack(const HtmlElement &element)
{
  QString title = element.toPlainText();
  return title.replace("&amp;", "&");
}


QString DeejayDeAlbumFetcherPrivate::getArtist(const HtmlElement &element)
{
  HtmlElement artistElement = element.findFirst("div.artist"); // "div.artist h1"
  artistElement = artistElement.findFirst("h1");
  return artistElement.toPlainText().replace("&amp;", "&");
}


QString DeejayDeAlbumFetcherPrivate::getTitleRelease(const HtmlElement &element)
{
  HtmlElement titleElement = element.findFirst("div.title"); //"div.title h1"
  titleElement = titleElement.findFirst("h1");
  return titleElement.toPlainText().replace("&amp;", "&");
}


QString DeejayDeAlbumFetcherPrivate::getLabel(const HtmlElement &element)
{
  HtmlElement labelElement = element.findFirst("div.label"); // "div.label h3"
  labelElement = labelElement.findFirst("h3");
  return labelElement.toPlainText().replace("&amp;", "&");
}


QString DeejayDeAlbumFetcherPrivate::getCatalog(const HtmlElement &element)
{
  HtmlElement labelElement = element.findFirst("div.label"); //"div.label h1"
  labelElement = labelElement.findFirst("h1");
  return labelElement.toPlainText().replace("&amp;", "&");
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
QDate DeejayDeAlbumFetcherPrivate::getDate(const HtmlElement &element)
{
  HtmlElement dateElement = element.findFirst("span.date");
  QString dateString = dateElement.toPlainText();
  QRegExp rx ("(\\d+).(\\d+).(\\d+)");
  int pos = rx.indexIn(dateString);
  QString date = rx.cap(0);

  return QDate::fromString(date, "dd.MM.yyyy");
}


// Возвращает стиль релиза.
QString DeejayDeAlbumFetcherPrivate::getStyle(const HtmlElement &element)
{
  HtmlElement styleElement = element.findFirst("div.styles"); //"div.styles a.main em"
  styleElement = styleElement.findFirst("a.main");
  styleElement = styleElement.findFirst("em");
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
MediaInfo DeejayDeAlbumFetcher::getFetchedMedia() const
{
    return p_d->media;
}

void DeejayDeAlbumFetcher::setDateGroup(const QDate &date)
{
    p_d->dateGroup = date;
}


// Производит выборку.
void DeejayDeAlbumFetcher::fetch(QNetworkReply* reply)
{
  p_d->media.clear();

  QString html = reply->readAll();
  HtmlElement root(html);

  if (reply->error() != QNetworkReply::NoError) {
      qDebug() << "error reply" << reply->errorString();
      return;
  }

  HtmlElement contentElement = root.findFirst("article.single_product");

  if (contentElement.isEmpty()) {
      qDebug() << "no data";
      emit finished();
      return;
  }

  // Считывает адрес на картинку (необходим для получения адреса на трек).
  QString images = p_d->getImages(contentElement);
  if (images.isEmpty()) return;

  QString artist = p_d->getArtist(contentElement);
  QString title = p_d->getTitleRelease(contentElement);  
  QString style = p_d->getStyle(contentElement);
  QString catalog = p_d->getCatalog(contentElement);
  QString label = p_d->getLabel(contentElement);
  int id = getUniqueId(catalog, label);
  QDate date = p_d->getDate(contentElement);

  if (!date.isValid())
      date = p_d->dateGroup;

  // Определяет треклист релиза.
  QVariantHash tracks = getTrackList(id, root, images.split(";").at(0));
  if (tracks.isEmpty()) {
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

  reply->deleteLater();
  emit finished();
}


// Возвращает треклист.
QVariantHash DeejayDeAlbumFetcher::getTrackList(int id, const HtmlElement &element,
                                               const QString& params)
{
  QVariantHash result;

  QList<HtmlElement> tracksCollection = element.findAll("a.track");
  if (tracksCollection.count() == 0)
    return QVariantHash();

  int idTrack = id;
  foreach (HtmlElement trackElement, tracksCollection) {
    QString link = p_d->getLinkTrack(trackElement, params);
    QString title = p_d->getTitleTrack(trackElement.findFirst("h5"));
    result.insert(QString::number(idTrack++), QStringList() << title << link);
  }

  return result;
}
