#ifndef MEDIAINFO_H
#define MEDIAINFO_H

#include <QHash>
#include <QMediaMetaData>
#include <QString>
#include <QDebug>

// Класс MediaInfo хранит информацию об альбоме.

class MediaInfo
{
public:
  enum Key {
    Id_Track,     // Уникальный id трека (qHash(Artist + Title)++).
    Id_Album,     // Уникальный id альбома (qHash(Artist + Title)).
    Artist,       // Артист.
    Title_Track,  // Название трека.
    Title_Album,  // Название aльбома.
    Style,        // Стиль.
    Catalog,      // Номер по каталогу.
    Label,        // Лэйбл выпустивший альбом.
    Date,         // Дата выпуска альбома.
    Images,       // Ссылки на изображения.
    Link_Track,   // Ссылка на трек.
    Link_Album,   // Ссылка на альбом.
    Source,       // Ресурс.
    Tracks        // Треки альбома.
  };

  // Устанавливает значение value по ключу key.
  void setData(int key, const QVariant& value);
  // Возвращает значение по ключу key.
  QVariant data(int key) const;
  // Возвращает строковое значение информации о треке в виде списка.
  QStringList toStringList() const;
  // Возвращает строковое значение ключа.
  static QString name(int key);
  // Очищает все поля в альбоме.
  void clear();
  // Проверяет на наличие информации в альбоме.
  bool isEmpty();

private:
  QHash <int, QVariant> m_data;

};

Q_DECLARE_METATYPE(MediaInfo)


#endif // MEDIAINFO_H
