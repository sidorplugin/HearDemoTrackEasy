#include "junolinkcreator.h"

QString JunoLinkCreator::create(Module::Mode mode, DataInput &input,
                                ModuleParameters &params)
{
  QHash<QString, QVariant> hash;

  QString address = params.data(ModuleParameters::Address).toString();

  hash = params.data(ModuleParameters::Styles).toHash();
  QStringList genreInfo = hash.value(input.data(DataInput::Style).toString()).
                                                                toStringList();
  hash = params.data(ModuleParameters::Periods).toHash();
  QStringList periodInfo = hash.value(input.data(DataInput::Period).toString()).
                                                                toStringList();

  return address + genreInfo.at(0) + "/" + periodInfo.at(0) + "/";
}
