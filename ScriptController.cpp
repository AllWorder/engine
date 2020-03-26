#include "ScriptController.hpp"
#include "Script.hpp" 

void SController::registerScript(Component* script)
{
  scripts.push_back(static_cast<Script*>(script));
}

void SController::unregisterScript(Component* script)
{
  std::vector<Script*>::iterator i;
  i = scripts.begin();
  for (Script* c: scripts)
    if (c != static_cast<Script*>(script))
      i++;
  scripts.erase(i);
}

void SController::doAllScripts(Singleton* sing)
{
  for (Script* c: scripts)
    c -> execute(sing);
}