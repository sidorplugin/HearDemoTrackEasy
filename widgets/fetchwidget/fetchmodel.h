#ifndef FETCHMODEL_H
#define FETCHMODEL_H

#include "dataclasses/moduleparameters.h"

#include <QStandardItemModel>

// Константы ролей.
const int ROLE_LIST = Qt::UserRole;
const int ROLE_SOURCE_DATA = Qt::UserRole + 1;
const int ROLE_CURRENT_INDEX = Qt::UserRole + 2;


class FetchModel : public QStandardItemModel
{
public:
  // Перечисление разновидностей item'ов в модели.
  enum ItemType { SourceItem,
                  StartDateItem,
                  EndDateItem,
                  GenreItem,
                  PeriodItem,
                  FilterItem
                };

  FetchModel(QObject *parent);

private:
  // Создает item модели.
  QStandardItem* createItem(int type, const QList<ModuleParameters>& params);
};

#endif // FETCHMODEL_H