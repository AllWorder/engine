#include <iostream>
#include <vector>
#include "DataStorage.hpp"
#include "Renderer.hpp"

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

    if(obj1.addComponent<Renderer>())
    {}

    sf::Texture obj1Texture;
    //if (!obj1Texture.loadFromFile("resources/opexus.png"))
    //{
    //    std::cout << "Loading texture erorr" << "\n";
    //}

    Renderer* c =  obj1.getComponent<Renderer>();
    if(c)
        std::cout << "not NULLPTR" << '\n';
    else
        std::cout << "is NULLPTR" << '\n';
    
    
    //obj1.getComponent<Renderer>()->setTexture(&obj1Texture);
    obj1.getComponent<Renderer>()->loadTexture("resources/opexus.png");
    obj1.getComponent<Renderer>()->setPosition(300, 400);
    obj1.getComponent<Renderer>()->setSize(100, 100);


    sf::Event event;
    sf::RenderWindow window(sf::VideoMode(SCREEN_X, SCREEN_Y), "game");
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    
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

        window.clear();
        window.draw(obj1.getComponent<Renderer>()->shape);
        window.display();
    }
        
}