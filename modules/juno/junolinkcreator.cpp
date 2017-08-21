#include "junolinkcreator.h"

QString JunoLinkCreator::create(Module::Mode mode, DataInput &input,
                                const ModuleParameters &params)
{
  QString address = params.address();
  QStringList genreInfo = params.genreInfo(input.data(DataInput::Genre).toString());
  QStringList periodInfo = params.periodInfo(input.data(DataInput::Period).toString());

  return address + genreInfo.at(VALUE) + "/" + periodInfo.at(VALUE) + "/";
}
