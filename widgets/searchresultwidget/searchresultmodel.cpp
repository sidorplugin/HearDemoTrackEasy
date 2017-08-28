#include "searchresultmodel.h"

#include <QDebug>

SearchResultModel::SearchResultModel()
{
  // Создает заголовки модели.
  for (int i = TrackInfo::Artist; i <= TrackInfo::LinkImage; ++i) {
    setHorizontalHeaderItem(i, new QStandardItem(name(i)));
  }
  setHeaderData(0, Qt::Horizontal, false,  Qt::CheckStateRole);
}


// Добавляет трек в модель.
void SearchResultModel::add(TrackInfo &track)
{
  insertRow(0);
  setData(index(0, TrackInfo::Artist), false, Qt::CheckStateRole);
  item(0, TrackInfo::Artist)->setCheckable(true);

  for (int i = TrackInfo::Artist; i <= TrackInfo::LinkImage; ++i) {
      setData(index(0, i), track.data(i).toString());
      item(0, i)->setEditable(false);
  }
}


// Возвращает информацию о треке по номеру строки.
TrackInfo SearchResultModel::getTrackInfo(int row)
{
  // Считывает запись из модели по index.
  QString artist =    data(index(row, TrackInfo::Artist))   .toString();
  QString title =     data(index(row, TrackInfo::Title))    .toString();
  QString album =     data(index(row, TrackInfo::Album))    .toString();
  QString style =     data(index(row, TrackInfo::Style))    .toString();
  QString catalog =   data(index(row, TrackInfo::Catalog))  .toString();
  QString label =     data(index(row, TrackInfo::Label))    .toString();
  QString date =      data(index(row, TrackInfo::Date))     .toString();
  QString linkTrack = data(index(row, TrackInfo::LinkTrack)).toString();
  QString linkImage = data(index(row, TrackInfo::LinkImage)).toString();

  // С помощью определенного ранее индекса получает доступ к данным модели.
  // Заполняет ими структуру TrackInfo.
  TrackInfo track;
  track.setData(TrackInfo::Artist,    artist);
  track.setData(TrackInfo::Title,     title);
  track.setData(TrackInfo::Album,     album);
  track.setData(TrackInfo::Style,     style);
  track.setData(TrackInfo::Catalog,   catalog);
  track.setData(TrackInfo::Label,     label);
  track.setData(TrackInfo::Date,      date);
  track.setData(TrackInfo::LinkTrack, linkTrack);
  track.setData(TrackInfo::LinkImage, linkImage);

  return track;
}


// Возвращает true если элемент в строке row выделен.
bool SearchResultModel::isCheckedState(int row)
{
  return data(index(row, TrackInfo::Artist), Qt::CheckStateRole).toBool();
}


// Возвращает строковое значение перечисления Items.
QString SearchResultModel::name(int key)
{
  QString name;

  switch (key) {
    case TrackInfo::Artist :      name = "Артист";             break;
    case TrackInfo::Title :       name = "Название";           break;
    case TrackInfo::Album :       name = "Альбом";             break;
    case TrackInfo::Style :       name = "Стиль";              break;
    case TrackInfo::Catalog :     name = "Каталог";            break;
    case TrackInfo::Label :       name = "Лэйбл";              break;
    case TrackInfo::Date :        name = "Дата";               break;
    case TrackInfo::LinkTrack :   name = "Ссылка Трек";        break;
    case TrackInfo::LinkImage :   name = "Ссылка Изображение"; break;
  }

  return name;
}

