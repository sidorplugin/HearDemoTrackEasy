#include "globaldata.h"

#include <QSettings>
#include <QFile>
#include <QXmlStreamReader>
#include <QDebug>

GlobalData* GlobalData::m_self = NULL;

// Возвращает единственный экземпляр объекта.
GlobalData* GlobalData::getInstance()
{
  if (!m_self)
    m_self = new GlobalData;
  return m_self;
}


// Устанавливает глобальные настройки программы.
void GlobalData::setGlobalSettings(const QString &root_string,
                                   int delay_value,
                                   int waiting_value,
                                   int loads_value)
{
  QSettings settings("settings.ini", QSettings::IniFormat);
  settings.setValue("Delay", delay_value);
  settings.setValue("Root", root_string);
  settings.setValue("Waiting", waiting_value);
  settings.setValue("Loads", loads_value);
}


// Считывает глобальные настройки программы.
void GlobalData::readGlobalSettings()
{
  qDebug() << "GlobalData::readGlobalSettings";
  QSettings settings("settings.ini", QSettings::IniFormat);
  delay = settings.value("Delay").toInt();
  root = settings.value("Root").toString();
  waiting = settings.value("Waiting").toInt();
  loads = settings.value("Loads").toInt();
}


// Возвращает хэш таблицу параметров модуля из XML файла.
ModuleParameters GlobalData::readFromXmlFile(const QString &fileName)
{
  qDebug() << "GlobalData::readFromXmlFile";

  ModuleParameters result;

  QFile file(fileName);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    return result;

  QXmlStreamReader xmlReader;
  xmlReader.setDevice(&file);
  xmlReader.readNext();   // Переходит к первому элементу в файле.
  // Крутимся в цикле до тех пор, пока не достигнем конца документа.
  while (!xmlReader.atEnd() && !xmlReader.hasError()) {
      xmlReader.readNext();
      // Пропускает все элементы пока не найдет начало тега.
      while (!xmlReader.isStartElement()) {
          xmlReader.readNext();
          if (xmlReader.atEnd())
            break;
      }

      if (xmlReader.name() == "module")
        continue;

      QXmlStreamAttributes attributes = xmlReader.attributes();
      if (xmlReader.name() == "name") {
        result.setId(attributes.value("id").toInt());
        xmlReader.readNext();
        result.setName(xmlReader.text().toString());
        continue;
      }

      if (xmlReader.name() == "address") {
        result.setAddress(attributes.value("href").toString());
        continue;
      }

      if (xmlReader.name() == "icon") {
        result.setIcon(attributes.value("path").toString());
        continue;
      }

      if (xmlReader.name() == "genre") {
        QString title = attributes.value("title").toString();
        QString link = attributes.value("link").toString();
        xmlReader.readNext();
        QString value = xmlReader.text().toString();
        result.setGenre(title, value, link);
        continue;
      }

      if (xmlReader.name() == "period") {
        QString title = attributes.value("title").toString();
        QString link = attributes.value("link").toString();
        xmlReader.readNext();
        QString value = xmlReader.text().toString();
        result.setPeriod(title, value, link);
        continue;
      }

      if (xmlReader.name() == "filter") {
        QString title = attributes.value("title").toString();
        QString link = attributes.value("link").toString();
        xmlReader.readNext();
        QString value = xmlReader.text().toString();
        result.setFilter(title, value, link);
        continue;
      }
  }
  parameters.push_back(result);
  return result;
}
