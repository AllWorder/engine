#ifndef GAME_RUN
#define GAME_RUN



bool gameRun()
{
  sf::Event event;
  bool fl = sing -> grManager -> window -> isOpen();

  *(sing -> timer)++;
  //PHISICS: 
  sing -> physController -> resolveCollisions(sing -> physController -> findCollisions(), sing);
  sing -> physController -> doAllPhysics(sing);
  

  //EVENT HANDLER

  while ((sing -> grManager -> window) -> pollEvent(event))
    if (event.type == sf::Event::Closed) 
    {
      (sing -> grManager -> window) -> close();
      fl = false;
    }

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
  {
    (sing -> grManager -> window) -> close();
    fl = false;
  }
  //LOGICS:
        
  sing -> sc -> doAllScripts(sing);

  //GRAPHICS:

  sing -> grManager -> drawAll();
  sing -> animationConroller -> doAllAnimations(sing);
  return fl;
}

#endif


