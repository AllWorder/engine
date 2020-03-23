#include "Head.hpp"
#include "Singleton.h"
#include "Script.hpp"
#include "GraphicManager.hpp"
#include "ScriptController.hpp"
#include "GameObject.hpp"
#include "DataStorage.hpp"
#include "Renderer.hpp"
#include "CustomScripts.hpp"




main()
{

    srand(time(0));
    
    DataStorage data;
    GrManager graphicsManager;
    SController sc;
    int timer = 0;
    
    Singleton* sing;
    sing = sing -> getInstance();
    
    sing -> data = &data;
    sing -> sc = &sc;
    sing -> grManager = &graphicsManager;
    sing -> timer = &timer;

    sing -> data -> createObjectInStorage("obj1");
    (data.getObject("obj1")) -> addComponent<Renderer>(sing);
    (data.getObject("obj1")) -> getComponent<Renderer>()->loadTexture("resources/opexus.png");
    (data.getObject("obj1")) -> getComponent<Renderer>()->setSize(100, 100);

    (data.getObject("obj1")) -> addComponent<PlayerController>(sing);

    sing -> data -> createObjectInStorage("obj2");
    (data.getObject("obj2")) -> addComponent<MonsterSpawner>(sing);
    

    sf::Event event;

    int i = 1;
    std::cout << i << '\n';

    while ((graphicsManager.window) -> isOpen())
    {
        timer++;
        //PHISICS: 


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
