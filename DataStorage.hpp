#ifndef DATA_STORAGE
#define DATA_STORAGE

#include "Head.hpp"

class DataStorage
{
    public:

        bool addObject(GameObject& newObject);

        bool deleteObject(std::string name);

        GameObject* getObject(std::string name);

        std::map<std::string, GameObject>* getAllObjects();

        bool createObjectInStorage(std::string name);
       
        void save(std::string name, Singleton* sing);
   
        void read(std::string name);

        DataStorage()
        {}

        std::map <std::string, GameObject> objects;

};

#endif





