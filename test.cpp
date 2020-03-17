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
    sc.getDataStorageLink(&data);



    data.createObjectInStorage("obj1");
    (data.getObject("obj1")) -> addComponent<Renderer>(&graphicsManager, &sc);
    (data.getObject("obj1")) -> getComponent<Renderer>()->loadTexture("resources/opexus.png");
    (data.getObject("obj1")) -> getComponent<Renderer>()->setSize(100, 100);

	(data.getObject("obj1")) -> addComponent<PlayerController>(&graphicsManager, &sc);


    sf::Event event;

    int i = 1;
    std::cout << i << '\n';

    while ((graphicsManager.window) -> isOpen())
    {
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
		
		sc.doAllScripts();

        //GRAPHICS:

        graphicsManager.drawAll();
    }

  data.deleteObject("obj1");       
}
