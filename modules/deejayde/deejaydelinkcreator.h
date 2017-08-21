#ifndef DEEJAYDELINKCREATOR_H
#define DEEJAYDELINKCREATOR_H

#include "baseclasses/linkcreator.h"

class DeejayDeLinkCreator : public LinkCreator
{
public:
  QString create(Module::Mode mode, DataInput& input,
                 const ModuleParameters& params);
};

#endif // DEEJAYDELINKCREATOR_H
