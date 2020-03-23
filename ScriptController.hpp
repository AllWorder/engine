#ifndef SCRIPT_CONTROLLER
#define SCRIPT_CONTROLLER

#include "Head.hpp"
#include "Script.hpp"
#include "Singleton.h"




class SController
{
  public:

  void registerScript(Component* script);
  void unregisterScript(Component* script);
  void doAllScripts(Singleton* sing);
  
  std::vector<Script*> scripts;
};

#endif
