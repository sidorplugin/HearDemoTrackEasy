#ifndef DEEJAYDELINKCREATOR_H
#define DEEJAYDELINKCREATOR_H

#include "baseclasses/linkcreator.h"

class DeejayDeLinkCreator : public LinkCreator
{
public:
  QString create(const DataInput& data, const ModuleParameters& params);
};

#endif // DEEJAYDELINKCREATOR_H
