#include <SFML/Graphics.hpp>
#include <typeinfo>
#include <map>
#include <type_traits>

const int SCREEN_Y = 720;
const int SCREEN_X = 1280;


class GameObject;
class SController;

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


class Singleton 
{
  private:
  static Singleton* instance;
  Singleton(){};
  Singleton (const Singleton&) {};
  Singleton& operator= (Singleton&) {};
  public:
  GrManager* grManager;
  SController* sc;
  DataStorage* data;
  int* timer;
  static Singleton* getInstance();
  static void deleteInstance();
};

class Script : public Component
{
  public:
  virtual void execute(Singleton* sing)
  {}
  
};

class SController
{
  public:

  void registerScript(Component* script);
  void unregisterScript(Component* script);
  void doAllScripts(Singleton* sing);
  
  std::vector<Script*> scripts;
};

class PlayerController: public Script
{
  public:

  PlayerController()
  {
    this->name = typeid(PlayerController).name();
  }

  void execute(Singleton* sing);

};

class MonsterSpawner: public Script
{
  public:

  MonsterSpawner()
  {
    this->name = typeid(MonsterSpawner).name();
  }

  void execute(Singleton* sing);

};

class Monster : public Script
{
  public:

  Monster()
  {
    this->name = typeid(Monster).name();
  }

  void execute(Singleton* sing)
  {
  }
};


class GameObject
{
    public:

        std::string name;

        template <typename T>
        bool addComponent(Singleton* sing);

        template <typename T>
        void deleteComponent(Singleton* sing);

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


  




