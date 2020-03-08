#include <typeinfo>

class Component
{
    public:

        std::string name;

        virtual ~Component()
        {           
        }


    private:

};


class GameObject
{
    public:

        std::string name;

        template <typename T>
        bool addComponent();
        template <typename T>
        void deleteComponent(T);
        template <typename T>
        T* getComponent();

        ~GameObject()
        {
            for(Component* c: components)
                delete c;
        }


    private:

        std::vector<Component*> components;

};

template <typename T>
bool GameObject::addComponent()
{
    for(Component* c: components)
    {
        if(c->name == typeid(T).name())
        {
            std::cout << "This component is already adeed" << '\n';
            return false;
        }
    }
    T* obj = new T;
    //obj -> name = comp.name;
    components.push_back(obj);
    return true;
}

template <typename T>
T* GameObject::getComponent()
{
    for(Component* c: components)
        if(c->name == typeid(T).name())
            return static_cast<T*>(c);

    return nullptr;
}