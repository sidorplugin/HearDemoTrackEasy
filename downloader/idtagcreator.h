#ifndef IDTAGCREATOR_H
#define IDTAGCREATOR_H

#include <QObject>
#include <QDebug>

// TODO Hash хранение.

class IdTagCreator
{
public:
  enum Version { DeejayDe, Hardwax };
  IdTagCreator();

  // Устанавливает заголовок.
  void setHeader(const QString& header) { m_header = header; }
  // Устанавливает название трека.
  void setTitle(const QString& title) { m_title = title; }
  // Устанавливает исполнителя.
  void setArtist(const QString& artist) { m_artist = artist; }
  // Устанавливает название альбома.
  void setAlbum(const QString& album) { m_album = album; }
  // Устанавливает год.
  void setYear(const QString& year) { m_year = year; }
  // Устанавливает комментарий.
  void setComment(const QString& comment) { m_comment = comment; }
  // Устанавливает номер трека.
  void setNumberTrack(const QString& number) { m_number = number; }
  // Устанавливает жанр.
  void setGenre(int genre) { m_genre = genre; }
  // Устанавливает версию.
  void setVersion(IdTagCreator::Version version) { m_version = version; }

public:
  // Возвращает блок тэга.
  QByteArray tag() const;

private:
  QString m_header;
  QString m_title;
  QString m_artist;
  QString m_album;
  QString m_year;
  QString m_comment;
  QString m_number;
  int m_genre;
  IdTagCreator::Version m_version;

};

#endif // IDTAGCREATOR_H
