#include "Head.hpp"


#include "Script.hpp"
#include "GraphicManager.hpp"
#include "ScriptController.hpp"
#include "GameObject.hpp"
#include "DataStorage.hpp"
#include "Renderer.hpp"
#include "CustomScripts.hpp"

#include "Collider.hpp"
#include "PhysController.hpp"
#include "PhysicScripts.hpp"
#include "Animator.hpp"
#include "Singleton.h"
Singleton* sing;
#include "gameRun.hpp"

// for compilation use:
//g++ test.cpp CustomScripts.cpp DataStorage.cpp GraphicManager.cpp Renderer.cpp ScriptController.cpp Singleton.cpp Collider.cpp PhysController.cpp Animator.cpp -o test -lsfml-graphics -lsfml-window -lsfml-system
// after use:
// ./test


#include "API.hpp"

main()
{ 
    sing = sing -> getInstance();

    API::createObject("obj1"); //player 
    API::getObject("obj1") -> addComponent<Renderer>(sing);
    API::getObject("obj1") -> getComponent<Renderer>()->loadTexture("resources/opexus.png");
    API::getObject("obj1") -> getComponent<Renderer>()->setSize(100, 100);
    API::getObject("obj1") -> addComponent<Collider>(sing);
    API::getObject("obj1") -> addComponent<BWCollided_player>(sing);
    API::setSquareVertexes("obj1", 100, 100);
    API::getObject("obj1") -> x = 500;
    API::getObject("obj1") -> y = 360;

    API::getObject("obj1") -> addComponent<PlayerController>(sing);
    API::getObject("obj1") -> addComponent<VelocityPhysic>(sing);
    API::getObject("obj1") -> addComponent<GravitationPhysic>(sing);




    API::createObject("wall1");
    API::getObject("wall1") -> addComponent<Collider>(sing);
    API::getObject("wall1") -> getComponent<Collider>() -> shape.ifMoveable = false;
    API::getObject("wall1") -> addComponent<BWCollided_wall>(sing);
    API::getObject("wall1") -> getComponent<Collider>() -> shape.addVertex(500, -500);
    API::getObject("wall1") -> getComponent<Collider>() -> shape.addVertex(500, 220);
    API::getObject("wall1") -> x = -500;
    API::getObject("wall1") -> y = 500;

    API::createObject("wall2");
    API::getObject("wall2") -> addComponent<Collider>(sing);
    API::getObject("wall2") -> getComponent<Collider>() -> shape.ifMoveable = false;
    //(data.getObject("wall2")) -> getComponent<Collider>() -> shape.ifElastic = false;
    API::getObject("wall2") -> addComponent<BWCollided_wall>(sing);
    API::getObject("wall2") -> getComponent<Collider>() -> shape.addVertex(-500, -280);
    API::getObject("wall2") -> getComponent<Collider>() -> shape.addVertex(780, -280);
    API::getObject("wall2") -> x = 500;
    API::getObject("wall2") -> y = 1000;

    API::createObject("wall3");
    API::getObject("wall3") -> addComponent<Collider>(sing);
    API::getObject("wall3") -> getComponent<Collider>() -> shape.ifMoveable = false;
    API::getObject("wall3") -> addComponent<BWCollided_wall>(sing);
    API::getObject("wall3") -> getComponent<Collider>() -> shape.addVertex(-720, 220);
    API::getObject("wall3") -> getComponent<Collider>() -> shape.addVertex(-720, -500);
    API::getObject("wall3") -> x = 2000;
    API::getObject("wall3") -> y = 500;

    API::createObject("wall4");
    API::getObject("wall4") -> addComponent<Collider>(sing);
    API::getObject("wall4") -> getComponent<Collider>() -> shape.ifMoveable = false;
    API::getObject("wall4") -> addComponent<BWCollided_wall>(sing);
    API::getObject("wall4") -> getComponent<Collider>() -> shape.addVertex(-500, 500);
    API::getObject("wall4") -> getComponent<Collider>() -> shape.addVertex(780, 500);
    API::getObject("wall4") -> x = 500;
    API::getObject("wall4") -> y = -500;

    API::createObject("obj2"); 
    API::getObject("obj2") -> addComponent<Renderer>(sing);
    API::getObject("obj2") -> getComponent<Renderer>()->loadTexture("resources/monster.png");
    API::getObject("obj2") -> getComponent<Renderer>()->setSize(100, 100);
    API::getObject("obj2") -> addComponent<Collider>(sing);
    API::getObject("obj2") -> addComponent<BWCollided_player>(sing);
    API::getObject("obj2") -> getComponent<Collider>() -> shape.addVertex(-50, -50);
    API::getObject("obj2") -> getComponent<Collider>() -> shape.mass = 0.3;
    API::getObject("obj2") -> getComponent<Collider>() -> shape.addVertex(50, -49);
    API::getObject("obj2") -> getComponent<Collider>() -> shape.addVertex(49, 50);
    API::getObject("obj2") -> getComponent<Collider>() -> shape.addVertex(-49, 49);
    API::getObject("obj2") -> x = 300;
    API::getObject("obj2") -> y = 330;
    API::getObject("obj2") -> getComponent<Collider>() -> shape.setVelocity(5, 0); 
    API::getObject("obj2") -> addComponent<VelocityPhysic>(sing);
    //(data.getObject("obj2")) -> getComponent<VelocityPhysic>() -> isHasInertion = false;

    API::createObject("spawner");
    API::getObject("spawner") -> addComponent<MonsterSpawner>(sing);

    API::createObject("bumbleBee");
    API::getObject("bumbleBee") -> addComponent<Renderer>(sing);
    API::getObject("bumbleBee") -> getComponent<Renderer>() -> loadTexture("resources/bb.png");
    API::getObject("bumbleBee") -> getComponent<Renderer>() -> setSize(200, 200);
    API::getObject("bumbleBee") -> x = 500;
    API::getObject("bumbleBee") -> y = 500;

    API::getObject("bumbleBee") -> addComponent<Animation>(sing);
    API::getObject("bumbleBee") -> getComponent<Animation>() -> addTexture("resources/bb.png");
    API::getObject("bumbleBee") -> getComponent<Animation>() -> addTexture("resources/bb1.png");
    API::getObject("bumbleBee") -> getComponent<Animation>() -> addTexture("resources/bb2.png");
    API::getObject("bumbleBee") -> getComponent<Animation>() -> addTexture("resources/bb3.png");
    API::getObject("bumbleBee") -> getComponent<Animation>() -> ticksPerAnimation = 10;

    API::createObject("background");
    API::getObject("background") -> addComponent<Renderer>(sing);
    API::getObject("background") -> getComponent<Renderer>() -> loadTexture("resources/background.jpg");
    API::getObject("background") -> getComponent<Renderer>() -> setSize(SCREEN_X, SCREEN_Y);
    API::getObject("background") -> x = SCREEN_X / 2;
    API::getObject("background") -> y = SCREEN_Y / 2;
    API::getObject("background") -> getComponent<Renderer>() -> layer = 3;




    while (gameRun())
    {
      //YOUR CODE AND LOGICS HERE
    }

  sing -> deleteInstance();       
}
