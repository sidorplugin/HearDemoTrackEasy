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

  PageSearcher* createPageSearcher() {
    return new JunoPageSearcher;
  }

  LinkCreator* createLinkCreator() {
    return new JunoLinkCreator;
  }

  ModuleParameters createParameters() {
    return readFromXmlFile(":/data/data/juno_module.xml");
  }

};

#endif // JUNOMODULEFACTORY

