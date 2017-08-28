#include "junofetcher.h"

//*************************  JunoFetcherPrivate  ****************************//
class JunoFetcherPrivate
{
public:
  QList <TrackInfo> trackDataList;

public:
  // Возвращает артиста.
  QString getArtist(const QWebElement &element);
  // Возвращает название релиза.
  QString getTitle(const QWebElement &element);
  // Возвращает лэйбл.
  QString getLabel(const QWebElement &element);
  // Возвращает номер по каталогу.
  QString getCatNumber(const QWebElement &element);
  // Возвращает ссылку на трек.
  QString getLinkTrack(const QWebElement &element, const QString& params = QString());
  // Возвращает название трека.
  QString getTitleTrack(const QWebElement &element);
  // Возвращает треклист.
  QStringList getTrackList(const QWebElement& element, const QString& params = QString());
  // Возвращает дату релиза.
  QDate getDateRelease(const QWebElement &element);

};


// Возвращает артиста.
QString JunoFetcherPrivate::getArtist(const QWebElement &element)
{
  return element.toPlainText().replace("/", ",");
}


// Возвращает название релиза.
QString JunoFetcherPrivate::getTitle(const QWebElement &element)
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
QString JunoFetcherPrivate::getLinkTrack(const QWebElement &element, const QString& params)
{
  QWebElement linkElement = element.findFirst("div.vi-icon a");
  return linkElement.attribute("href");
}


// Возвращает название трека.
QString JunoFetcherPrivate::getTitleTrack(const QWebElement &element)
{
  QWebElement titleTrackElement = element.findFirst("div.vi-text");

  QRegExp prepareRx ("[(]|[)]");
  QString title = titleTrackElement.toPlainText().replace("\"", "").replace("/", ",");
  QStringList list = title.split(prepareRx, QString::SkipEmptyParts);
  QString forRemove = list.last();
  return title.remove(" (" + forRemove + ")");
}


// Возвращает треклист.
QStringList JunoFetcherPrivate::getTrackList(const QWebElement &element, const QString& params)
{
  QStringList result;
  QStringList list;

  QWebElementCollection tracksCollection = element.findAll("li");
  if (tracksCollection.count() == 0) {
    // TODO Запись пустого релиза в logger.
  }

  foreach (QWebElement trackElement, tracksCollection) {
    QString hrefMp3 = getLinkTrack(trackElement);
    QString titleTrack = getTitleTrack(trackElement);
    list << hrefMp3 << titleTrack;
    result << list;
    list.clear();
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
  p_d->trackDataList.clear();

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

  emit ready(p_d->trackDataList);
  emit fetched(Fetcher::Finished);
}


void JunoFetcher::handleElement(const QWebElement &element)
{
  QString artist;
  QString album;
  QString catNumber;
  QDate date;
  QString label;
  QStringList trackList;

  QWebElementCollection infoCollection =
      element.findAll("div.pl-info.jq_highlight div.vi-text");
  qDebug() << infoCollection.count();
  if (infoCollection.count() < 3) return;
  else {
    artist = p_d->getArtist(infoCollection.at(0));
    album = p_d->getTitle(infoCollection.at(1));
    label = p_d->getLabel(infoCollection.at(2));
    catNumber = p_d->getCatNumber(infoCollection.at(3));
    date = p_d->getDateRelease(infoCollection.at(3));
  }
  QWebElement tracklistElement =
      element.findFirst("ol.vi-tracklist.jq_highlight");
  trackList = p_d->getTrackList(tracklistElement);

  for(int i = 0; i < trackList.size(); i = i + 2) {
      TrackInfo track;
      track.setData(TrackInfo::LinkTrack, trackList.at(i));
      track.setData(TrackInfo::Title, trackList.at(i + 1));
      track.setData(TrackInfo::Artist, artist);
      track.setData(TrackInfo::Album, album);
      track.setData(TrackInfo::Catalog, catNumber);
      track.setData(TrackInfo::Label, label);
      track.setData(TrackInfo::Date, date);
//      track.setData(TrackInfo::LinkImage, );

      p_d->trackDataList.push_back(track);
  }
}
