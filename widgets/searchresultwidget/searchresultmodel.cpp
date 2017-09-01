#include "searchresultmodel.h"

#include <QDebug>

SearchResultModel::SearchResultModel()
{
  // Создает заголовки модели.
  for (int i = AlbumInfo::Artist; i <= AlbumInfo::Source; ++i) {
    setHorizontalHeaderItem(i, new QStandardItem(name(i)));
  }
  setHeaderData(0, Qt::Horizontal, false,  Qt::CheckStateRole);
}


// Добавляет трек в модель.
void SearchResultModel::add(AlbumInfo &track)
{
  insertRow(0);
  setData(index(0, AlbumInfo::Artist), false, Qt::CheckStateRole);
  item(0, AlbumInfo::Artist)->setCheckable(true);

  for (int i = AlbumInfo::Artist; i <= AlbumInfo::Source; ++i) {
      setData(index(0, i), track.data(i).toString());
      item(0, i)->setEditable(false);
  }
}


// Возвращает информацию о треке по номеру строки.
AlbumInfo SearchResultModel::getTrackInfo(int row)
{
  // Считывает запись из модели по index.
  QString artist =    data(index(row, AlbumInfo::Artist))   .toString();
  QString title =     data(index(row, AlbumInfo::Title))    .toString();
//  QString album =     data(index(row, AlbumInfo::Album))    .toString();
  QString style =     data(index(row, AlbumInfo::Style))    .toString();
  QString catalog =   data(index(row, AlbumInfo::Catalog))  .toString();
  QString label =     data(index(row, AlbumInfo::Label))    .toString();
  QString date =      data(index(row, AlbumInfo::Date))     .toString();
//  QString linkTrack = data(index(row, AlbumInfo::LinkTrack)).toString();
//  QString linkImage = data(index(row, AlbumInfo::LinkImage)).toString();
  QString source =    data(index(row, AlbumInfo::Source))   .toString();

  // С помощью определенного ранее индекса получает доступ к данным модели.
  // Заполняет ими структуру AlbumInfo.
  AlbumInfo track;
  track.setData(AlbumInfo::Artist,    artist);
  track.setData(AlbumInfo::Title,     title);
//  track.setData(AlbumInfo::Album,     album);
  track.setData(AlbumInfo::Style,     style);
  track.setData(AlbumInfo::Catalog,   catalog);
  track.setData(AlbumInfo::Label,     label);
  track.setData(AlbumInfo::Date,      date);
//  track.setData(AlbumInfo::LinkTrack, linkTrack);
//  track.setData(AlbumInfo::LinkImage, linkImage);
  track.setData(AlbumInfo::Source,    source);

  return track;
}


// Возвращает true если элемент в строке row выделен.
bool SearchResultModel::isCheckedState(int row)
{
  return data(index(row, AlbumInfo::Artist), Qt::CheckStateRole).toBool();
}


// Возвращает строковое значение перечисления Items.
QString SearchResultModel::name(int key)
{
  QString name;

  switch (key) {
    case AlbumInfo::Artist :      name = "Артист";             break;
    case AlbumInfo::Title :       name = "Название";           break;
//    case AlbumInfo::Album :       name = "Альбом";             break;
    case AlbumInfo::Style :       name = "Стиль";              break;
    case AlbumInfo::Catalog :     name = "Каталог";            break;
    case AlbumInfo::Label :       name = "Лэйбл";              break;
    case AlbumInfo::Date :        name = "Дата";               break;
//    case AlbumInfo::LinkTrack :   name = "Ссылка Трек";        break;
//    case AlbumInfo::LinkImage :   name = "Ссылка Изображение"; break;
    case AlbumInfo::Source :      name = "Источник";           break;
  }

  return name;
}

