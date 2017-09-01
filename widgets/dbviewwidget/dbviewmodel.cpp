#include "dbviewmodel.h"
#include "database.h"

DbViewModel::DbViewModel()
{
}


// Добавляет список треков в модель.
void DbViewModel::add(const QList<AlbumInfo> &tracks)
{
  foreach (AlbumInfo track, tracks)
    add(track);
}


// Добавляет трек в модель.
void DbViewModel::add(AlbumInfo &track)
{
  // TODO Запросы такого типа model.setQuery("INSERT INTO album
  // VALUES (4,'Nilsen', 'Johan', 'Bakken 2', 'Stavanger')");
//  insertRow(0);
//  setData(index(0, 0), track.data(AlbumInfo::Artist).toString());
//  setData(index(0, 1), track.data(AlbumInfo::Title).toString());
//  setData(index(0, 2), track.data(AlbumInfo::Album).toString());
//  setData(index(0, 3), track.data(AlbumInfo::Style).toString());
//  setData(index(0, 4), track.data(AlbumInfo::Catalog).toString());
//  setData(index(0, 5), track.data(AlbumInfo::Label).toString());
//  setData(index(0, 6), track.data(AlbumInfo::Date).toString());
//  setData(index(0, 7), track.data(AlbumInfo::LinkTrack).toString());
//  setData(index(0, 8), track.data(AlbumInfo::LinkImage).toString());

  if (!submitAll())
    qDebug() << lastError();
}


// Удаляет все треки из модели.
void DbViewModel::remove()
{
  QSqlQuery query(database());
  if(!query.exec("DELETE FROM " + TABLE_NAME)) {
    qWarning() << "Failure to clear database " << query.lastError().text();
  }
  submitAll();
}


// Удаляет трек из модели.
void DbViewModel::remove(AlbumInfo &track)
{
  QString link = /*track.data(AlbumInfo::LinkTrack).toString()*/"";

  QSqlQuery query(database());
  if(!query.exec("DELETE FROM " + TABLE_NAME +
                 " WHERE  link_track = '" + link + "'")) {
      qWarning() << query.lastError();
  }
  submitAll();

}


// Возвращает информацию о треке по индексу.
AlbumInfo DbViewModel::getTrackInfo(int index)
{
  // Считывает запись из модели по index.
  QSqlRecord record = this->record(index);

  // Определяет индекс по имени столбца.
  int artistIndex = this->record(index).indexOf("artist");
  int titleIndex = this->record(index).indexOf("title");
  int albumIndex = this->record(index).indexOf("album");
  int styleIndex = this->record(index).indexOf("style");
  int catalogIndex = this->record(index).indexOf("catalog");
  int labelIndex = this->record(index).indexOf("label");
  int dateIndex = this->record(index).indexOf("date");
  int linkTrackIndex = this->record(index).indexOf("link_track");
  int linkImageIndex = this->record(index).indexOf("link_image");

  // С помощью определенного ранее индекса получает доступ к данным модели.
  // Заполняет ими структуру AlbumInfo.
  AlbumInfo track;
  track.setData(AlbumInfo::Artist, record.value(artistIndex).toString());
  track.setData(AlbumInfo::Title, record.value(titleIndex).toString());
//  track.setData(AlbumInfo::Album, record.value(albumIndex).toString());
  track.setData(AlbumInfo::Style, record.value(styleIndex).toString());
  track.setData(AlbumInfo::Catalog, record.value(catalogIndex).toString());
  track.setData(AlbumInfo::Label, record.value(labelIndex).toString());
  track.setData(AlbumInfo::Date, record.value(dateIndex).toString());
//  track.setData(AlbumInfo::LinkTrack, record.value(linkTrackIndex).toString());
//  track.setData(AlbumInfo::LinkImage, record.value(linkImageIndex).toString());

  return track;
}


// Возвращает true если модель пуста.
bool DbViewModel::isEmpty() const
{
  return (rowCount() == 0);
}


// Возвращает данные по индексу и роли. Переопределен.
QVariant DbViewModel::data(const QModelIndex &index, int role) const
{
  // Для роли AccessibleTextRole возвращает значение прогресса загрузки.
  if (role == Qt::AccessibleTextRole) {
    QString href = index.data().toString();
    return m_table.value(href);
  }

  return QSqlTableModel::data(index, role);
}


// Устанавливает значение прогресса для ссылки.
void DbViewModel::setProgress(const QString &href, int value)
{
  // Сохраняет значение в таблице.
  m_table.insert(href, value);

  submitAll();
}
