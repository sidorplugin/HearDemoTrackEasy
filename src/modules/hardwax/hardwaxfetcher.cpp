#include "hardwaxfetcher.h"

//*************************  HardwaxFetcherPrivate  ****************************//
class HardwaxFetcherPrivate
{
public:
  // Возвращает артиста.
  QString getArtist(const HtmlElement &element);
  // Возвращает название релиза.
  QString getTitleRelease(const HtmlElement &element);
  // Возвращает ссылку на релиз.
  QString getLinkRelease(const HtmlElement &element);
  // Возвращает лэйбл.
  QString getLabel(const HtmlElement &element);
  // Возвращает номер по каталогу.
  QString getCatNumber(const HtmlElement &element);
  // Возвращает ссылки на изображения релиза.
  QString getImages(const HtmlElement &element);
  // Возвращает треклист.
  QVariantHash getTrackList(int id, const HtmlElement& element,
                           const QString& params = QString());
};

// Возвращает артиста.
QString HardwaxFetcherPrivate::getArtist(const HtmlElement &element)
{
  //
  HtmlElement artistElement = element.findFirst("div.linebig");  //div.linebig strong a
  artistElement = artistElement.findFirst("a");
  return artistElement.toPlainText().section(':', 0, 0);
}


// Возвращает название релиза.
QString HardwaxFetcherPrivate::getTitleRelease(const HtmlElement &element)
{
  HtmlElement titleElement = element.findFirst("div.linebig");
  return titleElement.toPlainText().section(':', 1, 1).simplified();
}


// Возвращает ссылку на релиз.
QString HardwaxFetcherPrivate::getLinkRelease(const HtmlElement &element)
{
  QString result;
  HtmlElement linkElement = element.findFirst("div.linesmall"); // "div.linesmall a"
  linkElement = linkElement.findFirst("a");
  result = "https://hardwax.com" + linkElement.nextSibling().attribute("href");
  return result;
}


// Возвращает лэйбл.
QString HardwaxFetcherPrivate::getLabel(const HtmlElement &element)
{
  HtmlElement labelElement = element.findFirst("div.linesmall");  //"div.linesmall a"
  labelElement = labelElement.findFirst("a");
  return labelElement.toPlainText();
}


// Возвращает номер по каталогу.
QString HardwaxFetcherPrivate::getCatNumber(const HtmlElement &element)
{
  HtmlElement labelElement = element.findFirst("div.linesmall"); // div.linesmall a
  labelElement = labelElement.findFirst("a");
  return labelElement.nextSibling().toPlainText();
}


// Возвращает ссылки на изображения релиза.
QString HardwaxFetcherPrivate::getImages(const HtmlElement &element)
{
  //"div.picture.long a img.thumbnail"
  QList<HtmlElement> images = element.findAll("img.thumbnail");

  if (images.count() == 0)
    return QString();

  QStringList list;
  foreach (HtmlElement e, images) {
    QString image = e.attribute("src");
    list << image;
  }

  return list.join(";");
}


// Возвращает треклист.
QVariantHash HardwaxFetcherPrivate::getTrackList(int id, const HtmlElement &element,
                                                const QString& params)
{
  QVariantHash result;

  // "ul.tracklisting li a"
  QList<HtmlElement> linksCollection = element.findFirst("ul.tracklisting").findAll("a");

  if (linksCollection.count() == 0) {
    return result;
  }

  int idTrack = id;
  foreach (HtmlElement linkElement, linksCollection) {
    QString link = linkElement.attribute("href");
    QString title = linkElement.toPlainText().replace("&amp;", "&");
    result.insert(QString::number(idTrack++), QStringList() << title << link);
  }

  return result;
}


//**************************  HardwaxFetcher  *********************************//

HardwaxFetcher::HardwaxFetcher(QObject *parent)
{
  p_d = new HardwaxFetcherPrivate;
}

HardwaxFetcher::~HardwaxFetcher()
{
  delete p_d;
}


void HardwaxFetcher::fetch(QNetworkReply* reply)
{
  m_isStop = false;
  m_data.clear();

  QString html = reply->readAll();
  HtmlElement root(html);

  if (reply->error() != QNetworkReply::NoError) {
      qDebug() << "error reply" << reply->errorString();
      return;
  }

  // div.listing.block
  QList<HtmlElement> vinylCollection = root.findAll("div.listing block ");
  qDebug() << vinylCollection.count();

  // Если нет элементов на странице завершает выборку.
  if (vinylCollection.count() == 0) {
    return;
  }

  foreach (HtmlElement vinylElement, vinylCollection) {
    if (!m_isStop) {
      QString artist = p_d->getArtist(vinylElement);
      QString title = p_d->getTitleRelease(vinylElement);
      QString catalog = p_d->getCatNumber(vinylElement);
      QString label = p_d->getLabel(vinylElement);
      QString linkAlbum = p_d->getLinkRelease(vinylElement);
      int id = getUniqueId(catalog, label);
      QString images = p_d->getImages(vinylElement);
      QVariantHash tracks = p_d->getTrackList(id, vinylElement);

      MediaInfo media;
      media.setData(MediaInfo::Id_Album, id);
      media.setData(MediaInfo::Artist, artist);
      media.setData(MediaInfo::Title_Album, title);
      media.setData(MediaInfo::Catalog, catalog);
      media.setData(MediaInfo::Label, label);
      media.setData(MediaInfo::Images, images);
      media.setData(MediaInfo::Link_Album, linkAlbum);
      media.setData(MediaInfo::Source, "Hardwax");
      media.setData(MediaInfo::Tracks, tracks);

      m_data.push_back(media);
    }
    else {
      emit stopped();
      break;
      return;
    }
  }

  reply->deleteLater();
  emit finished();
}
