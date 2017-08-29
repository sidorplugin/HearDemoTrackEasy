#include "hardwaxlinkcreator.h"


QString HardwaxLinkCreator::create(Module::Mode mode, DataInput &input,
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

  map = params.data(ModuleParameters::Filters).toMap();
  QStringList filterInfo = map.value(input.data(DataInput::Filter).toString()).
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
