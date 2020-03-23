#ifndef RENDERER
#define RENDERER

#include "Head.hpp"
#include "GameObject.hpp"

class Renderer: public Component
{ 
    public:

        bool isVisible = true;

        int xSize = 50;
        int ySize = 50;

        sf::RectangleShape shape;
        sf::Texture texture;

        void setSize(int xLen, int yLen);
        void updatePosition();
        void setTexture(sf::Texture* newTexture);
        void loadTexture(std::string imagePath); // loads and automathicaly set it

        Renderer()
        {
            this->name = typeid(Renderer).name();
        }

    private:

};

#endif