#ifndef GAME_OBJECT
#define GAME_OBJECT

#include "Head.hpp"
#include "Renderer.hpp"
#include "ScriptController.hpp"
#include "GraphicManager.hpp"
#include "Singleton.h"
#include "Script.hpp"
#include "PhysController.hpp"
#include "Collider.hpp"
#include "Animator.hpp"

class GameObject
{
    public:

        std::string name;

        template <typename T>
        bool addComponent(Singleton* sing);

        template <typename T>
        void deleteComponent(Singleton* sing);

        template <typename T>
        T* getComponent();

        


        float x = 0;
        float y = 0;

        ~GameObject()
        {
            for(Component* c: components)
                delete c;
        }


    public:

        std::vector<Component*> components;

};

template <typename T>
bool GameObject::addComponent(Singleton* sing)
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

    if (typeid(T).name() == typeid(Renderer).name())
    {
      sing -> grManager -> registerRenderer(comp);
      return true;
    }
    
  if ( (std::is_base_of<Script, T>::value) == 1 )
  {  	
    sing -> sc -> registerScript(comp);
    return true;
  }

  if (typeid(T).name() == typeid(Collider).name())
  {
    sing -> physController -> registerCollider(comp);
    return true;
  }

  if (typeid(T).name() == typeid(Animation).name())
  {
    sing -> animationConroller -> registerAnimation(comp);
    return true;
  }		

  if ( (std::is_base_of<PhysicScript, T>::value) == 1 )
  {  	
    sing -> physController -> registerPhysicScript(comp);
    return true;
  }       
}

template <typename T>
void GameObject::deleteComponent(Singleton* sing)
{
  for(Component* c: components)
    if(c -> name == typeid(T).name())
    {
      Component* comp = c;
      if (typeid(T).name() == typeid(Renderer).name())
        sing -> grManager -> unregisterRenderer(comp);

      if ( std::is_base_of<Script, T>::value )
        sing -> sc -> unregisterScript(comp);
      
      if ( std::is_base_of<PhysicScript, T>::value )
        sing -> physController -> unregisterPhysicScript(comp);

      if (typeid(T).name() == typeid(Collider).name())
        sing -> physController -> unregisterCollider(comp);

      if (typeid(T).name() == typeid(Animation).name())
        sing -> animationConroller -> unregisterAnimation(comp);

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



#endif
