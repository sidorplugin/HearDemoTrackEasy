#ifndef ALBUMINFO_H
#define ALBUMINFO_H

#include <QHash>
#include <QMediaMetaData>
#include <QString>
#include <QDebug>

// Класс AlbumInfo хранит информацию об альбоме.

class AlbumInfo
{
public:
  enum Key { Id,           // Уникальный id альбома (qHash(Artist + Title)).
             Artist,       // Артист.
             Title,        // Название aльбома.
             Style,        // Стиль.
             Catalog,      // Номер по каталогу.
             Label,        // Лэйбл выпустивший альбом.
             Date,         // Дата выпуска альбома.
             Images,       // Ссылки на изображения.
             Tracks,       // Треки.
             Source        // Ресурс.
           };

//  AlbumInfo(){}

  // Устанавливает значение value по ключу key.
  void setData(int key, const QVariant& value);
  // Возвращает значение по ключу key.
  QVariant data(int key);
  // Возвращает строковое значение информации о треке в виде списка.
  QStringList toStringList() const;
  // Очищает все поля в альбоме.
  void clear();
  // Проверяет на наличие информации в альбоме.
  bool isEmpty();


private:
  // Возвращает строковое значение ключа.
  QString keyToString(int key) const;


private:
  QHash <int, QVariant> m_data;

};

Q_DECLARE_METATYPE(AlbumInfo)


#endif // ALBUMINFO_H
