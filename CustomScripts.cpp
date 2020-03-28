#include "Head.hpp"
#include "Script.hpp"
#include "CustomScripts.hpp"
#include "GameObject.hpp"
#include "Renderer.hpp"
#include "Singleton.h"
#include "GraphicManager.hpp"
#include "ScriptController.hpp"
#include "DataStorage.hpp"
#include "Collider.hpp"
#include "PhysController.hpp"

void PlayerController::execute(Singleton* sing)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        objPointer -> getComponent<Collider>() -> shape.velocityS[1] -= 0.5;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        objPointer -> getComponent<Collider>() -> shape.velocityS[1] += 0.5;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        objPointer -> getComponent<Collider>() -> shape.velocityS[0] -= 0.5;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        objPointer -> getComponent<Collider>() -> shape.velocityS[0] += 0.5;

  objPointer -> x += objPointer -> getComponent<Collider>() -> shape.velocityS[0];
  objPointer -> y += objPointer -> getComponent<Collider>() -> shape.velocityS[1];
  objPointer -> getComponent<Collider>() -> shape.velocityS[0] *= 0.97;
  objPointer -> getComponent<Collider>() -> shape.velocityS[1] *= 0.97;
}

void MonsterSpawner::execute(Singleton* sing)
{
  if (*(sing -> timer) % 10 == 0)
  {
    int monsterID = *(sing -> timer) % 100;
    std::string monsterName = "monster";
    monsterName.append(std::to_string(monsterID)); //giving monster unique name
    std::cout << "spawned " << monsterName << '\n';

    if(sing -> data -> createObjectInStorage(monsterName))  //not to change coordinates of existing objects
    {
      sing -> data -> getObject(monsterName)-> x = rand() % 1100;
      sing -> data -> getObject(monsterName)-> y = rand() % 600;
      sing -> data -> getObject(monsterName) -> addComponent<Renderer>(sing);
      sing -> data -> getObject(monsterName) -> getComponent<Renderer>()->loadTexture("resources/monster.png");
      sing -> data -> getObject(monsterName) -> getComponent<Renderer>()->setSize(100, 150);
    }

  }
}
