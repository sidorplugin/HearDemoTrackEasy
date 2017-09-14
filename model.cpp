#include "model.h"
#include "database.h"

Model::Model()
{
}


// Добавляет список треков в модель.
void Model::add(const QList<MediaInfo> &mediaList)
{
    foreach (MediaInfo media, mediaList) {
        add(media);
    }
}


// Добавляет медиа-информацию в модель.
void Model::add(MediaInfo &media)
{
    QVariantHash tracks = media.data(MediaInfo::Tracks).toHash();

    QHashIterator<QString, QVariant>it(tracks);
    while (it.hasNext()) {
        it.next();

        insertRow(0);

        int idTrack = it.key().toInt();
        QString titleTrack = it.value().toStringList().at(0);
        QString linkTrack = it.value().toStringList().at(1);

        setData(index(0, 0), idTrack);
        setData(index(0, 1), media.data(MediaInfo::Id_Album).toInt());
        setData(index(0, 2), media.data(MediaInfo::Artist).toString());
        setData(index(0, 3), titleTrack);
        setData(index(0, 4), media.data(MediaInfo::Title_Album).toString());
        setData(index(0, 5), media.data(MediaInfo::Style).toString());
        setData(index(0, 6), media.data(MediaInfo::Catalog).toString());
        setData(index(0, 7), media.data(MediaInfo::Label).toString());
        setData(index(0, 8), media.data(MediaInfo::Date).toString());
        setData(index(0, 9), media.data(MediaInfo::Images).toString());
        setData(index(0, 10), linkTrack);
        setData(index(0, 11), media.data(MediaInfo::Link_Album).toString());
        setData(index(0, 12), media.data(MediaInfo::Source).toString());

        if (!submitAll()) {
          qDebug() << lastError();
          qDebug() << "----------------Don't add track-----------------------";
          qDebug() << media.toStringList();
          removeRow(0);
        }
    }
}


// Удаляет все треки из модели.
void Model::remove()
{
    QSqlQuery query(database());
    if(!query.exec("DELETE FROM tracks")) {
        qWarning() << "Failure to clear database " << query.lastError().text();
    }
    submitAll();
}


// Удаляет трек из модели.
void Model::remove(MediaInfo& media)
{
    int idTrack  = media.data(MediaInfo::Id_Track).toInt();

    QSqlQuery query(database());
    if(!query.exec("DELETE FROM tracks WHERE id_track =" + QString::number(idTrack))) {
        qWarning() << query.lastError();
    }
    submitAll();
}


// Возвращает информацию об альбоме по значению строки.
MediaInfo Model::mediaInfo(int row)
{
    // Считывает запись из модели по index.
    QSqlRecord record = this->record(row);

    // Определяет индекс по имени столбца.
    int idTrackIndex    = this->record(row).indexOf("id_track");
    int idAlbumIndex    = this->record(row).indexOf("id_album");
    int artistIndex     = this->record(row).indexOf("artist");
    int titleTrackIndex = this->record(row).indexOf("title_track");
    int titleAlbumIndex = this->record(row).indexOf("title_album");
    int styleIndex      = this->record(row).indexOf("style");
    int catalogIndex    = this->record(row).indexOf("catalog");
    int labelIndex      = this->record(row).indexOf("label");
    int dateIndex       = this->record(row).indexOf("date");
    int imagesIndex     = this->record(row).indexOf("images");
    int linkTrackIndex  = this->record(row).indexOf("link_track");
    int linkAlbumIndex  = this->record(row).indexOf("link_album");
    int sourceIndex     = this->record(row).indexOf("source");

    // С помощью определенного ранее индекса получает доступ к данным модели.
    // Заполняет ими структуру MediaInfo.
    MediaInfo media;
    media.setData(MediaInfo::Id_Track, record.value(idTrackIndex).toInt());
    media.setData(MediaInfo::Id_Album, record.value(idAlbumIndex).toInt());
    media.setData(MediaInfo::Artist, record.value(artistIndex).toString());
    media.setData(MediaInfo::Title_Track, record.value(titleTrackIndex).toString());
    media.setData(MediaInfo::Title_Album, record.value(titleAlbumIndex).toString());
    media.setData(MediaInfo::Style, record.value(styleIndex).toString());
    media.setData(MediaInfo::Catalog, record.value(catalogIndex).toString());
    media.setData(MediaInfo::Label, record.value(labelIndex).toString());
    media.setData(MediaInfo::Date, record.value(dateIndex).toString());
    media.setData(MediaInfo::Images, record.value(imagesIndex).toString());
    media.setData(MediaInfo::Link_Track, record.value(linkTrackIndex).toString());
    media.setData(MediaInfo::Link_Album, record.value(linkAlbumIndex).toString());
    media.setData(MediaInfo::Source, record.value(sourceIndex).toString());

    return media;
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
        QString href = record(index.row()).value(MediaInfo::Link_Track).toString();

        return m_table.value(href);
    }

    return QSqlTableModel::data(index, role);
}


// Устанавливает значение прогресса для ссылки.
void Model::setProgress(const QString &href, int value)
{
    // Сохраняет значение в таблице.
    m_table.insert(href, value);

    submitAll();
}


// Фильтрует модель по колонке column и значению value.
void Model::updateFilter(int column, const QString &value)
{
  QString filter;

  // Если поле в фильтре пустое сбрасывает фильтр модели.
  if (value.isEmpty()) {
      filter = QString();
  }
  else
    // В зависимости от column формирует запрос на выборку элементов
    // модели по колонке и значению.
    filter = QString("%1 LIKE '%%2%' ORDER BY 'id_album'").
                         arg(nameFieldForColumn(column)).arg(value);

  // Устанавливает фильтр для модели.
  setFilter(filter);
  // Выбирает элементы из модели.
  select();

}


// Возвращает название поля в БД по колонке column.
QString Model::nameFieldForColumn(int column)
{
  QString name;
  switch (column) {
    case MediaInfo::Id_Album :         name = "id_album";         break;
    case MediaInfo::Id_Track :         name = "id_track";         break;
    case MediaInfo::Artist :           name = "artist";           break;
    case MediaInfo::Title_Album :      name = "title_album";      break;
    case MediaInfo::Title_Track :      name = "title_track";      break;
    case MediaInfo::Style :            name = "style";            break;
    case MediaInfo::Catalog :          name = "catalog";          break;
    case MediaInfo::Label :            name = "label";            break;
    case MediaInfo::Date :             name = "date";             break;
    case MediaInfo::Images :           name = "images";           break;
    case MediaInfo::Link_Track :       name = "link_track";       break;
    case MediaInfo::Link_Album :       name = "link_album";       break;
    case MediaInfo::Source :           name = "source";           break;
  }
  return name;
}
