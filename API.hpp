#ifndef API_
#define API_
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
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
      sing -> data -> save(name, sing);
    }
  
    void readGame(std::string name)
    {
      sing -> animationConroller -> animations = {};
      sing -> grManager -> render = {};
      sing -> physController -> colliders = {};
      sing -> physController -> physicScripts = {};
      sing -> sc -> scripts = {};
   
      std::map <std::string, GameObject>::iterator i;
      
      while (sing -> data -> objects.size() != 0)
      {
        i = sing -> data -> objects.begin();
        
        sing -> data -> deleteObject(i -> first);
      }

      std::string data = "Savings/";
      data += name;
      data += ".txt";
      std::fstream f;
      f.open(data.c_str());
      std::getline(f, data, '\0');
     
      
      std::string object;
      std::string objName;
      std::string componentName;
      *(sing -> timer) = std::atoi(data.substr(0, data.find('\n')).c_str());
      data = data.substr(data.find('\n') + 1);
      while (data.size() > 3)
      {
        if (data.substr(0, 3) == "###")
        {
          objName = data.substr(3, data.find('\n') - 3);
          sing -> data -> createObjectInStorage(objName);
          data = data.substr(data.find('\n') + 1);
          sing -> data -> getObject(objName) -> x = std::stof(data.substr(0, data.find('\n')));
          data = data.substr(data.find('\n') + 1);
          sing -> data -> getObject(objName) -> y = std::stof(data.substr(0, data.find('\n')));
          data = data.substr(data.find('\n') + 1);
        }
        if (data.substr(0, 3) == "@@@")
        {
          componentName = data.substr(3, data.find('\n') - 3);
          initScript(componentName, objName, sing -> data, sing);
          data = data.substr(data.find("...") + 4);
        }
        if (data.substr(0, 3) == "***")
        {
          componentName = data.substr(3, data.find('\n') - 3);
          data = data.substr(data.find('\n') + 1);
          object = data.substr(0, data.find("...") + 4);

          if (componentName == "Renderer")
            initRenderer(objName, sing, object);
          if (componentName == "Animation")
            initAnimation(objName, sing, object);
          if (componentName == "Collider")
            initCollider(objName, sing, object);
          if (componentName == typeid(GravitationPhysic).name())
            initGravitationPhysic(objName, sing, object);
          if (componentName == typeid(VelocityPhysic).name())
            initVelocityPhysic(objName, sing, object);

          data = data.substr(data.find("...") + 4);
        }
      }
      f.close();
    }

}






#endif
