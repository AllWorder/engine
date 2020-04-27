#include "DataStorage.hpp"
#include "GameObject.hpp"
#include <iostream>
#include <fstream>
#include <string>

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
        GameObject newObject;
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

void DataStorage::save(std::string name)
{
  name = "Savings/" + name + ".txt";
  std::ofstream write;
  write.open(name.c_str());
  std::map <std::string, GameObject>::iterator i;
  std::string dataLine;
  for (i = objects.begin(); i != objects.end(); i++)
  {
    write << "###" << i -> first << '\n';
    write << (i -> second).x << '\n';
    write << (i -> second).y << '\n';
    for (Component* c: (i -> second).components)
    {  
      dataLine = c -> writeDown();
      write << dataLine;
      fflush(0);
    }
  }
  write.close();
}

std::string BTS(bool fl)
{
  std::string s = "false";
  if (fl == true)
    s = "true";
  return s;
}








