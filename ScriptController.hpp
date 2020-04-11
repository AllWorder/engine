#ifndef SCRIPT_CONTROLLER
#define SCRIPT_CONTROLLER

#include "Head.hpp"


class SController
{
  public:

  void registerScript(Component* script);
  void unregisterScript(Component* script);
  void doAllScripts(Singleton* sing);
  
  std::vector<Script*> scripts;
};

#endif
