#include "DataStorage.hpp"

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

std::map<std::string, GameObject>* DataStorage::getAllObjects()
{
  return &(this -> objects);
}

bool DataStorage::createObjectInStorage(std::string name)
{

    if (objects.find(name) == objects.end()) // check, that it doesn't exist in objects
    {
        //GameObject* newObject = new GameObject;
        GameObject newObject;
        //newObject->name = name;
        objects[name] = newObject;      //do dot need dynamic memory as a new element is created in the map
        objects[name].name = name;
        return true;
    }

    else
    {
        std::cout << "This element is already in DataStorage" << '\n';
        return false;
    }

}