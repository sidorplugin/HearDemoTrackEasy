#include "saver.h"

#include <QFile>
#include <QDir>

Saver::Saver(QObject *parent) : QObject(parent)
{
}


// Сохраняет данные bytes c данными data в папку root.
void Saver::save(const QByteArray &bytes, TrackInfo &track, const QString &root)
{
  qDebug() << "Saver::save()";

  QByteArray result;
  QFile file;
  QString path = getPath(track, root);
  QString fileName = getValidFileName(
                  track.data(TrackInfo::AlbumArtist).toString() + " - " +
                  track.data(TrackInfo::Title).toString());
  qDebug() << "fileName = " << fileName;

  file.setFileName(path + "/" + fileName + ".mp3");
  if (!file.open(QIODevice::WriteOnly)) {
    qDebug() << "error, not open";
    return;
  }

  // Добавляет тег.
  QByteArray tag = getTag(track);
  result.append(bytes);
  result.append(tag);

  file.write(result);
  file.close();

  emit saved(track);

}


// Возвращает путь к файлу.
QString Saver::getPath(TrackInfo &track, const QString& root)
{
  QString nameResource;
  QString href = track.data(TrackInfo::Link).toString();
  QString genre = track.data(TrackInfo::Style).toString();
  QString date = track.data(TrackInfo::Date).toString();
  QString year = QDate::fromString(date, "dd.MM.yyyy").toString("yyyy");
  QString month = QDate::fromString(date, "dd.MM.yyyy").toString("MMMM");

  if (href.contains("deejay.de"))
    nameResource = "Deejay.de";
  if (href.contains("media.hardwax.com"))
    nameResource = "Hardwax.com";
  if (href.contains("juno.co.uk"))
    nameResource = "Juno.co.uk";

  QString path = root + "/" + nameResource + "/" + genre + "/"+ year + "/" + month;
  QDir dir(path);

  if (dir.mkpath(path)) {
    qDebug() << "m_path = " << path;
    return dir.canonicalPath();
  }
  else {
    qDebug() << "error create path" << path;
    return QString();
    }
}


// Возвращает тэг.
QByteArray Saver::getTag(TrackInfo &track)
{
  QByteArray result;
  QString href = track.data(TrackInfo::Link).toString();

  if (!href.contains("www.juno.co.uk")) {
    // Установка Tag.
    if (href.contains("media.hardwax.com")) {
      m_tagCreator.setVersion(IdTagCreator::Hardwax);
    }
    if (href.contains("deejay.de")) {
      m_tagCreator.setVersion(IdTagCreator::DeejayDe);
    }

    m_tagCreator.setHeader("TAG");
    m_tagCreator.setTitle(track.data(TrackInfo::Title).toString());
    m_tagCreator.setArtist(track.data(TrackInfo::AlbumArtist).toString());
    m_tagCreator.setAlbum(track.data(TrackInfo::AlbumTitle).toString());
    m_tagCreator.setYear(track.data(TrackInfo::Date).toDate().toString("yyyy"));
    m_tagCreator.setComment(track.data(TrackInfo::CatNumber).toString() + "," +
                   track.data(TrackInfo::Publisher).toString() + "," +
                   track.data(TrackInfo::Date).toDate().toString("dd.MM.yyyy"));

    int genre = codeGenre(track.data(TrackInfo::Style).toString());

    m_tagCreator.setGenre(genre);

    result = m_tagCreator.tag();
  }

  return result;
}


// Возвращает код жанра.
int Saver::codeGenre(const QString &genre)
{
  int codeGenre;

  if (genre == "House" || genre == "Chicago Oldschool" || genre == "Detroit" ||
      genre == "Detroit House")
    codeGenre = 35;
  if (genre == "Techno" || genre == "Detroit" )
    codeGenre = 18;
  if (genre == "Exclusive" || genre == "D Labels" || genre == "Euro Labels" ||
      genre == "Uk Labels" || genre == "Us Labels" || genre == "Reggae - Dub" ||
      genre == "Merchandise" || genre == "Exclusives" || genre == "Digital")
    codeGenre = 12;  // Other
  if (genre == "Ambient")
    codeGenre = 26;
  if (genre == "Electronic" || genre == "Electro" || genre == "Early Electronic")
    codeGenre = 52;

  return codeGenre;
}


// Возвращает валидное имя файла.
QString Saver::getValidFileName(const QString &name)
{
  QString result;

  result = name;
  return result.remove("/").remove("\"").remove("*").remove("'").remove("|").
                remove("?").remove("+").remove("\t");
}

