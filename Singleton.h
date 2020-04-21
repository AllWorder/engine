#ifndef SINGLETON
#define SINGLETON

#include "Head.hpp"


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
    PhysController* physController;
    AnimationConroller* animationConroller;

    int* timer;

    static Singleton* getInstance();
    static void deleteInstance();
};



#endif
