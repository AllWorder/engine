#include "GraphicManager.hpp"
#include "Renderer.hpp"

GrManager::GrManager()
{
  sf::RenderWindow* windows = new sf::RenderWindow;
  windows -> create(sf::VideoMode(SCREEN_X, SCREEN_Y), "game");
  windows -> setVerticalSyncEnabled(true);
  windows -> setFramerateLimit(60);
  window = windows;
}

GrManager::~GrManager()
{
  delete window;
}

void GrManager::registerRenderer(Component* renderer)
{
  render.push_back(static_cast<Renderer*>(renderer));
}

void GrManager::unregisterRenderer(Component* renderer)
{
  std::vector<Renderer*>::iterator i;
  i = render.begin();
  for (Renderer* c: render)
    if (c != static_cast<Renderer*>(renderer))//?
      i++;
  render.erase(i);
}

void GrManager::drawAll()
{ 
  window -> clear();
  
  for (int i = 0; i < render.size(); i++)
    for (int j = maxLayer; j >= 1; j--)
      if (render[i] -> layer == j) 
      {
        render[i] -> updatePosition();
        if (render[i] -> isVisible == true)
          window -> draw(render[i] -> shape);
      }

  window -> display(); 
} 





