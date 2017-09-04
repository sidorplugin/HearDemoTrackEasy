#include "dataclasses/albuminfo.h"


// Устанавливает значение value по ключу key.
void AlbumInfo::setData(int key, const QVariant &value)
{
    m_data.insert(key, value);
}

// Возвращает значение по ключу key.
QVariant AlbumInfo::data(int key)
{
    return m_data.value(key);
}

// Возвращает строковое значение информации о треке в виде списка.
QStringList AlbumInfo::toStringList() const
{
   QStringList result;
   QHashIterator <int, QVariant> i(m_data);
   while (i.hasNext()) {
       i.next();
       QString nameKey = keyToString(i.key());
       result.append(nameKey + " : " + i.value().toString());
   }
   return result;
}


// Очищает все поля в альбоме.
void AlbumInfo::clear()
{
  m_data.clear();
}


// Проверяет на наличие информации в альбоме.
bool AlbumInfo::isEmpty()
{
  return m_data.isEmpty();
}


// Возвращает строковое значение ключа.
QString AlbumInfo::keyToString(int key) const
{
    QString name;
    switch (key) {
      case AlbumInfo::Id :               name = "Id";           break;
      case AlbumInfo::Artist :           name = "Artist";       break;
      case AlbumInfo::Title :            name = "Title";        break;
      case AlbumInfo::Style :            name = "Style";        break;
      case AlbumInfo::Catalog :          name = "Catalog";      break;
      case AlbumInfo::Label :            name = "Label";        break;
      case AlbumInfo::Date :             name = "Date";         break;
      case AlbumInfo::Images :           name = "Images";       break;
      case AlbumInfo::Tracks :           name = "Tracks";       break;
      case AlbumInfo::Source :           name = "Source";       break;
    }
    return name;
}
