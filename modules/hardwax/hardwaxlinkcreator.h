#ifndef HARDWAXLINKCREATOR_H
#define HARDWAXLINKCREATOR_H

#include "baseclasses/linkcreator.h"

class HardwaxLinkCreator : public LinkCreator
{
public:
  QString create(Module::Mode mode, DataInput& input,
                 const ModuleParameters& params);
};

#endif // HARDWAXLINKCREATOR_H
