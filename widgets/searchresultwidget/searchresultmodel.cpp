#include "searchresultmodel.h"

#include <QDebug>

SearchResultModel::SearchResultModel()
{
  // Создает заголовки модели.
  for (int i = MediaInfo::Artist; i <= MediaInfo::Source; ++i) {
    setHorizontalHeaderItem(i, new QStandardItem(name(i)));
  }
  setHeaderData(0, Qt::Horizontal, false,  Qt::CheckStateRole);
}


// Добавляет трек в модель.
void SearchResultModel::add(MediaInfo &track)
{
  insertRow(0);
  setData(index(0, MediaInfo::Artist), false, Qt::CheckStateRole);
  item(0, MediaInfo::Artist)->setCheckable(true);

  for (int i = MediaInfo::Artist; i <= MediaInfo::Source; ++i) {
      setData(index(0, i), track.data(i).toString());
      item(0, i)->setEditable(false);
  }
}


// Возвращает информацию о треке по номеру строки.
MediaInfo SearchResultModel::getAlbumInfo(int row)
{
  // Считывает запись из модели по index.
  QString artist =    data(index(row, MediaInfo::Artist))   .toString();
  QString title =     data(index(row, MediaInfo::Title))    .toString();
//  QString album =     data(index(row, MediaInfo::Album))    .toString();
  QString style =     data(index(row, MediaInfo::Style))    .toString();
  QString catalog =   data(index(row, MediaInfo::Catalog))  .toString();
  QString label =     data(index(row, MediaInfo::Label))    .toString();
  QString date =      data(index(row, MediaInfo::Date))     .toString();
//  QString linkTrack = data(index(row, MediaInfo::LinkTrack)).toString();
//  QString linkImage = data(index(row, MediaInfo::LinkImage)).toString();
  QString source =    data(index(row, MediaInfo::Source))   .toString();

  // С помощью определенного ранее индекса получает доступ к данным модели.
  // Заполняет ими структуру MediaInfo.
  MediaInfo track;
  track.setData(MediaInfo::Artist,    artist);
  track.setData(MediaInfo::Title,     title);
//  track.setData(MediaInfo::Album,     album);
  track.setData(MediaInfo::Style,     style);
  track.setData(MediaInfo::Catalog,   catalog);
  track.setData(MediaInfo::Label,     label);
  track.setData(MediaInfo::Date,      date);
//  track.setData(MediaInfo::LinkTrack, linkTrack);
//  track.setData(MediaInfo::LinkImage, linkImage);
  track.setData(MediaInfo::Source,    source);

  return track;
}


// Возвращает true если элемент в строке row выделен.
bool SearchResultModel::isCheckedState(int row)
{
  return data(index(row, MediaInfo::Artist), Qt::CheckStateRole).toBool();
}


// Возвращает строковое значение перечисления Items.
QString SearchResultModel::name(int key)
{
  QString name;

  switch (key) {
    case MediaInfo::Artist :      name = "Артист";             break;
    case MediaInfo::Title :       name = "Название";           break;
//    case MediaInfo::Album :       name = "Альбом";             break;
    case MediaInfo::Style :       name = "Стиль";              break;
    case MediaInfo::Catalog :     name = "Каталог";            break;
    case MediaInfo::Label :       name = "Лэйбл";              break;
    case MediaInfo::Date :        name = "Дата";               break;
//    case MediaInfo::LinkTrack :   name = "Ссылка Трек";        break;
//    case MediaInfo::LinkImage :   name = "Ссылка Изображение"; break;
    case MediaInfo::Source :      name = "Источник";           break;
  }

  return name;
}

