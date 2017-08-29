#include "deejaydelinkcreator.h"


QString DeejayDeLinkCreator::create(Module::Mode mode, DataInput& input,
                                    ModuleParameters& params)
{
    QString result;
    QString address = params.data(ModuleParameters::Address).toString();
    switch (mode) {
        case Module::FetchMode :
        {
            QHash<QString, QVariant> hash =
                params.data(ModuleParameters::Styles).toHash();

            QStringList styleInfo =
              hash.value(input.data(DataInput::Style).toString()).toStringList();

            // "http://www.deejay.de/content.php?param=/m_House/sm_News/
            // sort_voe/perpage_160/page_";
            result = address + styleInfo.at(0) + styleInfo.at(1) + "%1";
        }
        break;

        case Module::SearchMode :
        {
            // https://www.deejay.de/moon+harbour/page_1/perpage_160
            // Преобразует строку поиска в запросный вид.
            QString searchString = input.data(DataInput::SearchText).toStringList().at(2);
            searchString.replace(QString(" "), QString("+"));
            result = address + searchString + "/page_%1/perpage_160";
        }
        break;
    }
    return result;
}
