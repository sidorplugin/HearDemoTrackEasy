#include "deejaydelinkcreator.h"


QString DeejayDeLinkCreator::create(Module::Mode mode, const DataInput& data,
                                    const ModuleParameters& params)
{
    switch (mode) {
        case Module::FetchMode :
        {
            QString address = params.address();
            QStringList genreInfo = params.genreInfo(data.genre);

            // "http://www.deejay.de/content.php?param=/m_House/sm_News/
            // sort_voe/perpage_160/page_";
            return address + genreInfo.at(VALUE) + genreInfo.at(LINK);
        }
        break;

        case Module::SearchMode :
        {
            // https://www.deejay.de/lord+sausage
            // TODO.
            // Преобразует строку поиска в запросный вид.
            return "https://www.deejay.de/" + data.search;
        }
        break;
    }
}
