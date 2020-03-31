#ifndef GRAPHIC_MANAGER
#define GRAPHIC_MANAGER

#include "Head.hpp"

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
    int maxLayer = 10;
    std::vector<Renderer*> render;
};

#endif
