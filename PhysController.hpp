#ifndef PHYSCONTROLLER
#define PHYSCONTROLLER

#include "Head.hpp"

class PhysController
{
  public:
  void registerCollider(Component* collider);
  void unregisterCollider(Component* collider);
  std::vector<Collider*> findCollisions();
  void resolveCollisions(std::vector<Collider*> collided, Singleton* sing);

  std::vector<Collider*> colliders;
};

#endif 