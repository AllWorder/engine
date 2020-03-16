

template <typename T>
bool GameObject::addComponent(GrManager* grManager, SController* sc)
{
	std::cout << typeid(T).name() << '\n'; //?
 
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
    
    if ( (std::is_base_of<Script, T>::value) )
    {  	
		std::cout << "I am not renderer " << typeid(T).name() << '\n';		
		sc -> registerScript(comp);
		return true;
	}	    

    if (typeid(T).name() == typeid(Renderer).name())
    {
      grManager -> registerRenderer(comp );
      return true;
    }
    
}

template <typename T>
void GameObject::deleteComponent(GrManager* grManager, SController* sc)
{
  for(Component* c: components)
    if(c -> name == typeid(T).name())
    {
      T* comp = c;
      if (typeid(T).name() == typeid(Renderer).name())
        grManager -> unregisterRenderer(comp);

      if ( std::is_base_of<Script, T>::value )
        sc -> unregisterScript(comp);

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
