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
    GameObject obj1;
    obj1.name = "obj1";
    GrManager graphicsManager;

    obj1.addComponent<Renderer>();
    
    sf::Texture obj1Texture;

    /*Renderer* c =  obj1.getComponent<Renderer>();
    if(c)
        std::cout << "not NULLPTR" << '\n';
    else
        std::cout << "is NULLPTR" << '\n';
    */
    data.addObject(obj1);
    (data.getObject("obj1")) -> getComponent<Renderer>()->loadTexture("resources/opexus.png");
    (data.getObject("obj1")) -> getComponent<Renderer>()->setPosition(300, 400);
    (data.getObject("obj1")) -> getComponent<Renderer>()->setSize(100, 100);

    //obj1.getComponent<Renderer>()->setSize(100, 100);                               PLEASE, STOP DOING LIKE THIS!!!!


    sf::Event event;
    sf::RenderWindow window(sf::VideoMode(SCREEN_X, SCREEN_Y), "game");
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    //(data.getObject("obj1")) -> deleteComponent<Renderer>();

    std::cout << "before cycle" << '\n';
    while (window.isOpen())
    {
        //PHISICS: 

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
  std::cout << "cycle closed" << '\n';
        
}
