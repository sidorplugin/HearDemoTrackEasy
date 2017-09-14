#include "junofetcher.h"

//*************************  JunoFetcherPrivate  ****************************//
class JunoFetcherPrivate
{
public:
  QList <MediaInfo> mediaList;

public:
  // Возвращает артиста.
  QString getArtist(const QWebElement &element);
  // Возвращает название релиза.
  QString getTitleRelease(const QWebElement &element);
  // Возвращает ссылку на релиз.
  QString getLinkRelease(const QWebElement &element);
  // Возвращает лэйбл.
  QString getLabel(const QWebElement &element);
  // Возвращает номер по каталогу.
  QString getCatNumber(const QWebElement &element);
  // Возвращает ссылки на изображения релиза.
  QString getImages(const QWebElement &element);
  // Возвращает ссылку на трек.
  QString getLinkTrack(const QWebElement &element, const QString& params = QString());
  // Возвращает название трека.
  QString getTitleTrack(const QWebElement &element);
  // Возвращает треклист.
  QVariantHash getTrackList(int id, const QWebElement& element, const QString& params = QString());
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


// Возвращает ссылку на релиз.
QString JunoFetcherPrivate::getLinkRelease(const QWebElement &element)
{
    QWebElement linkElement = element.findFirst("a.text_medium.text_fg");
    return "www.juno.co.uk" + linkElement.attribute("href");
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
QString JunoFetcherPrivate::getImages(const QWebElement &element)
{
  QWebElement imageElement = element.findFirst("div.pl-img img");

  if (imageElement.isNull())
    return QString();

  if (!imageElement.attribute("rel").isEmpty())
      return imageElement.attribute("rel");

  return imageElement.attribute("src");
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

  QRegExp prepareRx ("[(](\\d+):(\\d+)[)]");
  QString title =
      titleTrackElement.toPlainText().replace("\"", "").replace("/", ",");
  return title.remove(prepareRx);
}


// Возвращает треклист.
QVariantHash JunoFetcherPrivate::getTrackList(int id, const QWebElement &element,
                                              const QString& params)
{
  QVariantHash result;

  QWebElementCollection tracksCollection = element.findAll("li");
  if (tracksCollection.count() == 0) {
      return QVariantHash();
  }

  int idTrack = id;
  foreach (QWebElement track, tracksCollection) {
    QString link = getLinkTrack(track);
    QString title = getTitleTrack(track);
    result.insert(QString::number(idTrack++), QStringList() << title << link);
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
  p_d->mediaList.clear();

  QWebElementCollection vinylCollection =
          m_page.mainFrame()->findAllElements("div.dv-item");
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

  emit ready(p_d->mediaList);
  emit fetched(Fetcher::Finished);
}


void JunoFetcher::handleElement(const QWebElement &element)
{
  QWebElementCollection infoCollection =
      element.findAll("div.pl-info.jq_highlight div.vi-text");

  if (infoCollection.count() < 3)
    return;

  QString artist = p_d->getArtist(infoCollection.at(0));
  QString title = p_d->getTitleRelease(infoCollection.at(1));
  QString catalog = p_d->getCatNumber(infoCollection.at(3));
  QString label = p_d->getLabel(infoCollection.at(2));
  int id = GlobalData::getInstance()->getUniqueId(catalog, label);
  QString images = p_d->getImages(element);
  QString linkAlbum = p_d->getLinkRelease(infoCollection.at(1));
  QDate date = p_d->getDateRelease(infoCollection.at(3));

  QWebElement tracklistElement =
      element.findFirst("ol.vi-tracklist.jq_highlight");
  QVariantHash tracks = p_d->getTrackList(id, tracklistElement);

  MediaInfo album;
  album.setData(MediaInfo::Id_Album, id);
  album.setData(MediaInfo::Artist, artist);
  album.setData(MediaInfo::Title_Album, title);
  album.setData(MediaInfo::Catalog, catalog);
  album.setData(MediaInfo::Label, label);
  album.setData(MediaInfo::Date, date);
  album.setData(MediaInfo::Images, images);
  album.setData(MediaInfo::Link_Album, linkAlbum);
  album.setData(MediaInfo::Tracks, tracks);
  album.setData(MediaInfo::Source, "Juno");

  p_d->mediaList.push_back(album);
}
