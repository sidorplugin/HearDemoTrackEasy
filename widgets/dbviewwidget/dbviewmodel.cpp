#include "dbviewmodel.h"
#include "database.h"

DbViewModel::DbViewModel()
{
}


// Добавляет список треков в модель.
void DbViewModel::add(const QList<TrackInfo> &tracks)
{
  foreach (TrackInfo track, tracks)
    add(track);
}


// Добавляет трек в модель.
void DbViewModel::add(TrackInfo &track)
{
  insertRow(0);
  setData(index(0, 0), track.data(TrackInfo::Artist).toString());
  setData(index(0, 1), track.data(TrackInfo::Title).toString());
  setData(index(0, 2), track.data(TrackInfo::Album).toString());
  setData(index(0, 3), track.data(TrackInfo::Style).toString());
  setData(index(0, 4), track.data(TrackInfo::Catalog).toString());
  setData(index(0, 5), track.data(TrackInfo::Label).toString());
  setData(index(0, 6), track.data(TrackInfo::Date).toString());
  setData(index(0, 7), track.data(TrackInfo::LinkTrack).toString());
  setData(index(0, 8), track.data(TrackInfo::LinkImage).toString());

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
void DbViewModel::remove(TrackInfo &track)
{
  QString link = track.data(TrackInfo::LinkTrack).toString();

  QSqlQuery query(database());
  if(!query.exec("DELETE FROM " + TABLE_NAME +
                 " WHERE  link_track = '" + link + "'")) {
      qWarning() << query.lastError();
  }
  submitAll();

}


// Возвращает информацию о треке по индексу.
TrackInfo DbViewModel::getTrackInfo(int index)
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
  // Заполняет ими структуру TrackInfo.
  TrackInfo track;
  track.setData(TrackInfo::Artist, record.value(artistIndex).toString());
  track.setData(TrackInfo::Title, record.value(titleIndex).toString());
  track.setData(TrackInfo::Album, record.value(albumIndex).toString());
  track.setData(TrackInfo::Style, record.value(styleIndex).toString());
  track.setData(TrackInfo::Catalog, record.value(catalogIndex).toString());
  track.setData(TrackInfo::Label, record.value(labelIndex).toString());
  track.setData(TrackInfo::Date, record.value(dateIndex).toString());
  track.setData(TrackInfo::LinkTrack, record.value(linkTrackIndex).toString());
  track.setData(TrackInfo::LinkImage, record.value(linkImageIndex).toString());

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
