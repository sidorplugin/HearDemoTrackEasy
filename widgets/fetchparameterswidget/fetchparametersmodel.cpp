#include "globaldata.h"
#include "fetchparametersmodel.h"

#include <QDate>
#include <QDebug>

FetchParametersModel::FetchParametersModel(QObject *parent)
                     : QStandardItemModel(parent)
{
  // Берет информацию о модулях из глобальных данных.
  QList<ModuleParameters> parameters = GlobalData::getInstance()->parameters;

  for (int i = 0; i <= FetchParametersModel::FilterItem; i++) {
    QStandardItem *item = createItem(i, parameters);
    setItem(i, 0, item);
  }

  QStringList labels;
  labels << "Источник" << "Начало" << "Конец" << "Жанр" << "Период" << "Фильтр";
  setVerticalHeaderLabels(labels);
  setHorizontalHeaderLabels(QStringList(""));
}


// Создает item модели.
QStandardItem* FetchParametersModel::createItem(int type,
                                      const QList<ModuleParameters>& params)
{
  QStandardItem *item = new QStandardItem();

  // В зависимости от типа item устанавливает соответствующие данные.
  switch (type) {
    case FetchParametersModel::SourceItem:
    {
      QMap <QString, QVariant> data;
      // Проходит по всем модулям, собирает данные, устанавливает в item.
      foreach (ModuleParameters p, params) {
        int id = p.id();
        QString name = p.name();
        QString icon = p.icon();
        QStringList info;
        info << name << icon;
        data.insert(QString::number(id), info);
      }
      item->setData(data.value(QString::number(0)).toStringList().at(0),
                    Qt::DisplayRole);
      item->setData(QIcon(data.value(QString::number(0)).toStringList().at(1)),
                    Qt::DecorationRole);
      item->setData(0, ROLE_CURRENT_INDEX);
      item->setData(data, ROLE_SOURCE_DATA);

    }
    break;

    case FetchParametersModel::StartDateItem:
    {
      QDate date(2017, 01, 01);
      item->setData(date.toString("dd.MM.yyyy"), Qt::DisplayRole);
    }
    break;

    case FetchParametersModel::EndDateItem:
    {
      item->setData(QDate::currentDate().toString("dd.MM.yyyy"), Qt::DisplayRole);
    }
    break;

    case FetchParametersModel::GenreItem:
    {
      QMap <QString, QVariant> data;
      foreach (ModuleParameters p, params) {
        data.insert(p.name(), p.genres());
      }
      item->setData(data, ROLE_LIST);
    }
    break;

    case FetchParametersModel::PeriodItem:
    {
      QMap <QString, QVariant> data;
      foreach (ModuleParameters p, params) {
        data.insert(p.name(), p.periods());
      }
      item->setData(data, ROLE_LIST);
    }
    break;

    case FetchParametersModel::FilterItem:
    {
      QMap <QString, QVariant> data;
      foreach (ModuleParameters p, params) {
        data.insert(p.name(), p.filters());
      }
      item->setData(data, ROLE_LIST);
    }
    break;
  }

  return item;
}

