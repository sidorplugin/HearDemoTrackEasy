#include "idtagcreator.h"


// Устанавливает значение value по ключу key.
void IdTagCreator::setData(IdTagCreator::Key key, const QVariant &value)
{
  m_data.insert(key, value);
}


// Возвращает значение по ключу key.
QVariant IdTagCreator::data(IdTagCreator::Key key)
{
  return m_data.value(key);
}


// Возвращает блок тэга.
QByteArray IdTagCreator::tag() const
{
  QByteArray result;
  QString commentVersion;
  result.clear();

  int version = m_data.value(IdTagCreator::Ver).toInt();
  QString comment = m_data.value(IdTagCreator::Comment).toString();
  switch (version)
  {
    case IdTagCreator::DeejayDe :
      commentVersion = comment.leftJustified(30, ' ', true);
    break;
    case IdTagCreator::Hardwax :
      commentVersion = comment.leftJustified(29, ' ', true);
    break;
  }

  QString header = m_data.value(IdTagCreator::Header).toString();
  QString title = m_data.value(IdTagCreator::Title).toString();
  QString artist = m_data.value(IdTagCreator::Artist).toString();
  QString album = m_data.value(IdTagCreator::Album).toString();
  QString year = m_data.value(IdTagCreator::Year).toString();
  int style = m_data.value(IdTagCreator::Style).toInt();

  QString tag = header.leftJustified(3, ' ', true)  +
                title.leftJustified(30, ' ', true)  +
                artist.leftJustified(30, ' ', true) +
                album.leftJustified(30, ' ', true)  +
                year.leftJustified(4, ' ', true)    +
                commentVersion;
  result.append(tag);
  result.append(style);

  qDebug() << "tagSize = " << result.size();
  return result;
}


// Возвращает код стиля.
int IdTagCreator::codeStyle(const QString &style)
{
  int code = 12;  // Other

  if (style == "House" || style == "Chicago Oldschool" ||
      style == "Detroit" || style == "Detroit House")
    code = 35;
  if (style == "Techno" || style == "Detroit" )
    code = 18;
  if (style == "Ambient")
    code = 26;
  if (style == "Electronic" || style == "Electro" ||
      style == "Early Electronic")
    code = 52;

  return code;
}
