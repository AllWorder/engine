#ifndef COLLIDER
#define COLLIDER

#include "Head.hpp"
#include "Script.hpp"

class ObjShape
{
  public:
  bool ifMoveable = true;
  bool ifCollideable = true;
  bool ifElastic = true;
  bool ifCircle = false;
  float mass = 10;
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

class Collider : public Component
{
  public:
  ObjShape shape;
  bool checkCollision(Collider* obj2);
  bool checkDiverge(Collider* obj2); 
  void resolveCollision(Collider* obj2, Singleton* sing);
  void elasticHit(Collider* source, Collider* obj2);
  void inelasticHit(Collider* source, Collider* obj2);
  bool checkCrossingBetweenPreviousTics(Collider* source, Collider* obj2);
  std::string writeDown();  

  Collider()
  {
    this -> name = typeid(Collider).name();
  }
};

class BehaviourWhileCollided : public Script
{
  public:
  
  virtual void collisionResolving(Collider* source, Collider* enemy)
  {}
};

class BWCollided_player : public BehaviourWhileCollided
{
  public:

  BWCollided_player()
  {
    this -> name = typeid(BWCollided_player).name();
  }
  void collisionResolving(Collider* source, Collider* enemy);

};

class BWCollided_wall : public BehaviourWhileCollided
{
  public:

  BWCollided_wall()
  {
    this -> name = typeid(BWCollided_wall).name();
  }

  void collisionResolving(Collider* source, Collider* enemy);
};

void initCollider(std::string object, Singleton* sing, std::string component);

//user writes what happens when one object hits another, using our functions

#endif
