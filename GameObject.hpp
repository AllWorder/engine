#include <typeinfo>

class GameObject;

class Component
{
    public:

        std::string name;
        GameObject* objPointer;

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
        void deleteComponent();

        template <typename T>
        T* getComponent();


        int x = 0;
        int y = 0;

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
        if(c -> name == typeid(T).name())
        {
            std::cout << "This component is already adeed" << '\n';
            return false;
        }
    }
    T* comp = new T;
    comp->objPointer = this; // pointer to self-object
    components.push_back(comp);

    return true;
}

template <typename T>
void GameObject::deleteComponent()
{
  for(Component* c: components)
    if(c -> name == typeid(T).name())
    {
      delete c;
      return;
    }  
}

template <typename T>
T* GameObject::getComponent()
{
    for(Component* c: components)
        if(c -> name == typeid(T).name())
            return static_cast<T*>(c);

    return NULL;
}
