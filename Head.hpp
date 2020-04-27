#ifndef HEAD
#define HEAD

#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <time.h>
#include <typeinfo>
#include <map>
#include <type_traits>
#include <SFML/Graphics.hpp>

const int SCREEN_Y = 720;
const int SCREEN_X = 1280;
const float g = 0.1;

std::string BTS(bool fl);

class GameObject;

class Component
{
    public:

        std::string name;
        GameObject* objPointer;

        virtual ~Component()
        {           
        }
        virtual std::string writeDown()
        {}
};

class Singleton;
class Renderer;
class Script;
class DataStorage;
class GrManager;
class SController;

class objShape;
class Collider;
class PhysController;
class BehaviourWhileCollided;
class BWCollided_player;
class BWCollided_wall;
class PhysicScript;

class Animation;
class AnimationConroller;


#endif



  




