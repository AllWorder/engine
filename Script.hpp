#ifndef SCRIPT
#define SCRIPT

#include "Head.hpp"
#include "Singleton.h"


class Script : public Component
{
  public:
  virtual void execute(Singleton* sing)
  {}
  
};

#endif