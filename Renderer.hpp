#ifndef RENDERER
#define RENDERER

#include "Head.hpp"

class Renderer: public Component
{ 
    public:

        bool isVisible = true;
        int layer = 1;

        int xSize = 50;
        int ySize = 50;
        std::string path;
        sf::RectangleShape shape;
        sf::Texture texture;

        void setSize(int xLen, int yLen);
        void updatePosition();
        void setTexture(sf::Texture* newTexture);
        void loadTexture(std::string imagePath); // loads and automathicaly set it
        std::string writeDown();
        Renderer();
    
    private:

};

void initRenderer(std::string object, Singleton* sing, std::string component);
#endif
