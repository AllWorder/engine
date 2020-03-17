
void PlayerController::execute(DataStorage* data)
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

void MonsterSpawner::execute(DataStorage* data)
{
    int monsterID = rand() % 10;
    std::string monsterName = "monster";
    monsterName.append(std::to_string(monsterID)); //giving monster unique name
    std::cout << monsterName << '\n';

    data->createObjectInStorage(monsterName);
    //data->getObject(monsterName) -> addComponent<Renderer>(); // REQUIRES STUPID LINKS!!!!!! WHO OWN THEM?
    //data->getObject(monsterName) -> getComponent<Renderer>()->loadTexture("monster/opexus.png");
    //data->getObject(monsterName) -> getComponent<Renderer>()->setSize(100, 200);

    data->getObject(monsterName)-> x = rand() % 100;
    data->getObject(monsterName)-> y = rand() % 100;

}