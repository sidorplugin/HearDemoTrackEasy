#ifndef MODEL_H
#define MODEL_H

#include "dataclasses/albuminfo.h"

#include <QObject>
#include <QDebug>
#include <QSqlQueryModel>
#include <QSqlRecord>

// Модель Model является оберткой QSqlQueryModel с добавлением полей
// и методов обеспечивающих хранение и выдачу информации о ходе закачки файлов.


class Model : public QSqlQueryModel
{
public:
  Model() {}

  // Добавляет трек в модель.
  void add(AlbumInfo& album);
  // Удаляет все треки из модели.
  void remove();
  // Удаляет трек из модели.
  void remove(AlbumInfo& track);
  // Возвращает информацию об альбоме по значению строки.
  AlbumInfo getAlbumInfo(int row);
  // Возвращает true если модель пуста.
  bool isEmpty() const;
  // Устанавливает значение прогресса для ссылки.
  void setProgress(const QString& href, int value);
  // Производит выборку элементов в базе для представления.
  void select();



public:
  // Возвращает данные по индексу и роли. Переопределен.
  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

public slots:
  // Добавляет список треков в модель.
  void add(const QList<AlbumInfo>& albums);

private:
  void setHeaders(const QStringList &headers);
  bool insertAlbumToDb(AlbumInfo &album);
  bool insertTracksToDb(int id, const QVariantHash& tracks);
  bool insertTrackToDb(int id, const QString& title, const QString& link);

private:
  // Таблица "href - %".
  QHash <QString, int> m_table;

};

#endif // MODEL_H
