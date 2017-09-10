#include "searchresultmodel.h"

#include <QDebug>
#include <QDate>

SearchResultModel::SearchResultModel()
{
  // Создает заголовки модели.
  for (int i = MediaInfo::Id_Track; i <= MediaInfo::Source; ++i) {
    setHorizontalHeaderItem(i, new QStandardItem(MediaInfo::name(i)));
  }
  setHeaderData(0, Qt::Horizontal, false,  Qt::CheckStateRole);
}


// Добавляет медиа информацию в модель.
void SearchResultModel::add(MediaInfo &media)
{
  // Получает все треки из media.
  QVariantHash tracks = media.data(MediaInfo::Tracks).toHash();
  // Для каждого трека добавляет информацию в таблицу.
  QHashIterator<QString, QVariant>it(tracks);
  while (it.hasNext()) {
      it.next();
      int idTrack = it.key().toInt();
      QString titleTrack = it.value().toStringList().at(0);
      QString linkTrack = it.value().toStringList().at(1);

      insertRow(0);
      // Для  каждого столбца устанавливает данные.
      for (int i = MediaInfo::Id_Track; i <= MediaInfo::Source; ++i) {
          if (i == MediaInfo::Id_Track) {
              setData(index(0, i), idTrack);
          }
          else if (i == MediaInfo::Title_Track) {
              setData(index(0, i), titleTrack);
              item(0, i)->setEditable(false);
          }
          else if (i == MediaInfo::Link_Track) {
              setData(index(0, i), linkTrack);
              item(0, i)->setEditable(false);
          }
          else if (i == MediaInfo::Artist) {
              setData(index(0, i), false, Qt::CheckStateRole);
              item(0, i)->setCheckable(true);
          }
          else {
              setData(index(0, i), media.data(i).toString());
              item(0, i)->setEditable(false);
          }
      }
  }

}


// Возвращает информацию о треке по номеру строки.
MediaInfo SearchResultModel::mediaInfo(int row)
{
  int     idTrack =    data(index(row, MediaInfo::Id_Track))   .toInt();
  int     idAlbum =    data(index(row, MediaInfo::Id_Album))   .toInt();
  QString artist =     data(index(row, MediaInfo::Artist))     .toString();
  QString titleTrack = data(index(row, MediaInfo::Title_Track)).toString();
  QString titleAlbum = data(index(row, MediaInfo::Title_Album)).toString();
  QString style =      data(index(row, MediaInfo::Style))      .toString();
  QString catalog =    data(index(row, MediaInfo::Catalog))    .toString();
  QString label =      data(index(row, MediaInfo::Label))      .toString();
  QString date =       data(index(row, MediaInfo::Date))       .toString();
  QString images =     data(index(row, MediaInfo::Images))     .toString();
  QString linkTrack =  data(index(row, MediaInfo::Link_Track)) .toString();
  QString linkAlbum =  data(index(row, MediaInfo::Link_Album)) .toString();
  QString source =     data(index(row, MediaInfo::Source))     .toString();

  MediaInfo media;
  media.setData(MediaInfo::Id_Track,    idTrack);
  media.setData(MediaInfo::Id_Album,    idAlbum);
  media.setData(MediaInfo::Artist,      artist);
  media.setData(MediaInfo::Title_Track, titleTrack);
  media.setData(MediaInfo::Title_Album, titleAlbum);
  media.setData(MediaInfo::Style,       style);
  media.setData(MediaInfo::Catalog,     catalog);
  media.setData(MediaInfo::Label,       label);
  media.setData(MediaInfo::Date,        QDate::fromString(date, "dd.MM.yyyy"));
  media.setData(MediaInfo::Images,      images);
  media.setData(MediaInfo::Link_Track,  linkTrack);
  media.setData(MediaInfo::Link_Album,  linkAlbum);
  media.setData(MediaInfo::Source,      source);

  return media;
}


// Возвращает true если элемент в строке row выделен.
bool SearchResultModel::isCheckedState(int row)
{
  return data(index(row, MediaInfo::Artist), Qt::CheckStateRole).toBool();
}
