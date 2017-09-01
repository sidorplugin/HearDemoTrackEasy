#ifndef MODULEFACTORY
#define MODULEFACTORY

#include "globaldata.h"
#include "dataclasses/moduleparameters.h"
#include "baseclasses/fetcher.h"
#include "baseclasses/linkcreator.h"
#include "baseclasses/pagesearcher.h"

// Абстрактная фабрика для производства модулей.

class ModuleFactory
{
public:
  virtual Fetcher* createFetcher() = 0;
  virtual PageSearcher* createPageSearcher() = 0;
  virtual LinkCreator* createLinkCreator() = 0;
  virtual ModuleParameters createParameters() = 0;

  virtual ~ModuleFactory() {}
};

#endif // MODULEFACTORY

