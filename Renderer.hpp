#include <SFML/Graphics.hpp>

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

void Renderer::setSize(int xLen, int yLen)
{
    xSize = xLen;
    ySize = yLen;
    shape.setSize(sf::Vector2f(xSize, ySize));
}

void Renderer::updatePosition()
{
    shape.setPosition(objPointer->x - xSize / 2, objPointer->y - ySize / 2);
}

void Renderer::setTexture(sf::Texture* newTexture)
{
    shape.setTexture(newTexture);
}

void Renderer::loadTexture(std::string imagePath)
{
    if (!texture.loadFromFile(imagePath))
    {
        std::cout << "Loading texture erorr" << "\n";
        return;
    }

    texture.setSmooth(true);
    shape.setTexture(&texture);    
}

