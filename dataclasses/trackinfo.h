#ifndef TRACKINFO_H
#define TRACKINFO_H

#include <QHash>
#include <QMediaMetaData>
#include <QString>
#include <QDebug>

// Класс TrackInfo хранит информацию о треке.

class TrackInfo
{
public:
  enum Key { Link,         // Href трека.
             Title,        // Название трека.
             Genre,        // Жанр.
             AlbumArtist,  // Артист.
             AlbumTitle,   // Название альбома.
             CatNumber,    // Номер по каталогу.
             Publisher,    // Лэйбл выпустивший альбом.
             Date          // Дата выпуска альбома.
           };

//  TrackInfo(){}

  // Устанавливает значение value по ключу key.
  void setData(TrackInfo::Key key, const QVariant& value);
  // Возвращает значение по ключу key.
  QVariant data(TrackInfo::Key key);
  // Возвращает строковое значение информации о треке в виде списка.
  QStringList toStringList() const;

private:
  // Возвращает строковое значение ключа.
  QString keyToString(TrackInfo::Key key) const;


private:
  QHash <TrackInfo::Key, QVariant> m_attributes;

};

Q_DECLARE_METATYPE(TrackInfo)


#endif // TRACKINFO_H
