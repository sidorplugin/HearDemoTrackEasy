#include "hardwaxlinkcreator.h"


QString HardwaxLinkCreator::create(Module::Mode mode, DataInput &input,
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

  hash = params.data(ModuleParameters::Filters).toHash();
  QStringList filterInfo = hash.value(input.data(DataInput::Filter).toString()).
                                                                 toStringList();

  QString link = genreInfo.at(1);


  QString result;
  if (!genreInfo.at(0).isEmpty()) {
    result = address + genreInfo.at(0) + link;
  }
  else if (!periodInfo.at(0).isEmpty()) {
    result = address + periodInfo.at(0) + link;
  }
  else if (!filterInfo.at(0).isEmpty()) {
    result = address + filterInfo.at(0) + link;
  }

  return result;
}
