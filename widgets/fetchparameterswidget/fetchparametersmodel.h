#ifndef FETCHPARAMETERSMODEL_H
#define FETCHPARAMETERSMODEL_H

#include "dataclasses/moduleparameters.h"

#include <QStandardItemModel>

// Константы ролей.
const int ROLE_LIST = Qt::UserRole;
const int ROLE_SOURCE_DATA = Qt::UserRole + 1;
const int ROLE_CURRENT_INDEX = Qt::UserRole + 2;


class FetchParametersModel : public QStandardItemModel
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

  FetchParametersModel(QObject *parent);

private:
  // Устанавливает данные для item'а модели.
  void setDataItem(int type, const QList<ModuleParameters>& params);
};

#endif // FETCHPARAMETERSMODEL_H
