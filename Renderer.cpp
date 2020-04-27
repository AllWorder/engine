#include "Head.hpp"
#include "GameObject.hpp"
#include "Renderer.hpp"
#include "ScriptController.hpp"
#include "GraphicManager.hpp"
#include "Singleton.h"
#include "Script.hpp"
#include "CustomScripts.hpp"

Renderer::Renderer()
{
    this->name = typeid(Renderer).name();
}

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
        std::cout << "Loading texture erorr" << '\n';
        return;
    }
    path = imagePath;
    texture.setSmooth(true);
    shape.setTexture(&texture);    
}

std::string Renderer::writeDown()
{
  std::string s = "***Renderer";
  s += '\n';
  s += BTS(isVisible);
  s += '\n';
  s += std::to_string(layer);
  s += '\n';
  s += std::to_string(xSize);
  s += '\n';
  s += std::to_string(ySize);
  s += '\n';
  s += path;
  s += '\n';
  return s;
}


