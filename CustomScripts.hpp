
void PlayerController::execute(Singleton* sing)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        objPointer->y -= 5;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        objPointer->y += 5;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        objPointer->x -= 5;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        objPointer->x += 5;
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
