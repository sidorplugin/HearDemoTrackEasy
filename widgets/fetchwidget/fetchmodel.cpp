#include "globaldata.h"
#include "fetchmodel.h"

#include <QDate>
#include <QDebug>

FetchModel::FetchModel(QObject *parent)
                     : QStandardItemModel(parent)
{
  // Берет информацию о модулях из глобальных данных.
  QList<ModuleParameters> parameters = GlobalData::getInstance()->parameters;

  for (int i = 0; i <= FetchModel::FilterItem; i++) {
    QStandardItem *item = createItem(i, parameters);
    setItem(i, 0, item);
  }

  QStringList labels;
  labels << "Источник" << "Начало" << "Конец" << "Жанр" << "Период" << "Фильтр";
  setVerticalHeaderLabels(labels);
  setHorizontalHeaderLabels(QStringList(""));
}


// Создает item модели.
QStandardItem* FetchModel::createItem(int type,
                                      const QList<ModuleParameters>& params)
{
  QStandardItem *item = new QStandardItem();

  // В зависимости от типа item устанавливает соответствующие данные.
  switch (type) {
    case FetchModel::SourceItem:
    {
      QMap <QString, QVariant> data;
      // Проходит по всем модулям, собирает данные, устанавливает в item.
      foreach (ModuleParameters p, params) {
        int id = p.data(ModuleParameters::Id).toInt();
        QString name = p.data(ModuleParameters::Name).toString();
        QString icon = p.data(ModuleParameters::Icon).toString();
        QStringList info;
        info << name << icon;
        data.insert(QString::number(id), info);
      }
      item->setData(data.value(QString::number(0)).toStringList().at(0),
                    Qt::DisplayRole);
      item->setData(QIcon(data.value(QString::number(0)).toStringList().at(1)),
                    Qt::DecorationRole);
      item->setData(0, FetchModel::CurrentIndexRole);
      item->setData(data, FetchModel::SourceDataRole);

    }
    break;

    case FetchModel::StartDateItem:
    {
      QDate date(2017, 01, 01);
      item->setData(date.toString("dd.MM.yyyy"), Qt::DisplayRole);
    }
    break;

    case FetchModel::EndDateItem:
    {
      item->setData(QDate::currentDate().toString("dd.MM.yyyy"), Qt::DisplayRole);
    }
    break;

    case FetchModel::StyleItem:
    {
      QMap <QString, QVariant> data;
      foreach (ModuleParameters p, params) {
        QStringList styles =  p.data(ModuleParameters::Styles).toMap().keys();
        data.insert(p.data(ModuleParameters::Name).toString(), styles);
      }
      item->setData(data, FetchModel::ListRole);
    }
    break;

    case FetchModel::PeriodItem:
    {
      QMap <QString, QVariant> data;
      foreach (ModuleParameters p, params) {
        QStringList periods =  p.data(ModuleParameters::Periods).toMap().keys();
        data.insert(p.data(ModuleParameters::Name).toString(), periods);
      }
      item->setData(data, FetchModel::ListRole);
    }
    break;

    case FetchModel::FilterItem:
    {
      QMap <QString, QVariant> data;
      foreach (ModuleParameters p, params) {
        QStringList filters =  p.data(ModuleParameters::Filters).toMap().keys();
        data.insert(p.data(ModuleParameters::Name).toString(), filters);
      }
      item->setData(data, FetchModel::ListRole);
    }
    break;
  }

  return item;
}

