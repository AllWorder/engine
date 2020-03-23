#ifndef GAME_OBJECT
#define GAME_OBJECT

#include "Head.hpp"
#include "Singleton.h"


#include "GraphicManager.hpp"
#include "ScriptController.hpp"
#include "Renderer.hpp"

class GameObject
{
    public:

        std::string name;

        template <typename T>
        bool addComponent(Singleton* sing);

        template <typename T>
        void deleteComponent(Singleton* sing);

        template <typename T>
        T* getComponent();


        int x = 0;
        int y = 0;

        ~GameObject()
        {
            for(Component* c: components)
                delete c;
        }


    private:

        std::vector<Component*> components;

};


#endif