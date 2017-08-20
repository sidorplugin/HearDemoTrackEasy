#ifndef JUNOLINKCREATOR_H
#define JUNOLINKCREATOR_H

#include "baseclasses/linkcreator.h"

class JunoLinkCreator : public LinkCreator
{
public:
  QString create(Module::Mode mode, const DataInput& data,
                 const ModuleParameters& params);
};

#endif // JUNOLINKCREATOR_H
