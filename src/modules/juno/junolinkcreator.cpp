#include "junolinkcreator.h"

QString JunoLinkCreator::create(int mode, const InputPack& input, ModuleParameters& params)
{
  QMap<QString, QVariant> map;

  QString address = params.data(ModuleParameters::Address).toString();

  map = params.data(ModuleParameters::Styles).toMap();
  QStringList genreInfo = map.value(input.fetchPack.style).toStringList();
  map = params.data(ModuleParameters::Periods).toMap();
  QStringList periodInfo = map.value(input.fetchPack.period).toStringList();

  return address + genreInfo.at(0) + "/" + periodInfo.at(0) + "/" + "%1";
}
