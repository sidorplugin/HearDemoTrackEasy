#include "model.h"
#include "database.h"


// Производит выборку элементов в базе для представления.
void Model::select()
{
  setQuery("SELECT t.title, a.artist, a.title, a.style, a.catalog, "
           "a.label, a.date, t.link, a.images, a.source, a.id "
           "FROM albums as a JOIN tracks as t ON a.id = t.album_id");

  setHeaders(QStringList() << trUtf8("Трек")
                           << trUtf8("Артист")
                           << trUtf8("Альбом")
                           << trUtf8("Стиль")
                           << trUtf8("Каталог")
                           << trUtf8("Лэйбл")
                           << trUtf8("Дата")
                           << trUtf8("Ссылка")
                           << trUtf8("Обложки")
                           << trUtf8("Источник")
                           << trUtf8("Альбом_id")
       );

}


void Model::setHeaders(const QStringList &headers)
{
  for (int i = 0, j = 0; i < columnCount(); i++, j++) {
      setHeaderData(i, Qt::Horizontal, headers.at(j));
    }
}



// Добавляет список треков в модель.
void Model::add(const QList<AlbumInfo> &albums)
{
  foreach (AlbumInfo album, albums) {
    add(album);
  }
}


// Добавляет трек в модель.
void Model::add(AlbumInfo &album)
{
  qDebug() << " Model::add()";

  // Если данные об альбоме вставлены в базу успешно, вставляем данные о треках.
  if (insertAlbumToDb(album)) {
      int id = album.data(AlbumInfo::Id).toInt();
      QVariantHash tracks = album.data(AlbumInfo::Tracks).toHash();
      if (insertTracksToDb(id, tracks)) {
        select();
      }
      else {
        qDebug() << "error insert into tracks";
        return;
      }
  }
  // Иначе предупреждение об ошибке вставки альбома.
  else {
    qDebug() << "error insert into albums";
    return;
  }
}


bool Model::insertAlbumToDb(AlbumInfo &album)
{
  int id = album.data(AlbumInfo::Id).toInt();
  QString artist = album.data(AlbumInfo::Artist).toString();
  QString title = album.data(AlbumInfo::Title).toString();
  QString style = album.data(AlbumInfo::Style).toString();
  QString catalog = album.data(AlbumInfo::Catalog).toString();
  QString label = album.data(AlbumInfo::Label).toString();
  QString date = album.data(AlbumInfo::Date).toString();
  QStringList images = album.data(AlbumInfo::Images).toStringList();
  QVariantHash tracks = album.data(AlbumInfo::Tracks).toHash();
  QString source = album.data(AlbumInfo::Source).toString();

  QSqlQuery query;
  query.prepare("INSERT INTO albums (id, artist, title, style, catalog, "
                                     "label, date, images, source) "
                "VALUES (:id, :artist, :title, :style, :catalog, :label, "
                        ":date, :images, :title)");
  query.bindValue(":id", id);
  query.bindValue(":artist", artist);
  query.bindValue(":title", title);
  query.bindValue(":style", style);
  query.bindValue(":catalog", catalog);
  query.bindValue(":label", label);
  query.bindValue(":date", date);
  query.bindValue(":images", images.join(";"));
  query.bindValue(":source", source);

  if (query.exec()) {
    setQuery(query);
    return true;
  }

  qDebug() << query.lastError().text();
  return false;
}



bool Model::insertTracksToDb(int id, const QVariantHash &tracks)
{
  QHashIterator<QString, QVariant> i(tracks);
  while (i.hasNext()) {
      i.next();
      if (!insertTrackToDb(id, i.key(), i.value().toString()))
        return false;
  }

  return true;
}


bool Model::insertTrackToDb(int id, const QString &title, const QString &link)
{
  QSqlQuery query;
  query.prepare("INSERT INTO tracks (title, link, album_id)"
                "VALUES (:title, :link, :album_id)");
  query.bindValue(":title", title);
  query.bindValue(":link", link);
  query.bindValue(":album_id", id);

  if (query.exec()) {
      setQuery(query);
      return true;
  }

  qDebug() << query.lastError().text();
  return false;
}


// Удаляет все треки из модели.
void Model::remove()
{
  QSqlQuery query;
  if(query.exec("DELETE FROM tracks")) {
      setQuery(query);
      if(query.exec("DELETE FROM albums")) {
          setQuery(query);
          select();
          return;
      }
  }
  qWarning() << "Failure to clear database " << query.lastError().text();
}


// Удаляет трек из модели.
void Model::remove(AlbumInfo& track)
{
  QString link = track.data(AlbumInfo::Tracks).toHash().values().at(0).toString();

  QSqlQuery query;
  if(query.exec("DELETE FROM tracks WHERE link = '" + link + "'")) {
      setQuery(query);
      select();
      return;
  }

  qWarning() << query.lastError();
}


// Возвращает информацию об альбоме по значению строки.
AlbumInfo Model::getAlbumInfo(int row)
{
  QSqlRecord record = this->record(row);

  AlbumInfo album;
  album.setData(AlbumInfo::Id, record.value(10));
  album.setData(AlbumInfo::Artist, record.value(1));
  album.setData(AlbumInfo::Title, record.value(2));
  album.setData(AlbumInfo::Style, record.value(3));
  album.setData(AlbumInfo::Catalog, record.value(4));
  album.setData(AlbumInfo::Label, record.value(5));
  album.setData(AlbumInfo::Date, record.value(6));
  album.setData(AlbumInfo::Images, record.value(8).toString().split(";"));

  QString title = record.value(0).toString();
  QString link = record.value(7).toString();
  QVariantHash tracks;
  tracks.insert(title, link);
  album.setData(AlbumInfo::Tracks, tracks);
  album.setData(AlbumInfo::Source, record.value(9));

  return album;
}


// Возвращает true если модель пуста.
bool Model::isEmpty() const
{
  return (rowCount() == 0);
}


// Возвращает данные по индексу и роли. Переопределен.
QVariant Model::data(const QModelIndex &index, int role) const
{
  // Для роли AccessibleTextRole возвращает значение прогресса загрузки.
  if (role == Qt::AccessibleTextRole) {
    QString href = index.data().toString();
    return m_table.value(href);
  }

  return QSqlQueryModel::data(index, role);
}


// Устанавливает значение прогресса для ссылки.
void Model::setProgress(const QString &href, int value)
{
  // Сохраняет значение в таблице.
  m_table.insert(href, value);

//  submitAll();
}
