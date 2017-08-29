#include "dataclasses/trackinfo.h"


// Устанавливает значение value по ключу key.
void TrackInfo::setData(int key, const QVariant &value)
{
    m_data.insert(key, value);
}

// Возвращает значение по ключу key.
QVariant TrackInfo::data(int key)
{
    return m_data.value(key);
}

// Возвращает строковое значение информации о треке в виде списка.
QStringList TrackInfo::toStringList() const
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

// Возвращает строковое значение ключа.
QString TrackInfo::keyToString(int key) const
{
    QString name;
    switch (key) {
        case TrackInfo::Artist :           name = "Artist";       break;
        case TrackInfo::Title :            name = "Title";        break;
        case TrackInfo::Album :            name = "Album";        break;
        case TrackInfo::Style :            name = "Style";        break;
        case TrackInfo::Catalog :          name = "Catalog";      break;
        case TrackInfo::Label :            name = "Label";        break;
        case TrackInfo::Date :             name = "Date";         break;
        case TrackInfo::LinkTrack :        name = "LinkTrack";    break;
        case TrackInfo::LinkImage :        name = "LinkImage";    break;
        case TrackInfo::Source :           name = "Source";       break;
    }
    return name;
}
