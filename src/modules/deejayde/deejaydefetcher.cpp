#include "deejaydefetcher.h"
#include "deejaydealbumfetcher.h"
#include "dataclasses/mediainfo.h"

#include <QSet>
#include <QFile>

//*************************  DeejayDeFetcherPrivate  ****************************//
class DeejayDeFetcherPrivate
{
public:
  DeejayDeAlbumFetcher* albumFetcher;
  QDate releaseDate; // Текущая дата релиза по заголовку "Выпуски от dd.MM.yyyy".
  QString linkAlbum;

public:
  // Возвращает заголовок группы релизов "Выпуски от dd.MM.yyyy".
  QDate getDateGroup(const HtmlElement &element);
  // Возвращает ссылки на изображения релиза.
  QString getImages(const HtmlElement &element);
  // Возвращает true если ссылка правильная.
  bool validateLinkImage(const QString& link);


  // Возвращает артиста.
  QString getArtist(const HtmlElement &element);
  // Возвращает название релиза.
  QString getTitleRelease(const HtmlElement &element);
  // Возвращает лэйбл.
  QString getLabel(const HtmlElement &element);
  // Возвращает количество треков в релизе.
  int getCountTracksRelease(const HtmlElement &element);
  // Возвращает ссылку на трек.
  QString getLinkTrack(const HtmlElement &element,
                       const QString& params = QString());
  // Возвращает название трека.
  QString getTitleTrack(const HtmlElement &element);
  // Возвращает треклист.
  QVariantHash getTrackList(int id, const HtmlElement& element,
                            const QString& params = QString());

};


// Возвращает заголовок группы релизов "Выпуски от dd.MM.yyyy".
QDate DeejayDeFetcherPrivate::getDateGroup(const HtmlElement &element)
{
  QDate result;
  QRegExp rxDate("(\\d+){2}.(\\d+){2}.(\\d+){4}");
  if (element.hasClass("news")) {
      rxDate.indexIn(element.toPlainText());
      result = QDate::fromString(rxDate.cap(), "dd.MM.yyyy");
  }
  return result;
}


// Возвращает ссылки на изображения релиза.
QString DeejayDeFetcherPrivate::getImages(const HtmlElement &element)
{
  QStringList covers;
  QString coverImage1, coverImage2;
  QString baseAddress = "https://www.deejay.de";

  // "div.img.img1 a.zoom.noMod"
  HtmlElement cover1element = element.findFirst("div.img img1").findFirst("a.zoom noMod");
  // "div.img.img2 a.zoom.noMod"
  HtmlElement cover2element = element.findFirst("div.img img2").findFirst("a.zoom noMod");


  if (!cover1element.isEmpty())
      coverImage1 = cover1element.attribute("href");
  else {
      // "div.img.img1 a.noMod"
      cover1element = element.findFirst("div.img img1").findFirst("a.noMod");
      if (!cover1element.isEmpty())
          coverImage1 = cover1element.attribute("href");
  }
  if (!coverImage1.isEmpty())
    covers.append(baseAddress + coverImage1);

  if (!cover2element.isEmpty())
      coverImage2 = cover2element.attribute("href");
  else {
      // div.img.img2 a.noMod
      cover2element = element.findFirst("div.img img2").findFirst("a.noMod");
      if (!cover2element.isEmpty())
          coverImage2 = cover2element.attribute("href");
  }
  if (!coverImage2.isEmpty())
    covers.append(baseAddress + coverImage2);

  return covers.join(";");
}


// Возвращает true если ссылка правильная.
bool DeejayDeFetcherPrivate::validateLinkImage(const QString &link)
{
  // Если путь к изображению не подходящий.
  if (link.section("/", -3).isEmpty() || link.isEmpty()) {
    qDebug() << "picLink validate false";
    return false;
  }

  return true;
}


// Возвращает артиста.
QString DeejayDeFetcherPrivate::getArtist(const HtmlElement &element)
{
  // "h2.artist interprets a"
  HtmlElement artistElement = element.findFirst("h2.artist");
  artistElement = artistElement.findFirst("interprets");
  return artistElement.toPlainText().replace("&amp;", "&").replace("\"", "");
}


// Возвращает название релиза.
QString DeejayDeFetcherPrivate::getTitleRelease(const HtmlElement &element)
{
  // "h3.title a"
  HtmlElement titleElement = element.findFirst("h3.title");
  return titleElement.toPlainText().replace("&amp;", "&").replace("\"", "");
}


// Возвращает лэйбл.
QString DeejayDeFetcherPrivate::getLabel(const HtmlElement &element)
{
  HtmlElement labelElement = element.findFirst("div.label");
  QString label = labelElement.findFirst("b").toPlainText().replace("&amp;", "&");
  if (label.isEmpty())
    label = labelElement.findFirst("a").toPlainText().replace("&amp;", "&");
  return label;
}


// Возвращает количество треков в релизе.
int DeejayDeFetcherPrivate::getCountTracksRelease(const HtmlElement& element)
{
  int countTracks = -1;
//  "span.allTracks i"
  HtmlElement countTracksElement = element.findFirst("span.allTracks");

  // Если элемент существует, определяет число элементов.
  if (!countTracksElement.isEmpty()) {
      QString count = countTracksElement.toPlainText();
      QRegExp rx("[(]\\d+[)]");
      rx.indexIn(count);
      countTracks = rx.cap().remove("(").remove(")").toInt();
  }
  return countTracks;
}


