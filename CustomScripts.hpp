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

void initScript(std::string name, std::string objName, DataStorage* data, Singleton* sing);
void initVelocityPhysic(std::string object, Singleton* sing, std::string component);
void initGravitationPhysic(std::string object, Singleton* sing, std::string component);

#endif
