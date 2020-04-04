#include "Head.hpp"

#include "Singleton.h"
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

// for compilation use:
//g++ test.cpp CustomScripts.cpp DataStorage.cpp GraphicManager.cpp Renderer.cpp ScriptController.cpp Singleton.cpp Collider.cpp PhysController.cpp Animator.cpp -o test.app -lsfml-graphics -lsfml-window -lsfml-system

Singleton* sing;

#include "API.hpp"

main()
{  
    
    DataStorage data;
    GrManager graphicsManager;
    SController sc;
    PhysController physController;
    AnimationConroller animationConroller;

    int timer = 0;
    
    //Singleton* sing;
    sing = sing -> getInstance();
    
    sing -> data = &data;
    sing -> sc = &sc;
    sing -> grManager = &graphicsManager;
    sing -> timer = &timer;
    sing -> physController = &physController;
    sing -> animationConroller = &animationConroller;

    sing -> data -> createObjectInStorage("obj1"); //player 
    (data.getObject("obj1")) -> addComponent<Renderer>(sing);
    (data.getObject("obj1")) -> getComponent<Renderer>()->loadTexture("resources/opexus.png");
    (data.getObject("obj1")) -> getComponent<Renderer>()->setSize(100, 100);
    (data.getObject("obj1")) -> addComponent<Collider>(sing);
    (data.getObject("obj1")) -> addComponent<BWCollided_player>(sing);
    (data.getObject("obj1")) -> getComponent<Collider>() -> shape.addVertex(-50, -50);
    (data.getObject("obj1")) -> getComponent<Collider>() -> shape.addVertex(50, -49);
    (data.getObject("obj1")) -> getComponent<Collider>() -> shape.addVertex(49, 50);
    (data.getObject("obj1")) -> getComponent<Collider>() -> shape.addVertex(-49, 49);
    (data.getObject("obj1")) -> x = 500;
    (data.getObject("obj1")) -> y = 360;

    (data.getObject("obj1")) -> addComponent<PlayerController>(sing);
    (data.getObject("obj1")) -> addComponent<VelocityPhysic>(sing);
    (data.getObject("obj1")) -> addComponent<GravitationPhysic>(sing);




    sing -> data -> createObjectInStorage("wall1");
    (data.getObject("wall1")) -> addComponent<Collider>(sing);
    (data.getObject("wall1")) -> getComponent<Collider>() -> shape.ifMoveable = false;
    (data.getObject("wall1")) -> addComponent<BWCollided_wall>(sing);
    (data.getObject("wall1")) -> getComponent<Collider>() -> shape.addVertex(500, -500);
    (data.getObject("wall1")) -> getComponent<Collider>() -> shape.addVertex(500, 220);
    (data.getObject("wall1")) -> x = -500;
    (data.getObject("wall1")) -> y = 500;

    sing -> data -> createObjectInStorage("wall2");
    (data.getObject("wall2")) -> addComponent<Collider>(sing);
    (data.getObject("wall2")) -> getComponent<Collider>() -> shape.ifMoveable = false;
    //(data.getObject("wall2")) -> getComponent<Collider>() -> shape.ifElastic = false;
    (data.getObject("wall2")) -> addComponent<BWCollided_wall>(sing);
    (data.getObject("wall2")) -> getComponent<Collider>() -> shape.addVertex(-500, -280);
    (data.getObject("wall2")) -> getComponent<Collider>() -> shape.addVertex(780, -280);
    (data.getObject("wall2")) -> x = 500;
    (data.getObject("wall2")) -> y = 1000;

    sing -> data -> createObjectInStorage("wall3");
    (data.getObject("wall3")) -> addComponent<Collider>(sing);
    (data.getObject("wall3")) -> getComponent<Collider>() -> shape.ifMoveable = false;
    (data.getObject("wall3")) -> addComponent<BWCollided_wall>(sing);
    (data.getObject("wall3")) -> getComponent<Collider>() -> shape.addVertex(-720, 220);
    (data.getObject("wall3")) -> getComponent<Collider>() -> shape.addVertex(-720, -500);
    (data.getObject("wall3")) -> x = 2000;
    (data.getObject("wall3")) -> y = 500;

    sing -> data -> createObjectInStorage("wall4");
    (data.getObject("wall4")) -> addComponent<Collider>(sing);
    (data.getObject("wall4")) -> getComponent<Collider>() -> shape.ifMoveable = false;
    (data.getObject("wall4")) -> addComponent<BWCollided_wall>(sing);
    (data.getObject("wall4")) -> getComponent<Collider>() -> shape.addVertex(-500, 500);
    (data.getObject("wall4")) -> getComponent<Collider>() -> shape.addVertex(780, 500);
    (data.getObject("wall4")) -> x = 500;
    (data.getObject("wall4")) -> y = -500;

    sing -> data -> createObjectInStorage("obj2"); 
    (data.getObject("obj2")) -> addComponent<Renderer>(sing);
    (data.getObject("obj2")) -> getComponent<Renderer>()->loadTexture("resources/monster.png");
    (data.getObject("obj2")) -> getComponent<Renderer>()->setSize(100, 100);
    (data.getObject("obj2")) -> addComponent<Collider>(sing);
    (data.getObject("obj2")) -> addComponent<BWCollided_player>(sing);
    (data.getObject("obj2")) -> getComponent<Collider>() -> shape.addVertex(-50, -50);
    (data.getObject("obj2")) -> getComponent<Collider>() -> shape.mass = 0.3;
    (data.getObject("obj2")) -> getComponent<Collider>() -> shape.addVertex(50, -49);
    (data.getObject("obj2")) -> getComponent<Collider>() -> shape.addVertex(49, 50);
    (data.getObject("obj2")) -> getComponent<Collider>() -> shape.addVertex(-49, 49);
    (data.getObject("obj2")) -> x = 300;
    (data.getObject("obj2")) -> y = 330;
    (data.getObject("obj2")) -> getComponent<Collider>() -> shape.setVelocity(5, 0); 
    (data.getObject("obj2")) -> addComponent<VelocityPhysic>(sing);
    (data.getObject("obj2")) -> getComponent<VelocityPhysic>() -> isHasInertion = false;

    //sing -> data -> createObjectInStorage("spawner");
    //(data.getObject("spawner")) -> addComponent<MonsterSpawner>(sing);

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




    

    









    
    

    sf::Event event;

    int i = 1;

    while ((graphicsManager.window) -> isOpen())
    {
        timer++;
        //PHISICS: 

        physController.resolveCollisions(physController.findCollisions(), sing);
        physController.doAllPhysics(sing);


        //EVENT HANDLER

        while ((graphicsManager.window) -> pollEvent(event))
		{
		    if (event.type == sf::Event::Closed) 
                  (graphicsManager.window) -> close();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            (graphicsManager.window) -> close();

        //LOGICS:
        
         
		
		sc.doAllScripts(sing);

        //GRAPHICS:

        graphicsManager.drawAll();
        animationConroller.doAllAnimations(sing);
    }

  //data.deleteObject("obj1");
  sing -> deleteInstance();       
}
