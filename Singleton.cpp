#include "Singleton.h"

Singleton* Singleton::getInstance()
{
  if (!instance)
  {
    instance = new Singleton();
    return instance;
  } 
  return instance;
}

void Singleton::deleteInstance()
{
  if (!instance)
  {
    delete instance;
    instance = 0;
  }
}

Singleton* Singleton::instance = 0;