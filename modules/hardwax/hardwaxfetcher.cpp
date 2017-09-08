#include "hardwaxfetcher.h"

//*************************  HardwaxFetcherPrivate  ****************************//
class HardwaxFetcherPrivate
{
public:
  QList <MediaInfo> albums;

public:
  // Возвращает артиста.
  QString getArtist(const QWebElement &element);
  // Возвращает название релиза.
  QString getTitleRelease(const QWebElement &element);
  // Возвращает лэйбл.
  QString getLabel(const QWebElement &element);
  // Возвращает номер по каталогу.
  QString getCatNumber(const QWebElement &element);
  // Возвращает ссылку на трек.
  QString getLinkTrack(const QWebElement &element,
                       const QString& params = QString());
  // Возвращает ссылки на изображения релиза.
  QStringList getImages(const QWebElement &element);
  // Возвращает название трека.
  QString getTitleTrack(const QWebElement &element);
  // Возвращает треклист.
  QVariantHash getTrackList(const QWebElement& element,
                           const QString& params = QString());

};

// Возвращает артиста.
QString HardwaxFetcherPrivate::getArtist(const QWebElement &element)
{
  QWebElement artistElement = element.findFirst("div.linebig strong a");
  return artistElement.toPlainText().section(':', 0, 0);
}


// Возвращает название релиза.
QString HardwaxFetcherPrivate::getTitleRelease(const QWebElement &element)
{
  QWebElement titleElement = element.findFirst("div.linebig");
  return titleElement.toPlainText().section(':', 1, 1).replace("&nbsp;", "");
}


// Возвращает лэйбл.
QString HardwaxFetcherPrivate::getLabel(const QWebElement &element)
{
  QWebElement labelElement = element.findFirst("div.linesmall a");
  return labelElement.toInnerXml();
}


// Возвращает номер по каталогу.
QString HardwaxFetcherPrivate::getCatNumber(const QWebElement &element)
{
  QWebElement labelElement = element.findFirst("div.linesmall a");
  return labelElement.nextSibling().toInnerXml();
}


// Возвращает ссылку на трек.
QString HardwaxFetcherPrivate::getLinkTrack(const QWebElement &element,
                                            const QString& params)
{
  return element.attribute("href");
}


// Возвращает ссылки на изображения релиза.
QStringList HardwaxFetcherPrivate::getImages(const QWebElement &element)
{
  QStringList result;

  QWebElementCollection images = element.findAll("div.picture.long a img.thumbnail");

  if (images.count() == 0)
    return QStringList();

  foreach (QWebElement e, images) {
    QString image = e.attribute("src");
    result.push_back(image);
  }

  return result;
}


// Возвращает название трека.
QString HardwaxFetcherPrivate::getTitleTrack(const QWebElement &element)
{
  return element.toPlainText().replace("&amp;", "&");
}


// Возвращает треклист.
QVariantHash HardwaxFetcherPrivate::getTrackList(const QWebElement &element,
                                                const QString& params)
{
  QVariantHash result;

  QWebElementCollection linksCollection = element.findAll("ul.tracklisting li a");
  if (linksCollection.count() == 0) {
    return QVariantHash();
  }

  foreach (QWebElement linkElement, linksCollection) {
    QString link = getLinkTrack(linkElement);
    QString title = getTitleTrack(linkElement);
    result.insert(title, link);
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


void HardwaxFetcher::result(bool ok)
{
  m_isStop = false;
  p_d->albums.clear();

  QWebElementCollection vinylCollection =
      m_page.mainFrame()->findAllElements("div.listing.block");
  qDebug() << vinylCollection.count();

  // Если нет элементов на странице завершает выборку.
  if (vinylCollection.count() == 0) {
    emit fetched(Fetcher::NoElements);
    return;
  }

  foreach (QWebElement vinylElement, vinylCollection) {
    if (!m_isStop) {
      QString artist = p_d->getArtist(vinylElement);
      QString title = p_d->getTitleRelease(vinylElement);
      int id = qHash(artist + title);
      QString catalog = p_d->getCatNumber(vinylElement);
      QString label = p_d->getLabel(vinylElement);
      QStringList images = p_d->getImages(vinylElement);
      QVariantHash tracks = p_d->getTrackList(vinylElement);

      MediaInfo album;
      album.setData(MediaInfo::Id, id);
      album.setData(MediaInfo::Artist, artist);
      album.setData(MediaInfo::Title, title);
      album.setData(MediaInfo::Catalog, catalog);
      album.setData(MediaInfo::Label, label);
      album.setData(MediaInfo::Images, images);
      album.setData(MediaInfo::Tracks, tracks);
      album.setData(MediaInfo::Source, "Hardwax");

      p_d->albums.push_back(album);

    }
    else {
      emit fetched(Fetcher::Stoped);
      break;
      return;
    }
  }

  // Делает паузу.
  pause(m_delay);

  emit ready(p_d->albums);
  emit fetched(Fetcher::Finished);
}
