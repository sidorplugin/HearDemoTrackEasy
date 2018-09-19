#ifndef DEEJAYDEMODULEFACTORY
#define DEEJAYDEMODULEFACTORY

#include "baseclasses/modulefactory.h"
#include "modules/deejayde/deejaydefetcher.h"
#include "modules/deejayde/deejaydepagesearcher.h"
#include "modules/deejayde/deejaydelinkcreator.h"

// Фабрика для создания DeejayDe модуля.

class DeejayDeModuleFactory : public ModuleFactory
{
public:
  Fetcher* createFetcher() {
    return new DeejayDeFetcher;
  }

  PageSearcher* createPageSearcher() {
    return new DeejayDePageSearcher;
  }

  LinkCreator* createLinkCreator() {
    return new DeejayDeLinkCreator;
  }

  ModuleParameters createParameters() {
    return readFromXmlFile(":/data/data/deejayDe_module.xml");
  }

};

#endif // DEEJAYDEMODULEFACTORY

