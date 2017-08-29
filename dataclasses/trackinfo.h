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
             LinkImage,    // Ссылка на изображение.
             Source
           };

//  TrackInfo(){}

  // Устанавливает значение value по ключу key.
  void setData(int key, const QVariant& value);
  // Возвращает значение по ключу key.
  QVariant data(int key);
  // Возвращает строковое значение информации о треке в виде списка.
  QStringList toStringList() const;

private:
  // Возвращает строковое значение ключа.
  QString keyToString(int key) const;


private:
  QHash <int, QVariant> m_data;

};

Q_DECLARE_METATYPE(TrackInfo)


#endif // TRACKINFO_H
