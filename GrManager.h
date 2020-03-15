
class GrManager
{
  public:
    void drawAll(sf::RenderWindow* pointer, DataStorage* data);
    void clear();
    //~GrManager();
};

void GrManager::drawAll(sf::RenderWindow* pointer, DataStorage* data)
{ 
  pointer -> clear();

  std::map <std::string, GameObject> :: iterator i;
  for (i = (data -> objects).begin(); i != (data -> objects).end(); std::advance(i, 1))
  {
    if (i -> second.getComponent<Renderer>() != NULL)
    {
      i -> second.getComponent<Renderer>()->updatePosition(); // updates real object's coords to graph coords
      pointer -> draw(i -> second.getComponent<Renderer>()->shape); // где проверка на isVisible?
    }
  }

  pointer -> display(); 
} 

