#include <SFML/Graphics.hpp>
#include <typeinfo>
#include <map>
#include <type_traits>

const int SCREEN_Y = 720;
const int SCREEN_X = 1280;


class GameObject;

class Component
{
    public:

        std::string name;
        GameObject* objPointer;

        virtual ~Component()
        {           
        }
};

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

class Script : public Component
{
  public:
  virtual void execute()
  {}
  
};

class Monster : public Script
{
  public:
  void execute()
  {
	std::cout << "JL" << '\n'; 
  }
};

class SController
{
  public:

  void registerScript(Script* script);
  void unregisterScript(Script* script);
  void doAllScripts();
  
  std::vector<Script*> scripts;
};

class GrManager
{
  public:
    GrManager();
    ~GrManager();
    void registerRenderer(Renderer* renderer);
    void unregisterRenderer(Renderer* renderer);
    void drawAll();
    void clear();
  
    sf::RenderWindow* window;
    std::vector<Renderer*> render;
};

class GameObject
{
    public:

        std::string name;

        template <typename T>
        bool addComponent(GrManager* grManager, SController* sc);

        template <typename T>
        void deleteComponent(GrManager* grManager, SController* sc);

        template <typename T>
        T* getComponent();


        int x = 0;
        int y = 0;

        ~GameObject()
        {
            for(Component* c: components)
                delete c;
        }


    private:

        std::vector<Component*> components;

};

class DataStorage
{
    public:

        bool addObject(GameObject& newObject);

        bool deleteObject(std::string name);

        GameObject* getObject(std::string name);

        std::map<std::string, GameObject>* getAllObjects();

        bool createObjectInStorage(std::string name);

    

        std::map <std::string, GameObject> objects;

};
