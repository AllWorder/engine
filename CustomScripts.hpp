void PlayerController::execute()
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