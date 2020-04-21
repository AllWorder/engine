#include "Singleton.h"
#include "DataStorage.hpp"
#include "Script.hpp"
#include "GraphicManager.hpp"
#include "ScriptController.hpp"
#include "GameObject.hpp"
#include "Renderer.hpp"
#include "CustomScripts.hpp"

#include "Collider.hpp"
#include "PhysController.hpp"
#include "PhysicScripts.hpp"
#include "Animator.hpp"

Singleton* Singleton::getInstance()
{
  if (!instance)
  {
    instance = new Singleton();
    instance -> data = new DataStorage();
    instance -> sc = new SController;
    instance -> grManager = new GrManager;
    instance -> timer = new int;
    *(instance -> timer) = 0;
    instance -> physController = new PhysController;
    instance -> animationConroller =  new AnimationConroller;
    return instance;
  } 
  return instance;
}

void Singleton::deleteInstance()
{
  if (!instance)
  {
    delete instance -> data;
    delete instance -> sc;
    delete instance -> grManager;
    delete instance -> timer;
    delete instance -> physController;
    delete instance -> animationConroller;
    delete instance;
    instance = 0;
  }
}

Singleton* Singleton::instance = 0;


