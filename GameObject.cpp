#include "Head.hpp"
#include "GameObject.hpp"
#include "Renderer.hpp"
#include "ScriptController.hpp"
#include "GraphicManager.hpp"
#include "Singleton.h"
#include "Script.hpp"
#include "CustomScripts.hpp"

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

    if (typeid(T).name() == typeid(Renderer).name()) //DON'T FORGET TO ADD NEW COMP AS 'class NewComp;' IN .hpp
    {
      sing -> grManager -> registerRenderer(comp);
      return true;
    }
    
  if ( (std::is_base_of<Script, T>::value) == 1 )
  {  	
    sing -> sc -> registerScript(comp);
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