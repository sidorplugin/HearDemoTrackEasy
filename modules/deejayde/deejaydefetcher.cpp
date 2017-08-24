#include "deejaydefetcher.h"
#include "dataclasses/trackinfo.h"

#include <QSet>

//*************************  DeejayDeFetcherPrivate  ****************************//
class DeejayDeFetcherPrivate
{
public:
  DeejayDeAlbumFetcher* albumFetcher;
  QList <TrackInfo> trackDataList;
  // Текущая дата релиза по заголовку "Выпуски от dd.MM.yyyy".
  QDate releaseDate;
  QString linkRelease;

public:
  // Получает число треков в альбоме.
  int getCountTracks(const QString& str);
  // Возвращает заголовок группы релизов "Выпуски от dd.MM.yyyy".
  QDate getDateReleaseGroup(const QWebElement &element);
  // Возвращает ссылку на изображение релиза.
  QString getPicLinkRelease(const QWebElement &element);
  // Возвращает true если ссылка правильная.
  bool validatePicLinkRelease(const QString& link);


  // Возвращает дату релиза.
  QDate getDateRelease(const QWebElement &element);
  // Возвращает артиста.
  QString getArtist(const QWebElement &element);
  // Возвращает название релиза.
  QString getTitle(const QWebElement &element);
  // Возвращает лэйбл.
  QString getLabel(const QWebElement &element);
  // Возвращает номер по каталогу.
  QString getCatNumber(const QWebElement &element);
  // Возвращает ссылку на релиз.
  QString getLinkRelease(const QWebElement &element);
  // Возвращает стиль релиза.
  QString getStyle(const QWebElement &element);
  // Возвращает количество треков в релизе.
  int getCountTracksRelease(const QWebElement &element);
  // Возвращает ссылку на трек.
  QString getLinkTrack(const QWebElement &element,
                       const QString& params = QString());
  // Возвращает название трека.
  QString getTitleTrack(const QWebElement &element);
  // Возвращает треклист.
  QStringList getTrackList(const QWebElement& element,
                           const QString& params = QString());

};


// Получает число треков в альбоме.
int DeejayDeFetcherPrivate::getCountTracks(const QString& str)
{
  QRegExp rx ("[(]|[)]");
  QStringList list = str.split(rx, QString::SkipEmptyParts);
  QString countTracksString;

  if (!list.isEmpty()) {
    countTracksString = list.at(0);
    return countTracksString.toInt();
  }
  else
    return 0;
}


// Возвращает заголовок группы релизов "Выпуски от dd.MM.yyyy".
QDate DeejayDeFetcherPrivate::getDateReleaseGroup(const QWebElement &element)
{
  if (element.hasClass("news")) {
    QString date = element.findFirst("b").toInnerXml();
    return QDate::fromString(date, "dd.MM.yyyy");
  }
  else
    return QDate();
}


// Возвращает ссылку на изображение релиза.
QString DeejayDeFetcherPrivate::getPicLinkRelease(const QWebElement &element)
{
  QWebElement linkElement = element.findFirst("div.img.img1 a.zoom.noMod");
  if (linkElement.isNull())
    linkElement = element.findFirst("div.img.img1 a.noMod");

  QString href = linkElement.attribute("href");
  if (validatePicLinkRelease(href))
    return href;
  else
    return QString();
}


// Возвращает true если ссылка правильная.
bool DeejayDeFetcherPrivate::validatePicLinkRelease(const QString &link)
{
  // Если путь к изображению не подходящий.
  if (link.section("/", -3).isEmpty()) {
    qDebug() << "picLink validate false";
    return false;
  }

  return true;
}


// Возвращает дату релиза.
QDate DeejayDeFetcherPrivate::getDateRelease(const QWebElement &element)
{
  QWebElement dateElement = element.findFirst("div.date");
   QString dateString = dateElement.toPlainText();
  return QDate::fromString(dateString, "dd.MM.yyyy");
}


// Возвращает артиста.
QString DeejayDeFetcherPrivate::getArtist(const QWebElement &element)
{
  QWebElement artistElement = element.findFirst("h2.artist interprets a");
  return artistElement.toInnerXml().replace("&amp;", "&").replace("\"", "");
}


// Возвращает название релиза.
QString DeejayDeFetcherPrivate::getTitle(const QWebElement &element)
{
  QWebElement titleElement = element.findFirst("h3.title a");
  return titleElement.toInnerXml().replace("&amp;", "&").replace("\"", "");
}


// Возвращает лэйбл.
QString DeejayDeFetcherPrivate::getLabel(const QWebElement &element)
{
  QWebElement labelElement = element.findFirst("div.label");
  return labelElement.firstChild().nextSibling().nextSibling().
         toInnerXml().replace("&amp;", "&");
}


// Возвращает номер по каталогу.
QString DeejayDeFetcherPrivate::getCatNumber(const QWebElement &element)
{
  QWebElement labelElement = element.findFirst("div.label");
  return labelElement.firstChild().toInnerXml();
}


// Возвращает ссылку на релиз.
QString DeejayDeFetcherPrivate::getLinkRelease(const QWebElement &element)
{
  QWebElement albumNameElement = element.findFirst("h3.title a");
  return albumNameElement.attribute("href");
}


// Возвращает жанр релиза.
QString DeejayDeFetcherPrivate::getStyle(const QWebElement &element)
{
  QWebElement styleElement = element.findFirst("div.style a.main");
  return styleElement.toPlainText();
}


