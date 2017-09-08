#include "dataclasses/mediainfo.h"


// Устанавливает значение value по ключу key.
void MediaInfo::setData(int key, const QVariant &value)
{
    m_data.insert(key, value);
}

// Возвращает значение по ключу key.
QVariant MediaInfo::data(int key)
{
    return m_data.value(key);
}

// Возвращает строковое значение информации о треке в виде списка.
QStringList MediaInfo::toStringList() const
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
void MediaInfo::clear()
{
  m_data.clear();
}


// Проверяет на наличие информации в альбоме.
bool MediaInfo::isEmpty()
{
  return m_data.isEmpty();
}


// Возвращает строковое значение ключа.
QString MediaInfo::keyToString(int key) const
{
    QString name;
    switch (key) {
      case MediaInfo::Id_Album :         name = "Id_Album";     break;
      case MediaInfo::Id_Track :         name = "Id_Track";     break;
      case MediaInfo::Artist :           name = "Artist";       break;
      case MediaInfo::Title_Album :      name = "Title_Album";  break;
      case MediaInfo::Title_Track :      name = "Title_Track";  break;
      case MediaInfo::Style :            name = "Style";        break;
      case MediaInfo::Catalog :          name = "Catalog";      break;
      case MediaInfo::Label :            name = "Label";        break;
      case MediaInfo::Date :             name = "Date";         break;
      case MediaInfo::Images :           name = "Images";       break;
      case MediaInfo::Tracks :           name = "Tracks";       break;
      case MediaInfo::Link_Album :       name = "Link_Album";   break;
      case MediaInfo::Link_Track :       name = "Link_Track";   break;
      case MediaInfo::Source :           name = "Source";       break;
    }
    return name;
}
