#include <SFML/Graphics.hpp>

class Renderer: public Component
{ 
    public:

        bool isVisible = true;

        int x = 0;
        int y = 0;

        int xSize = 50;
        int ySize = 50;

        sf::RectangleShape shape;
        sf::Texture texture;

        void setSize(int xLen, int yLen);
        void setPosition(int newX, int newY);
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

void Renderer::setPosition(int newX, int newY)
{
    x = newX;
    y = newY;
    shape.setPosition(x, y);
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

