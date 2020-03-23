#ifndef GRAPHIC_MANAGER
#define GRAPHIC_MANAGER

#include "Head.hpp"
#include "Renderer.hpp"


class GrManager
{
  public:
    GrManager();
    ~GrManager();
    void registerRenderer(Component* renderer);
    void unregisterRenderer(Component* renderer);
    void drawAll();
    void clear();
  
    sf::RenderWindow* window;
    std::vector<Renderer*> render;
};

#endif