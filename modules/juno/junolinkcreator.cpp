#include "junolinkcreator.h"

QString JunoLinkCreator::create(Module::Mode mode, const DataInput &data,
                                const ModuleParameters &params)
{
  QString address = params.address();
  QStringList genreInfo = params.genreInfo(data.genre);
  QStringList periodInfo = params.periodInfo(data.period);

  return address + genreInfo.at(VALUE) + "/" + periodInfo.at(VALUE) + "/";
}
