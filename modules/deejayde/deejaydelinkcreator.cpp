#include "deejaydelinkcreator.h"


QString DeejayDeLinkCreator::create(const DataInput& data,
                                    const ModuleParameters& params)
{
  QString address = params.address();
  QStringList genreInfo = params.genreInfo(data.genre);

  // "http://www.deejay.de/content.php?param=/m_House/sm_News/sort_voe/perpage_160/page_";
  return address + genreInfo.at(VALUE) + genreInfo.at(LINK);
}
