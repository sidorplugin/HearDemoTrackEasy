#ifndef JUNOMODULEFACTORY
#define JUNOMODULEFACTORY

#include "baseclasses/modulefactory.h"
#include "modules/juno/junofetcher.h"
#include "modules/juno/junopagesearcher.h"
#include "modules/juno/junolinkcreator.h"

// Фабрика для создания Juno модуля.

class JunoModuleFactory : public ModuleFactory
{
public:
  Fetcher* createFetcher() {
    return new JunoFetcher;
  }

  Fetcher* createAlbumFetcher() {
    return 0;
  }

  PageSearcher* createPageSearcher() {
    return new JunoPageSearcher;
  }

  LinkCreator* createLinkCreator() {
    return new JunoLinkCreator;
  }

  ModuleParameters createParameters() {
    foreach (ModuleParameters p, GlobalData::getInstance()->parameters) {
      if (p.data(ModuleParameters::Name).toString() == "Juno")
        return p;
    }
    return ModuleParameters();
  }

};

#endif // JUNOMODULEFACTORY

