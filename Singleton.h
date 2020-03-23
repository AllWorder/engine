#ifndef SINGLETON
#define SINGLETON

#include "Head.hpp"

class DataStorage;
class GrManager;
class SController;



class Singleton 
{
  private:
  static Singleton* instance;
  Singleton(){};
  Singleton (const Singleton&) {};
  Singleton& operator= (Singleton&) {};
  public:
  GrManager* grManager;
  SController* sc;
  DataStorage* data;
  int* timer;
  static Singleton* getInstance();
  static void deleteInstance();
};

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

#endif