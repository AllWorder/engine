#include "PhysController.hpp"

#include "GameObject.hpp"
#include "math.h"
#include "Renderer.hpp"
#include "ScriptController.hpp"
#include "GraphicManager.hpp"
#include "Singleton.h"
#include "Script.hpp"
#include "Collider.hpp"

void PhysController::registerCollider(Component* collider)
{
  colliders.push_back(static_cast<Collider*>(collider));
}

void PhysController::unregisterCollider(Component* collider)
{
  std::vector<Collider*>::iterator i;
  i = colliders.begin();
  for (Collider* c: colliders)
    if (c != static_cast<Collider*>(collider))//?
      i++;
  colliders.erase(i);
}

std::vector<Collider*> PhysController::findCollisions()
{
  std::vector<Collider*> collided;
  
  fflush(0);

  for (Collider* c: colliders)
    for (Collider* d: colliders)
    {
      if (((c) -> checkCollision(d)) and (c != d))
      {
        collided.push_back(c);
        collided.push_back(d);
      }
    }

  fflush(0);
  return collided;
}

void PhysController::resolveCollisions(std::vector<Collider*> collided, Singleton* sing)
{
  for (int i = 0; i < collided.size(); i += 2 )
  {
    collided[i] -> resolveCollision(collided[i + 1], sing); 
    
  }
}

//////////////
//physScripts:

void PhysController::registerPhysicScript(Component* physic)
{
  physicScripts.push_back(static_cast<PhysicScript*>(physic));
}

void PhysController::unregisterPhysicScript(Component* physic)
{
  std::vector<PhysicScript*>::iterator i;
  i = physicScripts.begin();
  for (PhysicScript* c: physicScripts)
    if (c != static_cast<PhysicScript*>(physic))//?
      i++;
  physicScripts.erase(i);
}

void PhysController::doAllPhysics(Singleton* sing)
{
  for (PhysicScript* c: physicScripts)
    c -> executePhysic(sing);
}