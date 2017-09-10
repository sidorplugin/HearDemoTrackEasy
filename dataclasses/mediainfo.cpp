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
       QString nameKey = name(i.key());
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
QString MediaInfo::name(int key)
{
    QString name;
    switch (key) {
      case MediaInfo::Id_Album :         name = "Id_Альбом";          break;
      case MediaInfo::Id_Track :         name = "Id_Трек";            break;
      case MediaInfo::Artist :           name = "Артист";             break;
      case MediaInfo::Title_Album :      name = "Альбом";             break;
      case MediaInfo::Title_Track :      name = "Название";           break;
      case MediaInfo::Style :            name = "Стиль";              break;
      case MediaInfo::Catalog :          name = "Каталог";            break;
      case MediaInfo::Label :            name = "Лэйбл";              break;
      case MediaInfo::Date :             name = "Дата";               break;
      case MediaInfo::Images :           name = "Обложка";            break;
      case MediaInfo::Link_Track :       name = "Ссылка на трек";     break;
      case MediaInfo::Link_Album :       name = "Ссылка на альбом";   break;
      case MediaInfo::Source :           name = "Источник";           break;
      case MediaInfo::Tracks :           name = "Треки";              break;
    }
    return name;
}