// Возвращает ссылку на трек.
QString DeejayDeFetcherPrivate::getLinkTrack(const HtmlElement &element,
                                             const QString& params)
{
  QString href = "http://www.deejay.de/" + element.attribute("href");
  QString symbol = href.section("_", -1);

  QString result = "http://www.deejay.de/streamit/" + params.section("/", -3).
        replace(QString(".jpg"), symbol + QString(".mp3"));
  return result;
}


// Возвращает название трека.
QString DeejayDeFetcherPrivate::getTitleTrack(const HtmlElement &element)
{
  QString title = element.toPlainText();
  return title.replace("&amp;", "&").replace("\"", "");
}


// Возвращает треклист.
QVariantHash DeejayDeFetcherPrivate::getTrackList(int id,
                                                 const HtmlElement &element,
                                                 const QString& params)
{
  QList<HtmlElement> linksCollection = element.findAll("a.track");

  int idTrack = id;
  QVariantHash result;
  foreach (HtmlElement linkElement, linksCollection) {
    QString link = getLinkTrack(linkElement, params);
    QString title = getTitleTrack(linkElement.findFirst("em"));
    result.insert(QString::number(idTrack++), QStringList() << title << link);
  }
  return result;
}


//**************************  DeejayDeFetcher  *********************************//


DeejayDeFetcher::DeejayDeFetcher(QObject *parent)
{
  p_d = new DeejayDeFetcherPrivate;
  p_d->albumFetcher = new DeejayDeAlbumFetcher;
}


DeejayDeFetcher::~DeejayDeFetcher()
{
  delete p_d;
}


void DeejayDeFetcher::fetch(QNetworkReply* reply)
{
  qDebug() << "DeejayDeFetcher::fetch()";
  m_isStop = false;
  m_data.clear();

  if (reply->error() != QNetworkReply::NoError) {
      qDebug() << "error reply" << reply->errorString();
      return;
  }

  QString html = reply->readAll();
  HtmlElement root(html);

  QList<HtmlElement> vinylCollection = root.findAll("article.clearfix product notangemeldet");
  qDebug() << vinylCollection.count();

  // Если нет элементов на странице завершает выборку.
  if (vinylCollection.count() == 0) {
    return;
  }

  // Обрабатывает каждый элемент коллекции.
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


void DeejayDeFetcher::handleElement(const HtmlElement& element)
{
  // Определяет количество треков в альбоме.
  int countTracks = p_d->getCountTracksRelease(element);

  if (countTracks == -1) return;

  p_d->linkAlbum = element.findFirst("h3.title").attribute("href");
  // Проверяет заголовок группы текущей даты релиза "Выпуски от dd.MM.yyyy".
  QDate releaseDate = p_d->getDateGroup(element.previousSibling());
  if (releaseDate.isValid())
      p_d->releaseDate = releaseDate;

  // Если в альбоме больше 4 треков, производит разбор с помощью выборщика альбомов.
  if (countTracks > 4) {
      p_d->albumFetcher->setDateGroup(p_d->releaseDate);
      p_d->albumFetcher->load("https://www.deejay.de/content.php?param=" + p_d->linkAlbum);

      // Остается в цикле пока не произведется выборка альбома.
      QEventLoop wait;
      connect(p_d->albumFetcher, SIGNAL(finished()),
              &wait, SLOT(quit()));
      wait.exec();

      // Если результат выборки альбома не нулевой добавляет его в
      // результирующий список альбомов.
      MediaInfo fetchedMedia = p_d->albumFetcher->getFetchedMedia();
      if (!fetchedMedia.isEmpty())
        m_data.append(fetchedMedia);
  }
  // Если в альбоме не больше 4 треков.
  else {      
      // Определяет дату релиза.
      QDate date = QDate::fromString(element.findFirst("div.date").toPlainText(), "dd.MM.yyyy");

      // Если дата в релизе не указана, присваивает дату заголовка.
      if (!date.isValid()) date = p_d->releaseDate;

      QString artist = p_d->getArtist(element);
      QString title = p_d->getTitleRelease(element);
      QString style = element.findFirst("a.main").toPlainText();     // "div.style a.main"
      QString catalog = element.findFirst("div.label").firstChild().toPlainText();  //
      QString label = p_d->getLabel(element);
      int id = getUniqueId(catalog, label);
      QString images = p_d->getImages(element);

      if (images.isEmpty()) {
          qDebug() << "no images";
        return;
      }

      QVariantHash tracks = p_d->getTrackList(id, element, images.split(";").at(0));

      MediaInfo media;
      media.setData(MediaInfo::Id_Album, id);
      media.setData(MediaInfo::Artist, artist);
      media.setData(MediaInfo::Title_Album, title);
      media.setData(MediaInfo::Style, style);
      media.setData(MediaInfo::Catalog, catalog);
      media.setData(MediaInfo::Label, label);
      media.setData(MediaInfo::Date, date);
      media.setData(MediaInfo::Images, images);
      media.setData(MediaInfo::Link_Album, "http://www.deejay.de" + p_d->linkAlbum);
      media.setData(MediaInfo::Source, "DeejayDe");
      media.setData(MediaInfo::Tracks, tracks);

      m_data.push_back(media);
  }
}

