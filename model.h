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
  Model() {}

  // Добавляет медиа-информацию в модель.
  void add(MediaInfo& media);
  // Удаляет все треки из модели.
  void remove();
  // Удаляет медиа-информацию из модели.
  void remove(MediaInfo& media);
  // Возвращает информацию об альбоме по значению строки.
  MediaInfo mediaInfo(int row);
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
  // Добавляет список медиа-информации в модель.
  void add(const QList<MediaInfo>& mediaList);

private:
  // Таблица "href - %".
  QHash <QString, int> m_table;

};

#endif // MODEL_H
