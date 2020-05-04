#include "Head.hpp"
#include "GameObject.hpp"
#include "Renderer.hpp"
#include "ScriptController.hpp"
#include "GraphicManager.hpp"
#include "Singleton.h"
#include "Script.hpp"
#include "CustomScripts.hpp"
#include "DataStorage.hpp"

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

void initRenderer(std::string object, Singleton* sing, std::string component)
{
  sing -> data -> getObject(object) -> addComponent<Renderer>(sing);

  if (component.substr(0, component.find('\n')) == "true")
    sing -> data -> getObject(object) -> getComponent<Renderer>() -> isVisible = true;
  else
    sing -> data -> getObject(object) -> getComponent<Renderer>() -> isVisible = false;
  component = component.substr(component.find('\n') + 1);

  sing -> data -> getObject(object) -> getComponent<Renderer>() -> layer = std::atoi(component.substr(0, component.find('\n')).c_str());
  component = component.substr(component.find('\n') + 1);

  int xSize = std::atoi(component.substr(0, component.find('\n')).c_str());
  component = component.substr(component.find('\n') + 1);
  
  int ySize = std::atoi(component.substr(0, component.find('\n')).c_str());
  component = component.substr(component.find('\n') + 1);

  sing -> data -> getObject(object) -> getComponent<Renderer>() -> loadTexture(component.substr(0, component.find('\n')));
  sing -> data -> getObject(object) -> getComponent<Renderer>() -> setSize(xSize, ySize);
  component = component.substr(component.find('\n') + 1);
  
}





