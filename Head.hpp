#include <SFML/Graphics.hpp>
#include <typeinfo>
#include <map>
#include <type_traits>
#include "math.h"

const int SCREEN_Y = 720;
const int SCREEN_X = 1280;


class GameObject;
class SController;
class Collider;
class PhysController;

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
  PhysController* physController;
  int* timer;
  static Singleton* getInstance();
  static void deleteInstance();
};

class Script : public Component
{
  public:
  virtual void execute(Singleton* sing)
  {}
  virtual void collisionResolving(Collider* me, Collider* enemy)
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


        float x = 0;
        float y = 0;

        ~GameObject()
        {
            for(Component* c: components)
                delete c;
        }


    private:

        std::vector<Component*> components;

};

class ObjShape
{
  public:
  bool ifMoveable = true;
  bool ifCircle = false;
  float mass = 1;
  float r = 1;
  std::vector<float> velocityS = {0, 0};
  std::vector<std::vector <float>> vertex;
  
  void addVertex(float x, float y)
  {
    std::vector<float> oneVertex;
    oneVertex.push_back(x);
    oneVertex.push_back(y);
    vertex.push_back(oneVertex);
  }

  void SetVelocity(float vx, float vy)
  {
    std::vector<float> v;
    v.push_back(vx);
    v.push_back(vy);
    velocityS = v;
  }
};


class Collider : public Component
{
  public:
  ObjShape shape;
  bool checkCollision(Collider* obj2); 
  void resolveCollision(Collider* obj2, Singleton* sing);
  
  Collider()
  {
    this -> name = typeid(Collider).name();
  }
};

class PhysController
{
  public:
  void registerCollider(Component* collider);
  void unregisterCollider(Component* collider);
  std::vector<Collider*> findCollisions();
  void resolveCollisions(std::vector<Collider*> collided, Singleton* sing);

  std::vector<Collider*> colliders;
};

class BehaviourWhileCollided : public Script
{
  public:
  BehaviourWhileCollided()
  {
    this -> name = typeid(BehaviourWhileCollided).name();
  }

  void collisionResolving(Collider* me, Collider* enemy);
};
















