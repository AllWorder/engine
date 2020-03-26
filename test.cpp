#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <time.h>

#include "Head.hpp"
#include "Script.hpp"
#include "Renderer.hpp"
#include "GraphicManager.hpp"
#include "ScriptController.hpp"
#include "GameObject.hpp"
#include "DataStorage.hpp"
#include "Collider.h"
#include "PhysController.h"
#include "Singleton.h"

#include "CustomScripts.hpp"



main()
{

    srand(time(0));

    int j = rand() % 10;
    std::string a = "object";
    a.append(std::to_string(j));
    std::cout << a << '\n';
    
    DataStorage data;
    GrManager graphicsManager;
    SController sc;
    PhysController physController;
    int timer = 0;
    
    Singleton* sing;
    sing = sing -> getInstance();
    
    sing -> data = &data;
    sing -> sc = &sc;
    sing -> grManager = &graphicsManager;
    sing -> timer = &timer;
    sing -> physController = &physController;

    sing -> data -> createObjectInStorage("obj1");
    (data.getObject("obj1")) -> addComponent<Renderer>(sing);
    (data.getObject("obj1")) -> getComponent<Renderer>()->loadTexture("resources/opexus.png");
    (data.getObject("obj1")) -> getComponent<Renderer>()->setSize(100, 100);
    (data.getObject("obj1")) -> addComponent<Collider>(sing);
    (data.getObject("obj1")) -> addComponent<BehaviourWhileCollided>(sing);
    (data.getObject("obj1")) -> getComponent<Collider>() -> shape.addVertex(-50, -50);
    (data.getObject("obj1")) -> getComponent<Collider>() -> shape.addVertex(50, -49);
    (data.getObject("obj1")) -> getComponent<Collider>() -> shape.addVertex(49, 50);
    (data.getObject("obj1")) -> getComponent<Collider>() -> shape.addVertex(-49, 49);
    (data.getObject("obj1")) -> x = 200;
    (data.getObject("obj1")) -> y = 200;

    (data.getObject("obj1")) -> addComponent<PlayerController>(sing);

    //sing -> data -> createObjectInStorage("obj2");
    //(data.getObject("obj2")) -> addComponent<MonsterSpawner>(sing);

    sing -> data -> createObjectInStorage("wall1");
    (data.getObject("wall1")) -> addComponent<Collider>(sing);
    (data.getObject("wall1")) -> addComponent<BehaviourWhileCollided>(sing);
    (data.getObject("wall1")) -> getComponent<Collider>() -> shape.addVertex(500, -500);
    (data.getObject("wall1")) -> getComponent<Collider>() -> shape.addVertex(500, 220);
    (data.getObject("wall1")) -> x = -500;
    (data.getObject("wall1")) -> y = 500;

    sing -> data -> createObjectInStorage("wall2");
    (data.getObject("wall2")) -> addComponent<Collider>(sing);
    (data.getObject("wall2")) -> addComponent<BehaviourWhileCollided>(sing);
    (data.getObject("wall2")) -> getComponent<Collider>() -> shape.addVertex(-500, -280);
    (data.getObject("wall2")) -> getComponent<Collider>() -> shape.addVertex(780, -280);
    (data.getObject("wall2")) -> x = 500;
    (data.getObject("wall2")) -> y = 1000;

    sing -> data -> createObjectInStorage("wall3");
    (data.getObject("wall3")) -> addComponent<Collider>(sing);
    (data.getObject("wall3")) -> addComponent<BehaviourWhileCollided>(sing);
    (data.getObject("wall3")) -> getComponent<Collider>() -> shape.addVertex(-720, 220);
    (data.getObject("wall3")) -> getComponent<Collider>() -> shape.addVertex(-720, -500);
    (data.getObject("wall3")) -> x = 2000;
    (data.getObject("wall3")) -> y = 500;

    sing -> data -> createObjectInStorage("wall4");
    (data.getObject("wall4")) -> addComponent<Collider>(sing);
    (data.getObject("wall4")) -> addComponent<BehaviourWhileCollided>(sing);
    (data.getObject("wall4")) -> getComponent<Collider>() -> shape.addVertex(-500, 500);
    (data.getObject("wall4")) -> getComponent<Collider>() -> shape.addVertex(780, 500);
    (data.getObject("wall4")) -> x = 500;
    (data.getObject("wall4")) -> y = -500;
    
    

    sf::Event event;

    int i = 1;
    std::cout <<  ((data.getObject("wall4")) -> getComponent<BehaviourWhileCollided>()) << '\n';

    while ((graphicsManager.window) -> isOpen())
    {
        timer++;
        //PHISICS: 
        physController.resolveCollisions(physController.findCollisions(), sing);


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
    }

  data.deleteObject("obj1");
  sing -> deleteInstance();       
}
