#ifndef PHYSCONTROLLER
#define PHYSCONTROLLER

#include "Head.hpp"

class PhysicScript: public Component
{
    public:

      virtual void executePhysic(Singleton* sing)
      {}

};

class PhysController
{
  public:

    // collisions:
    
    void registerCollider(Component* collider);
    void unregisterCollider(Component* collider);
    std::vector<Collider*> findCollisions();
    void resolveCollisions(std::vector<Collider*> collided, Singleton* sing);

    std::vector<Collider*> colliders;

    // physScripts:

    void registerPhysicScript(Component* physic);
    void unregisterPhysicScript(Component* physic);
    void doAllPhysics(Singleton* sing);

    std::vector<PhysicScript*> physicScripts;

};

#endif 