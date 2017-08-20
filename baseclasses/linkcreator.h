#ifndef LINKCREATOR_H
#define LINKCREATOR_H

#include "dataclasses/datainput.h"
#include "dataclasses/moduleparameters.h"
#include "baseclasses/module.h"

#include <QString>

class LinkCreator
{
public:
  LinkCreator() {}

  virtual QString create(Module::Mode mode, const DataInput& data,
                         const ModuleParameters& params) = 0;
};

#endif // LINKCREATOR_H
