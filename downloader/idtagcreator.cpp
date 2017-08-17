#include "idtagcreator.h"

IdTagCreator::IdTagCreator()
{

}

// Возвращает блок тэга.
QByteArray IdTagCreator::tag() const
{
  QByteArray tag;
  QString commentVersion;
  tag.clear();

  switch (m_version)
  {
    case IdTagCreator::DeejayDe :
      commentVersion = m_comment.leftJustified(30, ' ', true);
      break;
    case IdTagCreator::Hardwax :
      commentVersion = m_comment.leftJustified(29, ' ', true);
      break;
  }

  QString strTag = m_header.leftJustified(3, ' ', true)   +
                   m_title.leftJustified(30, ' ', true)   +
                   m_artist.leftJustified(30, ' ', true)  +
                   m_album.leftJustified(30, ' ', true)   +
                   m_year.leftJustified(4, ' ', true)     +
                   commentVersion;
  tag.append(strTag);
  tag.append(m_genre);

  qDebug() << "tagSize = " << tag.size();
  return tag;
}