// Возвращает количество треков в релизе.
int DeejayDeFetcherPrivate::getCountTracksRelease(const QWebElement &element)
{
  int countTracks = -1;
  QWebElement countTracksElement = element.findFirst("span.allTracks i");

  // Если элемент существует, определяет число элементов.
  if (!countTracksElement.isNull()) {
    countTracks = getCountTracks(countTracksElement.toInnerXml());
  }
  return countTracks;
}


// Возвращает ссылку на трек.
QString DeejayDeFetcherPrivate::getLinkTrack(const QWebElement &element,
                                             const QString& params)
{
  QString href = "http://www.deejay.de/" + element.attribute("href");
  QString symbol = href.section("_", -1);
  QString result = "http://www.deejay.de/streamit/" + params.section("/", -3).
        replace(QString(".jpg"), symbol + QString(".mp3"));
  return result;
}


// Возвращает название трека.
QString DeejayDeFetcherPrivate::getTitleTrack(const QWebElement &element)
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

  return titleTrack.replace("&amp;", "&").replace("\"", "");
}


// Возвращает треклист.
QStringList DeejayDeFetcherPrivate::getTrackList(const QWebElement &element,
                                                 const QString& params)
{
  QWebElementCollection linksCollection = element.findAll("a.track");

  QStringList result;
  QStringList list;
  foreach (QWebElement linkElement, linksCollection) {
    QString hrefMp3 = getLinkTrack(linkElement, params);
    QString titleTrack = getTitleTrack(linkElement);
    list << hrefMp3 << titleTrack;
    result << list;
    list.clear();
  }

  return result;
}


//**************************  DeejayDeFetcher  *********************************//


DeejayDeFetcher::DeejayDeFetcher(QObject *parent)
{
  p_d = new DeejayDeFetcherPrivate;
}


DeejayDeFetcher::~DeejayDeFetcher()
{
  delete p_d;
}


void DeejayDeFetcher::setAlbumFetcher(DeejayDeAlbumFetcher *fetcher)
{
  p_d->albumFetcher = fetcher;
}


void DeejayDeFetcher::result(bool ok)
{
  m_isStop = false;
  p_d->trackDataList.clear();

  QWebElementCollection vinylCollection =
    m_page.mainFrame()->findAllElements("article.clearfix.product.notangemeldet");
  qDebug() << vinylCollection.count();

  // Если нет элементов на странице завершает выборку.
  if (vinylCollection.count() == 0) {
    emit fetched(Fetcher::NoElements);
    return;
  }

  // Обрабатывает каждый элемент коллекции.
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
  pause(m_delay);

  emit ready(p_d->trackDataList);
  emit fetched(Fetcher::Finished);
}



void DeejayDeFetcher::handleElement(const QWebElement& element)
{
  // Определяет количество треков в альбоме.
  int countTracks = p_d->getCountTracksRelease(element);

  // Если в альбоме не определено количество треков.
  if (countTracks == -1) {
      p_d->linkRelease = p_d->getLinkRelease(element);
      return;
  }

  // Если в альбоме больше 4 треков, производит разбор с помощью выборщика альбомов.
  if (countTracks > 4) {
      p_d->linkRelease = p_d->getLinkRelease(element);
      pause(m_delay);
      p_d->albumFetcher->start("http://www.deejay.de/content.php?param=" + p_d->linkRelease);

      // Остается в цикле пока не произведется выборка альбома.
      QEventLoop wait;
      connect(p_d->albumFetcher, SIGNAL(fetched(Fetcher::State)),
              &wait, SLOT(quit()));
      wait.exec();

      // Если результат выборки альбома не нулевой добавляет его в
      // результирующий список треков.
      QList <TrackInfo> albumFetchedList =
                                 p_d->albumFetcher->getFetchedTrackInfoList();
      if (!albumFetchedList.isEmpty())
        p_d->trackDataList.append(albumFetchedList);
  }
  // Если в альбоме не больше 4 треков.
  else {
      // Проверяет заголовок группы текущей даты релиза "Выпуски от dd.MM.yyyy".
      p_d->releaseDate = p_d->getDateReleaseGroup(element.previousSibling());
      // Определяет дату релиза.
      QDate date = p_d->getDateRelease(element);

      // Если дата в релизе не указана, присваивает дату заголовка.
      if (!date.isValid()) {
        qDebug() << "no date";
        date = p_d->releaseDate;
      }

      QString artist = p_d->getArtist(element);
      QString album = p_d->getTitle(element);
      QString label = p_d->getLabel(element);
      QString catNumber = p_d->getCatNumber(element);
      QString picLink = p_d->getPicLinkRelease(element);
      QString style = p_d->getStyle(element);

      if (picLink.isEmpty()) {
        p_d->linkRelease = p_d->getLinkRelease(element);
        return;
      }

      QStringList trackList = p_d->getTrackList(element, picLink);

      for (int i = 0; i < trackList.size(); i = i + 2) {
          TrackInfo track;
          track.setData(TrackInfo::Link, trackList.at(i));
          track.setData(TrackInfo::Title, trackList.at(i + 1));
          track.setData(TrackInfo::Style, style);
          track.setData(TrackInfo::AlbumArtist, artist);
          track.setData(TrackInfo::AlbumTitle, album);
          track.setData(TrackInfo::CatNumber, catNumber);
          track.setData(TrackInfo::Publisher, label);
          track.setData(TrackInfo::Date, date);

          p_d->trackDataList.push_back(track);
      }
  }
}

