#ifndef COLLIDER
#define COLLIDER

#include "Head.hpp"
#include "Script.hpp"

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

  void setVelocity(float vx, float vy) //
  {
    std::vector<float> v;
    v.push_back(vx);
    v.push_back(vy);
    velocityS = v;
  }
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

class Collider : public Component
{
  public:
  ObjShape shape;
  bool checkCollision(Collider* obj2);
  bool checkDiverge(Collider* obj2); 
  void resolveCollision(Collider* obj2, Singleton* sing);
  
  Collider()
  {
    this -> name = typeid(Collider).name();
  }
};

#endif