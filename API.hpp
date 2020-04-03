#ifndef API
#define API

#include "Head.hpp"

#include "Script.hpp"
#include "CustomScripts.hpp"
#include "GameObject.hpp"
#include "Renderer.hpp"
#include "Singleton.h"
#include "GraphicManager.hpp"
#include "ScriptController.hpp"
#include "DataStorage.hpp"
#include "Collider.hpp"
#include "PhysController.hpp"
#include "PhysicScripts.hpp"



namespace API
{


    void createObject(std::string name);
    void deleteObject(std::string name);
    GameObject* getObject(std::string name);


    void createObject(std::string name)
    {
        sing -> data -> createObjectInStorage(name);
    }

    void deleteObject(std::string name)
    {
        sing -> data -> deleteObject(name);
    }

    GameObject* getObject(std::string name)
    {
        return sing -> data -> getObject(name);
    }

}

#endif