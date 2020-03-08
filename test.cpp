#include <iostream>
#include <vector>
#include "DataStorage.hpp"

class TestComponent: public Component
{
    public:

    TestComponent()
    {
        this->name = typeid(TestComponent).name();
    }

};

main()
{
    
    DataStorage data;
    GameObject obj1;
    obj1.name = "obj1";
    GameObject obj2;
    obj2.name = "obj2";

    if(data.addObject(obj1))
        std::cout << "Added" << '\n';
    if(data.addObject(obj1))
        std::cout << "Added" << '\n'; // Must write, that this element is already aexist in data
    
    data.getObject("obj1")->name = "Jenya loh";
    std::cout << data.getObject("obj1")->name << '\n';
    

    std::cout << "#######" << '\n';

    TestComponent comp1;
    comp1.name = typeid(TestComponent).name();

    if(obj1.addComponent<TestComponent>())
        std::cout << "Added" << '\n';
    if(obj1.addComponent<TestComponent>())
        std::cout << "Added" << '\n'; // Must write, that this element is already aexist in data


    TestComponent* comp2 = obj1.getComponent<TestComponent>();
    std::cout << "over" << std::endl;
    std::cout << comp2 -> name;
}