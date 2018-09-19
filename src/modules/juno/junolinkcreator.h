#ifndef JUNOLINKCREATOR_H
#define JUNOLINKCREATOR_H

#include "baseclasses/linkcreator.h"

class JunoLinkCreator : public LinkCreator
{
public:
  QString create(int mode, const InputPack& input, ModuleParameters& params);
};

#endif // JUNOLINKCREATOR_H
