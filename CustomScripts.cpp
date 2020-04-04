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
#include "PhysicScripts.hpp"
//#include "API.hpp"

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

}

void BWCollided_player::collisionResolving(Collider* source, Collider* enemy)
{
    //logics

    if (source -> checkDiverge(enemy) == false)                            
    {
      
      if ((enemy -> shape.ifElastic == true) and (source -> shape.ifElastic == true))
        source -> elasticHit(source, enemy);
      else
        source -> inelasticHit(source, enemy);
    }
}

void BWCollided_wall::collisionResolving(Collider* source, Collider* enemy)
{
  return;
}

void MonsterSpawner::execute(Singleton* sing)
{
  if (*(sing -> timer) % 100 == 0)
  {
    int monsterID = rand() % 10;
    std::string monsterName = "monster";
    monsterName.append(std::to_string(monsterID)); //giving monster unique name
    std::cout << "spawned " << monsterName << '\n';

    if(sing -> data -> createObjectInStorage(monsterName))  //not to change coordinates of existing objects
    {
      sing -> data -> getObject(monsterName)-> x = rand() % 1100;
      sing -> data -> getObject(monsterName)-> y = rand() % 600;
      sing -> data -> getObject(monsterName) -> addComponent<Renderer>(sing);
      sing -> data -> getObject(monsterName) -> getComponent<Renderer>()->loadTexture("resources/monster.png");
      sing -> data -> getObject(monsterName) -> getComponent<Renderer>()->setSize(100, 100);
      sing -> data -> getObject(monsterName) -> addComponent<Collider>(sing);
      sing -> data -> getObject(monsterName) -> addComponent<BWCollided_player>(sing);
      sing -> data -> getObject(monsterName) -> getComponent<Collider>() -> shape.addVertex(-50, -50);
      sing -> data -> getObject(monsterName) -> getComponent<Collider>() -> shape.addVertex(50, -49);
      sing -> data -> getObject(monsterName) -> getComponent<Collider>() -> shape.addVertex(49, 50);
      sing -> data -> getObject(monsterName) -> getComponent<Collider>() -> shape.addVertex(-49, 49);
      sing -> data -> getObject(monsterName) -> getComponent<Collider>() -> shape.setVelocity(rand() % 10, rand () % 10); 
      sing -> data -> getObject(monsterName) -> addComponent<VelocityPhysic>(sing);
      std::cout << "already spawned " << monsterName << '\n';
      sing -> data -> getObject(monsterName) -> getComponent<Collider>() -> shape.mass = 0.3;

    }

  }
}
