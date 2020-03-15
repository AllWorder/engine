#include <iostream>
#include <vector>
#include <iterator>
#include "DataStorage.hpp"
#include "Renderer.hpp"
#include "GrManager.h"

const int SCREEN_Y = 720;
const int SCREEN_X = 1280;

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



    data.createObjectInStorage("obj1"); //?
    (data.getObject("obj1")) -> addComponent<Renderer>();

    (data.getObject("obj1")) -> getComponent<Renderer>()->loadTexture("resources/opexus.png");
    (data.getObject("obj1")) -> getComponent<Renderer>()->setSize(100, 100);



    sf::Event event;
    sf::RenderWindow window(sf::VideoMode(SCREEN_X, SCREEN_Y), "game");
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    int newX = 0;
    int newY = 0;

    while (window.isOpen())
    {
        //PHISICS: 

        
        (data.getObject("obj1")) -> x = newX;
        (data.getObject("obj1")) -> y = newY;

        newX = newX + 1;    
        newY += 1;


        //EVENT HANDLER

        while (window.pollEvent(event))
		{
		    if (event.type == sf::Event::Closed) 
                  window.close();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window.close();

        //LOGICS:

        //GRAPHICS:

        graphicsManager.drawAll(&window, &data);
    }

  data.deleteObject("obj1");       
}
