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

class GameObject;

class Component
{
    public:

        std::string name;
        GameObject* objPointer;

        virtual ~Component()
        {           
        }
};


#endif



  




