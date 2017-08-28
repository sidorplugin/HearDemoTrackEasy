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
  QString path = buildSavePath(track, root);
  QString fileName = getValidFileName(
                  track.data(TrackInfo::Artist).toString() + " - " +
                  track.data(TrackInfo::Title).toString());
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
QString Saver::buildSavePath(TrackInfo &track, const QString& root)
{
  QString nameResource;
  QString href = track.data(TrackInfo::LinkTrack).toString();
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


// Создает тэг.
QByteArray Saver::createTag(TrackInfo &track)
{
  QByteArray result;
  QString href = track.data(TrackInfo::LinkTrack).toString();

  if (!href.contains("www.juno.co.uk")) {
    // Установка Tag.
    if (href.contains("media.hardwax.com")) {
      m_tagCreator.setData(IdTagCreator::Ver, IdTagCreator::Hardwax);
    }
    if (href.contains("deejay.de")) {
      m_tagCreator.setData(IdTagCreator::Ver, IdTagCreator::DeejayDe);
    }

    m_tagCreator.setData(IdTagCreator::Header, "TAG");
    m_tagCreator.setData(IdTagCreator::Title,
                         track.data(TrackInfo::Title).toString());
    m_tagCreator.setData(IdTagCreator::Artist,
                         track.data(TrackInfo::Artist).toString());
    m_tagCreator.setData(IdTagCreator::Album,
                         track.data(TrackInfo::Album).toString());
    m_tagCreator.setData(IdTagCreator::Year,
                         track.data(TrackInfo::Date).toDate().toString("yyyy"));
    m_tagCreator.setData(IdTagCreator::Comment,
                         track.data(TrackInfo::Catalog).toString() + "," +
                         track.data(TrackInfo::Label).toString() + "," +
                         track.data(TrackInfo::Date).
                         toDate().toString("dd.MM.yyyy"));
    int style = m_tagCreator.codeStyle(track.data(TrackInfo::Style).toString());
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
