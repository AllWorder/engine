#ifndef API_
#define API_

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
    void setSquareVertexes(std::string name, int xSize, int ySize);
    std::vector<Collider*> getAllCollisions();
    void saveGame(std::string name);

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

    void setSquareVertexes(std::string name, int xSize, int ySize)
    {
        if(GameObject* obj = API::getObject(name))
        {
            if(obj -> getComponent<Collider>())
            {
                API::getObject(name) -> getComponent<Collider>() -> shape.addVertex(-xSize / 2, -ySize / 2);
                API::getObject(name) -> getComponent<Collider>() -> shape.addVertex(xSize / 2, -ySize / 2);
                API::getObject(name) -> getComponent<Collider>() -> shape.addVertex(xSize / 2, ySize / 2);
                API::getObject(name) -> getComponent<Collider>() -> shape.addVertex(-xSize / 2, ySize / 2);
            }
            else
            {
                std::cout << "GameObject " << name << " must have a collider" << '\n';
            }
            
        }
    }

    std::vector<Collider*> getAllCollisions()
    {
      return sing -> physController -> findCollisions();
    }

    void saveGame(std::string name)
    {
      sing -> data -> save(name);
    }

}

#endif
