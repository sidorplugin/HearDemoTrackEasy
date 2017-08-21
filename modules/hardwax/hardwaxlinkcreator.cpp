#include "hardwaxlinkcreator.h"


QString HardwaxLinkCreator::create(Module::Mode mode, DataInput &input,
                                   const ModuleParameters &params)
{
  QString address = params.address();
  QStringList genreInfo = params.genreInfo(input.data(DataInput::Genre).toString());
  QStringList periodInfo = params.periodInfo(input.data(DataInput::Period).toString());
  QStringList filterInfo = params.filterInfo(input.data(DataInput::Filter).toString());
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
