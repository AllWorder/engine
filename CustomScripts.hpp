#ifndef CUSTOM_SCRIPTS
#define CUSTOM_SCRIPTS

#include "Head.hpp"

class PlayerController: public Script
{
  public:

  PlayerController()
  {
    this->name = typeid(PlayerController).name();
  }

  void execute(Singleton* sing);

};

class MonsterSpawner: public Script
{
  public:

  MonsterSpawner()
  {
    this->name = typeid(MonsterSpawner).name();
  }

  void execute(Singleton* sing);

};

class Monster : public Script
{
  public:

  Monster()
  {
    this->name = typeid(Monster).name();
  }

  void execute(Singleton* sing)
  {
  }
};

#endif