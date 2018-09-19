#ifndef MODULEFACTORY
#define MODULEFACTORY

#include "dataclasses/moduleparameters.h"
#include "baseclasses/fetcher.h"
#include "baseclasses/linkcreator.h"
#include "baseclasses/pagesearcher.h"

#include <QXmlStreamReader>

// Абстрактная фабрика для производства модулей.

class ModuleFactory
{
public:
  virtual Fetcher* createFetcher() = 0;
  virtual PageSearcher* createPageSearcher() = 0;
  virtual LinkCreator* createLinkCreator() = 0;
  virtual ModuleParameters createParameters() = 0;

  ModuleParameters readFromXmlFile(const QString& fileName) {
      qDebug() << "ModuleFactory::readFromXmlFile";

      ModuleParameters result;
      QStringList searchGroups;
      QMap<QString, QVariant> styles;
      QMap<QString, QVariant> periods;
      QMap<QString, QVariant> filters;

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
            result.setData(ModuleParameters::Id, attributes.value("id").toInt());
            xmlReader.readNext();
            result.setData(ModuleParameters::Name, xmlReader.text().toString());
            continue;
          }

          if (xmlReader.name() == "address") {
            result.setData(ModuleParameters::Address, attributes.value("href").toString());
            continue;
          }

          if (xmlReader.name() == "icon") {
            result.setData(ModuleParameters::Icon, attributes.value("path").toString());
            continue;
          }

          if (xmlReader.name() == "group") {
            xmlReader.readNext();
            QString value = xmlReader.text().toString();
            searchGroups.append(value);
            continue;
          }


          if (xmlReader.name() == "style") {
            QString title = attributes.value("title").toString();
            QString link = attributes.value("link").toString();
            xmlReader.readNext();
            QString value = xmlReader.text().toString();
            QStringList styleInfo;
            styleInfo << value << link;
            styles.insert(title, styleInfo);
            continue;
          }

          if (xmlReader.name() == "period") {
            QString title = attributes.value("title").toString();
            QString link = attributes.value("link").toString();
            xmlReader.readNext();
            QString value = xmlReader.text().toString();
            QStringList periodInfo;
            periodInfo << value << link;
            periods.insert(title, periodInfo);
            continue;
          }

          if (xmlReader.name() == "filter") {
            QString title = attributes.value("title").toString();
            QString link = attributes.value("link").toString();
            xmlReader.readNext();
            QString value = xmlReader.text().toString();
            QStringList filterInfo;
            filterInfo << value << link;
            filters.insert(title, filterInfo);
            continue;
          }
      }
      result.setData(ModuleParameters::SearchGroups, searchGroups);
      result.setData(ModuleParameters::Styles, styles);
      result.setData(ModuleParameters::Periods, periods);
      result.setData(ModuleParameters::Filters, filters);

      return result;
  }

  virtual ~ModuleFactory() {}
};



#endif // MODULEFACTORY
