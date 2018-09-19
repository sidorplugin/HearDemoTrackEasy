#ifndef DEEJAYDELINKCREATOR_H
#define DEEJAYDELINKCREATOR_H

#include "baseclasses/linkcreator.h"

class DeejayDeLinkCreator : public LinkCreator
{
public:
  QString create(int mode, const InputPack& input, ModuleParameters& params);
};

#endif // DEEJAYDELINKCREATOR_H
