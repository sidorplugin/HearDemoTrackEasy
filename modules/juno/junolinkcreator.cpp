#include "junolinkcreator.h"

QString JunoLinkCreator::create(Module::Mode mode, DataInput &input,
                                ModuleParameters &params)
{
  QMap<QString, QVariant> map;

  QString address = params.data(ModuleParameters::Address).toString();

  map = params.data(ModuleParameters::Styles).toMap();
  QStringList genreInfo = map.value(input.data(DataInput::Style).toString()).
                                                                toStringList();
  map = params.data(ModuleParameters::Periods).toMap();
  QStringList periodInfo = map.value(input.data(DataInput::Period).toString()).
                                                                toStringList();

  return address + genreInfo.at(0) + "/" + periodInfo.at(0) + "/";
}
