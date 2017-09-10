#include "saver.h"

#include <QFile>
#include <QDir>

Saver::Saver(QObject *parent) : QObject(parent)
{
}


// Сохраняет данные bytes c данными data в папку root.
void Saver::save(const QByteArray &bytes, MediaInfo &media, const QString &root)
{
  qDebug() << "Saver::save()";

  QByteArray result;
  QFile file;
  QString path = buildSavePath(media, root);
  QString fileName = getValidFileName(
                  media.data(MediaInfo::Artist).toString() + " - " +
                  media.data(MediaInfo::Title_Track).toString());
  qDebug() << "fileName = " << fileName;

  file.setFileName(path + "/" + fileName + ".mp3");
  if (!file.open(QIODevice::WriteOnly)) {
    qDebug() << "error, not open";
    return;
  }

  // Добавляет тег.
  QByteArray tag = createTag(media);
  result.append(bytes);
  result.append(tag);

  file.write(result);
  file.close();

  emit saved(media);

}


// Строит путь сохранения для файла.
QString Saver::buildSavePath(MediaInfo &media, const QString& root)
{
  QString nameResource;
  QString link = media.data(MediaInfo::Link_Track).toString();
  QString style = media.data(MediaInfo::Style).toString();
  QDate date = media.data(MediaInfo::Date).toDate();
  QString year = date.toString("yyyy");
  QString month = date.toString("MMMM");

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
QByteArray Saver::createTag(MediaInfo &media)
{
  QByteArray result;
  QString link = media.data(MediaInfo::Link_Track).toString();

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
                         media.data(MediaInfo::Title_Track).toString());
    m_tagCreator.setData(IdTagCreator::Artist,
                         media.data(MediaInfo::Artist).toString());
    m_tagCreator.setData(IdTagCreator::Album,
                         media.data(MediaInfo::Title_Album).toString());
    m_tagCreator.setData(IdTagCreator::Year,
                         media.data(MediaInfo::Date).toDate().toString("yyyy"));
    m_tagCreator.setData(IdTagCreator::Comment,
                         media.data(MediaInfo::Catalog).toString() + "," +
                         media.data(MediaInfo::Label).toString() + "," +
                         media.data(MediaInfo::Date).
                         toDate().toString("dd.MM.yyyy"));
    int style = m_tagCreator.codeStyle(media.data(MediaInfo::Style).toString());
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
