#ifndef FETCHMODEL_H
#define FETCHMODEL_H

#include "dataclasses/moduleparameters.h"

#include <QStandardItemModel>

class FetchModel : public QStandardItemModel
{
public:
  // Перечисление разновидностей item'ов в модели.
  enum ItemType { SourceItem,
                  StartDateItem,
                  EndDateItem,
                  StyleItem,
                  PeriodItem,
                  FilterItem
                };

  enum Roles { ListRole = Qt::UserRole + 1,
               SourceDataRole,
               CurrentIndexRole
             };

  FetchModel(QObject *parent);

private:
  // Создает item модели.
  QStandardItem* createItem(int type, const QList<ModuleParameters>& params);
};

#endif // FETCHMODEL_H
