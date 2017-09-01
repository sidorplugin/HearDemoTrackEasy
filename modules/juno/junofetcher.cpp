#include "junofetcher.h"

//*************************  JunoFetcherPrivate  ****************************//
class JunoFetcherPrivate
{
public:
  QList <AlbumInfo> albums;

public:
  // Возвращает артиста.
  QString getArtist(const QWebElement &element);
  // Возвращает название релиза.
  QString getTitleRelease(const QWebElement &element);
  // Возвращает лэйбл.
  QString getLabel(const QWebElement &element);
  // Возвращает номер по каталогу.
  QString getCatNumber(const QWebElement &element);
  // Возвращает ссылки на изображения релиза.
  QStringList getImages(const QWebElement &element);
  // Возвращает ссылку на трек.
  QString getLinkTrack(const QWebElement &element, const QString& params = QString());
  // Возвращает название трека.
  QString getTitleTrack(const QWebElement &element);
  // Возвращает треклист.
  QVariantHash getTrackList(const QWebElement& element, const QString& params = QString());
  // Возвращает дату релиза.
  QDate getDateRelease(const QWebElement &element);

};


// Возвращает артиста.
QString JunoFetcherPrivate::getArtist(const QWebElement &element)
{
  return element.toPlainText().replace("/", ",");
}


// Возвращает название релиза.
QString JunoFetcherPrivate::getTitleRelease(const QWebElement &element)
{
  QWebElement titleElement = element.findFirst("a.text_medium.text_fg");
  return titleElement.toPlainText().replace("\"", "");
}


// Возвращает лэйбл.
QString JunoFetcherPrivate::getLabel(const QWebElement &element)
{
  return element.toPlainText();
}


// Возвращает номер по каталогу.
QString JunoFetcherPrivate::getCatNumber(const QWebElement &element)
{
  return element.toPlainText().section(". Rel:", 0, 0).remove("Cat: ");
}


// Возвращает ссылки на изображения релиза.
QStringList JunoFetcherPrivate::getImages(const QWebElement &element)
{
  QStringList result;

  QWebElement imageElement = element.findFirst("div.pl-img a img");

  if (imageElement.isNull())
    return QStringList();

  QString image = imageElement.attribute("src");
  result.push_back(image);

  return result;
}


// Возвращает дату релиза.
QDate JunoFetcherPrivate::getDateRelease(const QWebElement &element)
{
  QLocale eng(QLocale::English);
  QString dateString = element.toPlainText().section("Rel:", 1, 1).remove(0, 1);
  QDate date =  eng.toDate(dateString, "dd MMM yy");
  QDate result(date.year() + 100, date.month(), date.day());
  return result;
}


// Возвращает ссылку на трек.
QString JunoFetcherPrivate::getLinkTrack(const QWebElement &element,
                                         const QString& params)
{
  QWebElement linkElement = element.findFirst("div.vi-icon a");
  return linkElement.attribute("href");
}


// Возвращает название трека.
QString JunoFetcherPrivate::getTitleTrack(const QWebElement &element)
{
  QWebElement titleTrackElement = element.findFirst("div.vi-text");

  QRegExp prepareRx ("[(]|[)]");
  QString title =
      titleTrackElement.toPlainText().replace("\"", "").replace("/", ",");
  QStringList list = title.split(prepareRx, QString::SkipEmptyParts);
  QString forRemove = list.last();
  return title.remove(" (" + forRemove + ")");
}


// Возвращает треклист.
QVariantHash JunoFetcherPrivate::getTrackList(const QWebElement &element,
                                              const QString& params)
{
  QVariantHash result;

  QWebElementCollection tracksCollection = element.findAll("li");
  if (tracksCollection.count() == 0) {
      return QVariantHash();
  }

  foreach (QWebElement track, tracksCollection) {
    QString link = getLinkTrack(track);
    QString title = getTitleTrack(track);
    result.insert(title, link);
  }

  return result;
}


//**************************  JunoFetcher  *********************************//


JunoFetcher::JunoFetcher(QObject *parent)
{
  p_d = new JunoFetcherPrivate;
}


JunoFetcher::~JunoFetcher()
{
  delete p_d;
}


void JunoFetcher::result(bool ok)
{
  m_isStop = false;
  p_d->albums.clear();

  QWebElementCollection vinylCollection = m_page.mainFrame()->findAllElements("div.dv-item");
  qDebug() << vinylCollection.count();

  // Если нет элементов на странице завершает выборку.
  if (vinylCollection.count() == 0) {
    emit fetched(Fetcher::NoElements);
    return;
  }

  foreach (QWebElement element, vinylCollection) {
    if (!m_isStop) {
      handleElement(element);
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


void JunoFetcher::handleElement(const QWebElement &element)
{
  QWebElementCollection infoCollection =
      element.findAll("div.pl-info.jq_highlight div.vi-text");
  qDebug() << infoCollection.count();

  if (infoCollection.count() < 3)
    return;

  QString artist = p_d->getArtist(infoCollection.at(0));
  QString title = p_d->getTitleRelease(infoCollection.at(1));
  int id = qHash(artist + title);
  QString label = p_d->getLabel(infoCollection.at(2));
  QString catalog = p_d->getCatNumber(infoCollection.at(3));
  QStringList images = p_d->getImages(element);
  QDate date = p_d->getDateRelease(infoCollection.at(3));

  QWebElement tracklistElement =
      element.findFirst("ol.vi-tracklist.jq_highlight");
  QVariantHash tracks = p_d->getTrackList(tracklistElement);

  AlbumInfo album;
  album.setData(AlbumInfo::Id, id);
  album.setData(AlbumInfo::Artist, artist);
  album.setData(AlbumInfo::Title, title);
  album.setData(AlbumInfo::Catalog, catalog);
  album.setData(AlbumInfo::Label, label);
  album.setData(AlbumInfo::Images, images);
  album.setData(AlbumInfo::Tracks, tracks);
  album.setData(AlbumInfo::Source, "Juno");

  p_d->albums.push_back(album);
}
