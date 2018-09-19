#ifndef HARDWAXLINKCREATOR_H
#define HARDWAXLINKCREATOR_H

#include "baseclasses/linkcreator.h"

class HardwaxLinkCreator : public LinkCreator
{
public:
  QString create(int mode, const InputPack& input, ModuleParameters& params);
};

#endif // HARDWAXLINKCREATOR_H
