#include "junofetcher.h"

//*************************  JunoFetcherPrivate  ****************************//
class JunoFetcherPrivate
{
public:
  QList <MediaInfo> mediaList;

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
  // Возвращает ссылку на трек.
  QString getLinkTrack(const HtmlElement &element, const QString& params = QString());
  // Возвращает название трека.
  QString getTitleTrack(const HtmlElement &element);
  // Возвращает треклист.
  QVariantHash getTrackList(int id, const HtmlElement& element, const QString& params = QString());
  // Возвращает дату релиза.
  QDate getDateRelease(const HtmlElement &element);

};


// Возвращает артиста.
QString JunoFetcherPrivate::getArtist(const HtmlElement &element)
{
  QStringList artists;
  QList<HtmlElement> artistsCollection = element.findAll("a.text_medium text_fg");
  foreach (HtmlElement artistElement, artistsCollection) {
      artists.append(artistElement.toPlainText().replace("&amp;", "&"));
  }
  return artists.join(",");
}


// Возвращает название релиза.
QString JunoFetcherPrivate::getTitleRelease(const HtmlElement &element)
{
  HtmlElement titleElement = element.findFirst("a.text_medium text_fg");
  return titleElement.toPlainText().replace("\"", "").replace("&amp;", "&");
}


// Возвращает ссылку на релиз.
QString JunoFetcherPrivate::getLinkRelease(const HtmlElement &element)
{
    HtmlElement linkElement = element.findFirst("a.text_medium text_fg");
    return "www.juno.co.uk" + linkElement.attribute("href");
}


// Возвращает лэйбл.
QString JunoFetcherPrivate::getLabel(const HtmlElement &element)
{
  // "vi-text mb_sml"
  HtmlElement labelElement = element.findFirst("a.text_medium text_subtle");
  return labelElement.toPlainText();
}


// Возвращает номер по каталогу.
QString JunoFetcherPrivate::getCatNumber(const HtmlElement &element)
{
  return element.toPlainText().section(". Rel:", 0, 0).remove("Cat: ");
}


// Возвращает ссылки на изображения релиза.
QString JunoFetcherPrivate::getImages(const HtmlElement &element)
{
  HtmlElement imageElement = element.findFirst("img.lazy_img img-fluid");

  if (!imageElement.attribute("rel").isEmpty())
      return imageElement.attribute("rel");

  return imageElement.attribute("src");
}


// Возвращает дату релиза.
QDate JunoFetcherPrivate::getDateRelease(const HtmlElement &element)
{
  QLocale eng(QLocale::English);
  QRegExp rx("(\\d{2}) (Jan|Feb|Mar|Apr|May|Jun|Jul|Aug|Sep|Oct|Nov|Dec) (\\d{2})");

  QString rowString = element.toPlainText();
  int pos = rx.lastIndexIn(rowString);
  QString dateString = rowString.remove(0, pos);
  QDate date =  eng.toDate(dateString, "dd MMM yy");
  QDate result(date.year() + 100, date.month(), date.day());
  return result;
}


// Возвращает ссылку на трек.
QString JunoFetcherPrivate::getLinkTrack(const HtmlElement &element,
                                         const QString& params)
{
  HtmlElement linkElement = element.findFirst("div.vi-icon");  // "div.vi-icon a"
  linkElement = linkElement.findFirst("a");
  return linkElement.attribute("href");
}


// Возвращает название трека.
QString JunoFetcherPrivate::getTitleTrack(const HtmlElement &element)
{
  HtmlElement titleTrackElement = element.findFirst("div.vi-text");

  QRegExp timeRemoveRx ("[(](\\d+):(\\d+)[)]");
  QRegExp whitespaceRemoveRx ("(^\\s+|\\t+)");
  QString title =
      titleTrackElement.toPlainText().replace("\"", "").replace("/", ",").replace("&amp;", "&");
  return title.remove(timeRemoveRx).remove(whitespaceRemoveRx);
}


// Возвращает треклист.
QVariantHash JunoFetcherPrivate::getTrackList(int id, const HtmlElement &element,
                                              const QString& params)
{
  QVariantHash result;

  QList<HtmlElement> tracksCollection = element.findAll("li");
  if (tracksCollection.count() == 0) {
      return result;
  }

  int idTrack = id;
  foreach (HtmlElement track, tracksCollection) {
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


void JunoFetcher::fetch(QNetworkReply* reply)
{
  m_isStop = false;
  m_data.clear();

  QString html = reply->readAll();
  HtmlElement root(html);

  if (reply->error() != QNetworkReply::NoError) {
      qDebug() << "error reply" << reply->errorString();
      return;
  }

  QList<HtmlElement> vinylCollection = root.findAll("div.dv-item");
  qDebug() << vinylCollection.count();

  // Если нет элементов на странице завершает выборку.
  if (vinylCollection.count() == 0) {
    return;
  }

  foreach (HtmlElement element, vinylCollection) {
    if (!m_isStop) {
      handleElement(element);
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


void JunoFetcher::handleElement(const HtmlElement &element)
{
  // "div.pl-info.jq_highlight div.vi-text"
  QList<HtmlElement> infoCollection = element.findAll("div.vi-text");

  if (infoCollection.count() < 3)
    return;

  QString artist = p_d->getArtist(infoCollection.at(0));
  QString title = p_d->getTitleRelease(infoCollection.at(1));
  QString catalog = p_d->getCatNumber(infoCollection.at(2));
  QString label = p_d->getLabel(infoCollection.at(2));
  int id = getUniqueId(catalog, label);
  QString images = p_d->getImages(element);
  QString linkAlbum = p_d->getLinkRelease(infoCollection.at(1));
  QDate date = p_d->getDateRelease(infoCollection.at(3));

  HtmlElement tracklistElement =
      element.findFirst("ol.vi-tracklist jq_highlight");
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

  m_data.push_back(album);
}
