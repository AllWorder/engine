#include <iostream>
#include <vector>
#include <iterator>
#include "Head.h"
#include "Script.h"
#include "Renderer.hpp"
#include "GrManager.h"
#include "SController.h"
#include "GameObject.hpp"
#include "DataStorage.hpp"



class TestComponent: public Component
{
    public:

    TestComponent()
    {
        this->name = typeid(TestComponent).name();
    }

};

main()
{
    
    DataStorage data;
    //GameObject obj1;
    //obj1.name = "obj1";
    GrManager graphicsManager;
    SController sc;



    data.createObjectInStorage("obj1"); //?
    (data.getObject("obj1")) -> addComponent<Renderer>(&graphicsManager, &sc);

    (data.getObject("obj1")) -> getComponent<Renderer>()->loadTexture("resources/opexus.png");
    (data.getObject("obj1")) -> getComponent<Renderer>()->setSize(100, 100);
	
	Monster monstr;
	std::cout << (std::is_base_of<Script, Renderer>::value) << '\n';
	(data.getObject("obj1")) -> addComponent<Monster>(&graphicsManager, &sc);
	//sc.registerScript(&monstr);


    sf::Event event;

    int newX = 0;
    int newY = 0;

	

    while ((graphicsManager.window) -> isOpen())
    {
        //PHISICS: 

        
        (data.getObject("obj1")) -> x = newX;
        (data.getObject("obj1")) -> y = newY;

        newX = newX + 1;    
        newY += 1;


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
