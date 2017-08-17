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
        case TrackInfo::Link :        name = "Link";         break;
        case TrackInfo::Title :       name = "Title";        break;
        case TrackInfo::Genre :       name = "Genre";        break;
        case TrackInfo::AlbumArtist : name = "Artist";       break;
        case TrackInfo::AlbumTitle :  name = "Title";        break;
        case TrackInfo::CatNumber :   name = "Cat";          break;
        case TrackInfo::Publisher :   name = "Publisher";    break;
        case TrackInfo::Date :        name = "Date";         break;
    }
    return name;
}
