
void PlayerController::execute(Singleton* sing)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        objPointer -> getComponent<Collider>() -> shape.velocityS[1] -= 0.05;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        objPointer -> getComponent<Collider>() -> shape.velocityS[1] += 0.05;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        objPointer -> getComponent<Collider>() -> shape.velocityS[0] -= 0.05;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        objPointer -> getComponent<Collider>() -> shape.velocityS[0] += 0.05;

  objPointer -> x += objPointer -> getComponent<Collider>() -> shape.velocityS[0];
  objPointer -> y += objPointer -> getComponent<Collider>() -> shape.velocityS[1];
}

void MonsterSpawner::execute(Singleton* sing)
{
  if (*(sing -> timer) % 10 == 0)
  {
    int monsterID = *(sing -> timer);
    std::string monsterName = "monster";
    monsterName.append(std::to_string(monsterID)); //giving monster unique name. HaHaha, not unique, it turned out
    std::cout << monsterName << '\n';

    sing -> data -> createObjectInStorage(monsterName);
    sing -> data -> getObject(monsterName) -> addComponent<Renderer>(sing); // REQUIRES STUPID LINKS!!!!!! WHO OWN THEM?
    sing -> data -> getObject(monsterName) -> getComponent<Renderer>()->loadTexture("resources/monster.png");
    sing -> data -> getObject(monsterName) -> getComponent<Renderer>()->setSize(100, 200);

    sing -> data -> getObject(monsterName)-> x = rand() % 1100;
    sing -> data -> getObject(monsterName)-> y = rand() % 600;
  }
}

void BehaviourWhileCollided::collisionResolving(Collider* source, Collider* enemy)
{
  if (source -> objPointer -> name != "obj1")
    return;
  //std::cout << "Function called for player" << std::endl;

  fflush(0);
  if (enemy -> objPointer -> name == "wall1")
    source -> shape.velocityS[0] = - source -> shape.velocityS[0];
  if (enemy -> objPointer -> name == "wall2")
    source -> shape.velocityS[1] = - source -> shape.velocityS[1];
  if (enemy -> objPointer -> name == "wall3")
    source -> shape.velocityS[0] = - source -> shape.velocityS[0];
  if (enemy -> objPointer -> name == "wall4")
    source -> shape.velocityS[1] = - source -> shape.velocityS[1];
}









