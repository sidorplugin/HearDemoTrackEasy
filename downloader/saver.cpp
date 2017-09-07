#include "saver.h"

#include <QFile>
#include <QDir>

Saver::Saver(QObject *parent) : QObject(parent)
{
}


// Сохраняет данные bytes c данными data в папку root.
void Saver::save(const QByteArray &bytes, AlbumInfo &track, const QString &root)
{
  qDebug() << "Saver::save()";

  QByteArray result;
  QFile file;
  QString path = buildSavePath(track, root);
  QString fileName = getValidFileName(
                  track.data(AlbumInfo::Artist).toString() + " - " +
                  track.data(AlbumInfo::Title).toString());
  qDebug() << "fileName = " << fileName;

  file.setFileName(path + "/" + fileName + ".mp3");
  if (!file.open(QIODevice::WriteOnly)) {
    qDebug() << "error, not open";
    return;
  }

  // Добавляет тег.
  QByteArray tag = createTag(track);
  result.append(bytes);
  result.append(tag);

  file.write(result);
  file.close();

  emit saved(track);

}


// Строит путь сохранения для файла.
QString Saver::buildSavePath(AlbumInfo &track, const QString& root)
{
  QString nameResource;
  QString link = track.data(AlbumInfo::Tracks).toHash().values().at(0).toString();
  QString style = track.data(AlbumInfo::Style).toString();
  QString date = track.data(AlbumInfo::Date).toString();
  QString year = QDate::fromString(date, "dd.MM.yyyy").toString("yyyy");
  QString month = QDate::fromString(date, "dd.MM.yyyy").toString("MMMM");

  if (link.contains("deejay.de"))
    nameResource = "Deejay.de";
  if (link.contains("media.hardwax.com"))
    nameResource = "Hardwax.com";
  if (link.contains("juno.co.uk"))
    nameResource = "Juno.co.uk";

  QString path = root + "/" + nameResource + "/" + style + "/"+ year + "/" + month;
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


// Создает тэг.
QByteArray Saver::createTag(AlbumInfo &track)
{
  QByteArray result;
  QString link = track.data(AlbumInfo::Tracks).toHash().values().at(0).toString();

  if (!link.contains("www.juno.co.uk")) {
    // Установка Tag.
    if (link.contains("media.hardwax.com")) {
      m_tagCreator.setData(IdTagCreator::Ver, IdTagCreator::Hardwax);
    }
    if (link.contains("deejay.de")) {
      m_tagCreator.setData(IdTagCreator::Ver, IdTagCreator::DeejayDe);
    }

    m_tagCreator.setData(IdTagCreator::Header, "TAG");
    m_tagCreator.setData(IdTagCreator::Title,
                         track.data(AlbumInfo::Tracks).toHash().keys().at(0));
    m_tagCreator.setData(IdTagCreator::Artist,
                         track.data(AlbumInfo::Artist).toString());
    m_tagCreator.setData(IdTagCreator::Album,
                         track.data(AlbumInfo::Title).toString());
    m_tagCreator.setData(IdTagCreator::Year,
                         track.data(AlbumInfo::Date).toDate().toString("yyyy"));
    m_tagCreator.setData(IdTagCreator::Comment,
                         track.data(AlbumInfo::Catalog).toString() + "," +
                         track.data(AlbumInfo::Label).toString() + "," +
                         track.data(AlbumInfo::Date).
                         toDate().toString("dd.MM.yyyy"));
    int style = m_tagCreator.codeStyle(track.data(AlbumInfo::Style).toString());
    m_tagCreator.setData(IdTagCreator::Style, style);

    result = m_tagCreator.tag();
  }

  return result;
}


// Возвращает валидное имя файла.
QString Saver::getValidFileName(const QString &name)
{
  QString result;

  result = name;
  return result.remove("/").remove("\"").remove("*").remove("'").remove("|").
                remove("?").remove("+").remove("\t");
}
