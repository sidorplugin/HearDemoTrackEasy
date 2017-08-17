#include "globaldata.h"
#include "fetchparametersmodel.h"

#include <QDate>

FetchParametersModel::FetchParametersModel(QObject *parent)
                     : QStandardItemModel(parent)
{
  // Задает параметры модели.
  setRowCount(6);
  setColumnCount(1);

  // Создает item'ы модели.
  for (int row = 0; row < 6; ++row) {
    for (int column = 0; column < 1; ++column) {
      QStandardItem *item = new QStandardItem();
      setItem(row, column, item);
    }
  }

  QStringList labels;
  labels << "Источник" << "Начало" << "Конец" << "Жанр" << "Период" << "Фильтр";
  setVerticalHeaderLabels(labels);
  setHorizontalHeaderLabels(QStringList(""));

  // Берет информацию о модулях из глобальных данных.
  QList<ModuleParameters> parameters = GlobalData::getInstance()->parameters;
  // Проходит по всем item'ам размещая в них данные.
  for (int i = 0; i <= FetchParametersModel::FilterItem; i++)
    setDataItem(i, parameters);

}


// Устанавливает данные для item'а модели.
void FetchParametersModel::setDataItem(int type,
                                       const QList<ModuleParameters>& params)
{
  // Получает item модели по индексу.
  QStandardItem* item = this->item(type);

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
      QHash <QString, QVariant> data;
      foreach (ModuleParameters p, params) {
        data.insert(p.name(), p.periods());
      }
      item->setData(data, ROLE_LIST);
    }
    break;

    case FetchParametersModel::FilterItem:
    {
      QHash <QString, QVariant> data;
      foreach (ModuleParameters p, params) {
        data.insert(p.name(), p.filters());
      }
      item->setData(data, ROLE_LIST);
    }
    break;
  }
}

