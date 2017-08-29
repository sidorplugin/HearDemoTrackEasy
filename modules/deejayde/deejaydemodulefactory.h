#ifndef DEEJAYDEMODULEFACTORY
#define DEEJAYDEMODULEFACTORY

#include "baseclasses/modulefactory.h"
#include "modules/deejayde/deejaydefetcher.h"
#include "modules/deejayde/deejaydealbumfetcher.h"
#include "modules/deejayde/deejaydepagesearcher.h"
#include "modules/deejayde/deejaydelinkcreator.h"

// Фабрика для создания DeejayDe модуля.

class DeejayDeModuleFactory : public ModuleFactory
{
public:
  Fetcher* createFetcher() {
    return new DeejayDeFetcher;
  }

  Fetcher* createAlbumFetcher() {
    return new DeejayDeAlbumFetcher;
  }

  PageSearcher* createPageSearcher() {
    return new DeejayDePageSearcher;
  }

  LinkCreator* createLinkCreator() {
    return new DeejayDeLinkCreator;
  }

  ModuleParameters createParameters() {
    foreach (ModuleParameters p, GlobalData::getInstance()->parameters) {
      if (p.data(ModuleParameters::Name).toString() == "DeejayDe")
        return p;
    }
    return ModuleParameters();
  }

};

#endif // DEEJAYDEMODULEFACTORY

