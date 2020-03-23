#ifndef DATA_STORAGE
#define DATA_STORAGE

#include "Head.hpp"
#include "GameObject.hpp"

class DataStorage
{
    public:

        bool addObject(GameObject& newObject);

        bool deleteObject(std::string name);

        GameObject* getObject(std::string name);

        std::map<std::string, GameObject>* getAllObjects();

        bool createObjectInStorage(std::string name);

    

        std::map <std::string, GameObject> objects;

};

#endif





