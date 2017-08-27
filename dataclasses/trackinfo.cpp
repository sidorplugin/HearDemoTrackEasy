#include "dataclasses/trackinfo.h"


// Устанавливает значение value по ключу key.
void TrackInfo::setData(TrackInfo::Key key, const QVariant &value)
{
    m_attributes.insert(key, value);
}

// Возвращает значение по ключу key.
QVariant TrackInfo::data(TrackInfo::Key key)
{
    return m_attributes.value(key);
}

// Возвращает строковое значение информации о треке в виде списка.
QStringList TrackInfo::toStringList() const
{
   QStringList result;
   QHashIterator <TrackInfo::Key, QVariant> i(m_attributes);
   while (i.hasNext()) {
       i.next();
       QString nameKey = keyToString(i.key());
       result.append(nameKey + " : " + i.value().toString());
   }
   return result;
}

// Возвращает строковое значение ключа.
QString TrackInfo::keyToString(TrackInfo::Key key) const
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
    }
    return name;
}
