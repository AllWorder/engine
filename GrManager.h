
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

void GrManager::registerRenderer(Renderer* renderer)
{
  render.push_back(renderer);
}

void GrManager::unregisterRenderer(Renderer* renderer)
{
  std::vector<Renderer*>::iterator i;
  i = render.begin();
  for (Renderer* c: render)
    if (c != renderer)
      i++;
  render.erase(i);
}

void GrManager::drawAll()
{ 
  window -> clear();
  
  for(Renderer* c: render)
  {
    c -> updatePosition();
    window -> draw(c -> shape);
  }

  window -> display(); 
} 

