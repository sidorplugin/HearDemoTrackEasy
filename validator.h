#ifndef VALIDATOR_H
#define VALIDATOR_H

#include "dataclasses/datainput.h"

class Validator
{
public:
  Validator();

  bool verify(int action, DataInput& input);
};

#endif // VALIDATOR_H
