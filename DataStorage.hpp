#include <map>
#include "GameObject.hpp"

class DataStorage
{
    public:

        bool addObject(GameObject& newObject);
        bool deleteObject(std::string name);
        GameObject* getObject(std::string name);
        std::vector<GameObject*> getAllObjects();

    

        std::map <std::string, GameObject> objects;

};

bool DataStorage::addObject(GameObject& newObject)
{
    std::string name = newObject.name;

    if (objects.find(name) == objects.end()) // check, that it doesn't exist in objects
    {
        objects[name] = newObject;
        return true;
    }

    else
    {
        std::cout << "This element is already in DataStorage" << '\n';
        return false;
    }

}

bool DataStorage::deleteObject(std::string name)
{
    if ((objects.find(name) != objects.end()))
    {    
        objects.erase( objects.find(name) );
        return true;
    }
    else
        return false;

}

GameObject* DataStorage::getObject(std::string name)
{
    if ((objects.find(name) != objects.end()))
    {    
        return &objects[name];
    }

    std::cout << "No such object" << '\n';
    return NULL;
    
}

std::vector<GameObject*> DataStorage::getAllObjects()
{
  std::vector<GameObject*> obj;
  std::map<std::string, GameObject>::iterator i;
  
  for (i = objects.begin(); i != objects.end(); std::advance(i, 1)) 
    obj.push_back(&(i -> second));
  
  return obj;
}









