#include "searchresultmodel.h"

#include <QDebug>

SearchResultModel::SearchResultModel()
{
  // Создает заголовки модели.
  for (int i = SearchResultModel::CheckItem; i <= SearchResultModel::DateItem; ++i) {
    setHorizontalHeaderItem(i, new QStandardItem(name(i)));
  }
}


// Добавляет трек в модель.
void SearchResultModel::add(TrackInfo &track)
{
  insertRow(0);
  setData(index(0, SearchResultModel::CheckItem), false, Qt::CheckStateRole);
  item(0, SearchResultModel::CheckItem)->setCheckable(true);

  setData(index(0, SearchResultModel::ArtistItem),
                   track.data(TrackInfo::AlbumArtist).toString());

  setData(index(0, SearchResultModel::TitleItem),
                   track.data(TrackInfo::Title).toString());

  setData(index(0, SearchResultModel::AlbumItem),
                   track.data(TrackInfo::AlbumTitle).toString());

  setData(index(0, SearchResultModel::GenreItem),
                   track.data(TrackInfo::Style).toString());

  setData(index(0, SearchResultModel::LinkItem),
                   track.data(TrackInfo::Link).toString());

  setData(index(0, SearchResultModel::CatalogItem),
                   track.data(TrackInfo::CatNumber).toString());

  setData(index(0, SearchResultModel::PublisherItem),
                   track.data(TrackInfo::Publisher).toString());

  setData(index(0, SearchResultModel::DateItem),
                   track.data(TrackInfo::Date).toString());

  for (int i = SearchResultModel::CheckItem; i <= SearchResultModel::DateItem; ++i) {
    item(0, i)->setEditable(false);
  }

}


// Возвращает информацию о треке по номеру строки.
TrackInfo SearchResultModel::getTrackInfo(int row)
{
  // Считывает запись из модели по index.
  QString artist = data(index(row, SearchResultModel::ArtistItem))   .toString();
  QString title =  data(index(row, SearchResultModel::TitleItem))    .toString();
  QString album =  data(index(row, SearchResultModel::AlbumItem))    .toString();
  QString link =   data(index(row, SearchResultModel::LinkItem))     .toString();
  QString genre =  data(index(row, SearchResultModel::GenreItem))    .toString();
  QString cat =    data(index(row, SearchResultModel::CatalogItem))  .toString();
  QString pub =    data(index(row, SearchResultModel::PublisherItem)).toString();
  QString date =   data(index(row, SearchResultModel::DateItem))     .toString();

  // С помощью определенного ранее индекса получает доступ к данным модели.
  // Заполняет ими структуру TrackInfo.
  TrackInfo track;
  track.setData(TrackInfo::Link,        link);
  track.setData(TrackInfo::Title,       title);
  track.setData(TrackInfo::Style,       genre);
  track.setData(TrackInfo::AlbumArtist, artist);
  track.setData(TrackInfo::AlbumTitle,  album);
  track.setData(TrackInfo::CatNumber,   cat);
  track.setData(TrackInfo::Publisher,   pub);
  track.setData(TrackInfo::Date,        date);

  return track;
}


// Возвращает true если элемент в строке row выделен.
bool SearchResultModel::isCheckedState(int row)
{
  return data(index(row, SearchResultModel::CheckItem),
                                        Qt::CheckStateRole).toBool();
}


// Возвращает строковое значение перечисления Items.
QString SearchResultModel::name(int key)
{
  QString name;

  switch (key) {
    case SearchResultModel::CheckItem :     name = "";               break;
    case SearchResultModel::LinkItem :      name = "Ссылка";         break;
    case SearchResultModel::TitleItem :     name = "Название";       break;
    case SearchResultModel::GenreItem :     name = "Жанр";           break;
    case SearchResultModel::ArtistItem :    name = "Артист";         break;
    case SearchResultModel::AlbumItem :     name = "Альбом";         break;
    case SearchResultModel::CatalogItem :   name = "Каталог";        break;
    case SearchResultModel::PublisherItem : name = "Лэйбл";          break;
    case SearchResultModel::DateItem :      name = "Дата";           break;
  }

  return name;
}

