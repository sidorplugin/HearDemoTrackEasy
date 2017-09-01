#ifndef DBVIEWMODEL_H
#define DBVIEWMODEL_H

#include "dataclasses/albuminfo.h"

#include <QObject>
#include <QDebug>
#include <QSqlTableModel>
#include <QSqlRecord>

// Модель DbViewModel является оберткой QSqlTableModel с добавлением полей
// и методов обеспечивающих хранение и выдачу информации о ходе закачки файлов.

class DbViewModel : public QSqlTableModel
{
public:
  DbViewModel();

  // Добавляет трек в модель.
  void add(AlbumInfo& track);
  // Удаляет все треки из модели.
  void remove();
  // Удаляет трек из модели.
  void remove(AlbumInfo& track);
  // Возвращает информацию о треке по индексу.
  AlbumInfo getTrackInfo(int index);
  // Возвращает true если модель пуста.
  bool isEmpty() const;
  // Устанавливает значение прогресса для ссылки.
  void setProgress(const QString& href, int value);

public:
  // Возвращает данные по индексу и роли. Переопределен.
  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

public slots:
  // Добавляет список треков в модель.
  void add(const QList<AlbumInfo>& tracks);


private:
  // Таблица "href - %".
  QHash <QString, int> m_table;

};

#endif // DBVIEWMODEL_H
