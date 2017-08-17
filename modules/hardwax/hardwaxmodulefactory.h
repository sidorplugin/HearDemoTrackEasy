#ifndef HARDWAXMODULEFACTORY
#define HARDWAXMODULEFACTORY

#include "baseclasses/modulefactory.h"
#include "modules/hardwax/hardwaxfetcher.h"
#include "modules/hardwax/hardwaxpagesearcher.h"
#include "modules/hardwax/hardwaxlinkcreator.h"

// Фабрика для создания Hardwax модуля.

class HardwaxModuleFactory : public ModuleFactory
{
public:
  Fetcher* createFetcher() {
    return new HardwaxFetcher;
  }

  Fetcher* createAlbumFetcher() {
    return 0;
  }

  PageSearcher* createPageSearcher() {
    return new HardwaxPageSearcher;
  }

  LinkCreator* createLinkCreator() {
    return new HardwaxLinkCreator;
  }

  ModuleParameters createParameters() {
    foreach (ModuleParameters p, GlobalData::getInstance()->parameters) {
      if (p.name() == "Hardwax")
        return p;
    }
    return ModuleParameters();
  }


};

#endif // HARDWAXMODULEFACTORY

