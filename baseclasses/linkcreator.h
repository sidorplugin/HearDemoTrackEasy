#ifndef LINKCREATOR_H
#define LINKCREATOR_H

#include "dataclasses/datainput.h"
#include "dataclasses/moduleparameters.h"

#include <QString>

class LinkCreator
{
public:
  LinkCreator() {}

  virtual QString create(const DataInput& data,
                         const ModuleParameters& params) = 0;
};

#endif // LINKCREATOR_H
