#ifndef MODEL_H
#define MODEL_H

#include "dataclasses/mediainfo.h"

#include <QObject>
#include <QDebug>
#include <QSqlTableModel>
#include <QSqlRecord>

// Модель Model является оберткой QSqlQueryModel с добавлением полей
// и методов обеспечивающих хранение и выдачу информации о ходе закачки файлов.


class Model : public QSqlTableModel
{
public:
  Model();

  // Добавляет медиа-информацию в модель.
  void add(const MediaInfo& media);
  // Удаляет все треки из модели.
  void remove();
  // Удаляет медиа-информацию из модели.
  void remove(MediaInfo& media);
  // Возвращает информацию о треке по строке.
  MediaInfo mediaInfo(int row);
  // Возвращает информацию о треке по id.
  MediaInfo mediaInfoById(int id);
  // Возвращает true если модель пуста.
  bool isEmpty() const;
  // Устанавливает значение прогресса для ссылки.
  void setProgress(const QString& href, int value);
  //
  QString report() const;
  //
  void fixReport();
  //
  int countAddedTracks() const;

public:
  // Возвращает данные по индексу и роли. Переопределен.
  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

public slots:
  // Добавляет список медиа-информации в модель.
  void add(const QList<MediaInfo>& mediaList);
  // Фильтрует модель по колонке column и значению value.
  void updateFilter(int column, const QString& value);
  // Возвращает название поля в БД по колонке column.
  QString nameFieldForColumn(int column);

private:
  // Таблица "href - %".
  QHash <QString, int> m_table;
  QString m_report;
  int m_countAddedTracks;

};

#endif // MODEL_H
