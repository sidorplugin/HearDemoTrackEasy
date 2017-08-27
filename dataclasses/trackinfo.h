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
  enum Key { Artist,       // Артист.
             Title,        // Название трека.
             Album,        // Название альбома.
             Style,        // Стиль.
             Catalog,      // Номер по каталогу.
             Label,        // Лэйбл выпустивший альбом.
             Date,         // Дата выпуска альбома.
             LinkTrack,    // Ссылка на трек.
             LinkImage     // Ссылка на изображение.
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
