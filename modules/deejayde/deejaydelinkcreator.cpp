#include "deejaydelinkcreator.h"


QString DeejayDeLinkCreator::create(Module::Mode mode, DataInput& input,
                                    const ModuleParameters& params)
{
    switch (mode) {
        case Module::FetchMode :
        {
            QString address = params.address();
            QStringList genreInfo = params.genreInfo(
                                    input.data(DataInput::Genre).toString());

            // "http://www.deejay.de/content.php?param=/m_House/sm_News/
            // sort_voe/perpage_160/page_";
            return address + genreInfo.at(VALUE) + genreInfo.at(LINK) + "%1";
        }
        break;

        case Module::SearchMode :
        {
            // https://www.deejay.de/moon+harbour/page_1/perpage_160
            // Преобразует строку поиска в запросный вид.
            QString searchString = input.data(DataInput::Search).toStringList().at(2);
            searchString.replace(QString(" "), QString("+"));
            return "https://www.deejay.de/" + searchString + "/page_%1/perpage_160";
        }
        break;
    }
}
