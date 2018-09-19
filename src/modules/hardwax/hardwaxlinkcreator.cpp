#include "hardwaxlinkcreator.h"


QString HardwaxLinkCreator::create(int mode, const InputPack& input, ModuleParameters& params)
{
  QMap<QString, QVariant> map;

  QString address = params.data(ModuleParameters::Address).toString();

  map = params.data(ModuleParameters::Styles).toMap();
  QStringList genreInfo = map.value(input.fetchPack.style).toStringList();

  map = params.data(ModuleParameters::Periods).toMap();
  QStringList periodInfo = map.value(input.fetchPack.period).toStringList();

  map = params.data(ModuleParameters::Filters).toMap();
  QStringList filterInfo = map.value(input.fetchPack.filter).toStringList();

  QString result;
  if (!genreInfo.at(0).isEmpty()) {
    result = address + genreInfo.at(0) + genreInfo.at(1) + "%1";
  }
  else if (!periodInfo.at(0).isEmpty()) {
    result = address + periodInfo.at(0) + periodInfo.at(1) + "%1";
  }
  else if (!filterInfo.at(0).isEmpty()) {
    result = address + filterInfo.at(0) + filterInfo.at(1) + "%1";
  }

  return result;
}
