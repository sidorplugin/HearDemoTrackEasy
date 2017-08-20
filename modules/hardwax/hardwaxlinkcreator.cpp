#include "hardwaxlinkcreator.h"


QString HardwaxLinkCreator::create(Module::Mode mode, const DataInput &data,
                                   const ModuleParameters &params)
{
  QString address = params.address();
  QStringList genreInfo = params.genreInfo(data.genre);
  QStringList periodInfo = params.periodInfo(data.period);
  QStringList filterInfo = params.filterInfo(data.filter);
  QString link = genreInfo.at(LINK);


  QString result;
  if (!genreInfo.at(VALUE).isEmpty()) {
    result = address + genreInfo.at(VALUE) + link;
  }
  else if (!periodInfo.at(VALUE).isEmpty()) {
    result = address + periodInfo.at(VALUE) + link;
  }
  else if (!filterInfo.at(VALUE).isEmpty()) {
    result = address + filterInfo.at(VALUE) + link;
  }

  return result;
}
