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
  
  //std::cout << "size of collided " << collided.size() << std::endl;
  fflush(0);
  /*std::vector<Collider*>::iterator i; 
  std::vector<Collider*>::iterator j;
 
  for (i = colliders.begin(); i < colliders.end(); i++)
    for (j = i++; j < colliders.end(); j++)
  */
  for (Collider* c: colliders)
    for (Collider* d: colliders)
    {
      if ((c) -> checkCollision(d) )
      {
        collided.push_back(c);
        collided.push_back(d);
      }
    }
  if (collided.size() == 4)
    std::cout << "size of collided " << collided.size() << std::endl;
  fflush(0);
  return collided;
}

void PhysController::resolveCollisions(std::vector<Collider*> collided, Singleton* sing)
{
  std::vector<Collider*>::iterator j;
  
  for (j = collided.begin(); j < collided.end(); std::advance(j, 2))
  {
    (*j) -> resolveCollision(*(j++), sing); 
    //std::cout << "collision resolve " << '\n';
    //(*(j++)) -> resolveCollision(*j, sing);
  }
}












