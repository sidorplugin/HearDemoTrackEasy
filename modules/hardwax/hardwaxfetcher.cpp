#include "hardwaxfetcher.h"

//*************************  HardwaxFetcherPrivate  ****************************//
class HardwaxFetcherPrivate
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
  QString getLinkTrack(const QWebElement &element,
                       const QString& params = QString());
  // Возвращает название трека.
  QString getTitleTrack(const QWebElement &element);
  // Возвращает треклист.
  QStringList getTrackList(const QWebElement& element,
                           const QString& params = QString());

};

// Возвращает артиста.
QString HardwaxFetcherPrivate::getArtist(const QWebElement &element)
{
  QWebElement artistElement = element.findFirst("div.linebig strong a");
  return artistElement.toPlainText().section(':', 0, 0);
}


// Возвращает название релиза.
QString HardwaxFetcherPrivate::getTitle(const QWebElement &element)
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


// Возвращает название трека.
QString HardwaxFetcherPrivate::getTitleTrack(const QWebElement &element)
{
  return element.toPlainText().replace("&amp;", "&");
}


// Возвращает треклист.
QStringList HardwaxFetcherPrivate::getTrackList(const QWebElement &element,
                                                const QString& params)
{
  QStringList result;
  QStringList list;

  QWebElementCollection linksCollection = element.findAll("ul.tracklisting li a");
  if (linksCollection.count() == 0) {
    // TODO Запись пустого релиза в logger.
  }

  foreach (QWebElement linkElement, linksCollection) {
    QString hrefMp3 = getLinkTrack(linkElement);
    QString titleTrack = getTitleTrack(linkElement);
    list << hrefMp3 << titleTrack;
    result << list;
    list.clear();
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
  p_d->trackDataList.clear();

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
      QString label = p_d->getLabel(vinylElement);
      QString catNumber = p_d->getCatNumber(vinylElement);
      QString artist = p_d->getArtist(vinylElement);
      QString album = p_d->getTitle(vinylElement);
      QStringList trackList = p_d->getTrackList(vinylElement);

      QStringList list;
      for(int i = 0; i < trackList.size(); i = i + 2) {
          TrackInfo track;
          track.setData(TrackInfo::LinkTrack, trackList.at(i));
          track.setData(TrackInfo::Title, trackList.at(i + 1));
          track.setData(TrackInfo::Artist, artist);
          track.setData(TrackInfo::Album, album);
          track.setData(TrackInfo::Catalog, catNumber);
          track.setData(TrackInfo::Label, label);
//          track.setData(TrackInfo::LinkImage, trackList.at(i));

          p_d->trackDataList.push_back(track);
      }
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
