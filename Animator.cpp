#include "Animator.hpp"

#include "Head.hpp"
#include "GameObject.hpp"
#include "Renderer.hpp"

void Animation::addTexture(std::string texturePath)
{
        sf::Texture* newTexture  = new sf::Texture;
        
        if (!newTexture->loadFromFile(texturePath))
        {
            std::cout << "Loading texture erorr" << "\n";
            return;
        }
        texturePaths.push_back(texturePath);
        newTexture -> setSmooth(true);

        this->textures.push_back(newTexture);

}

void Animation::deleteTexture(int textureNum)
{ 
    textures.erase(textures.begin() + textureNum);
    texturePaths.erase(texturePaths.begin() + textureNum);
}     

void AnimationConroller::registerAnimation(Component* animation)
{
  animations.push_back(static_cast<Animation*>(animation));
}

void AnimationConroller::unregisterAnimation(Component* animation)
{
  std::vector<Animation*>::iterator i;
  i = animations.begin();
  for (Animation* c: animations)
    if (c != static_cast<Animation*>(animation))
      i++;
  animations.erase(i);
}

void AnimationConroller::doAllAnimations(Singleton* sing)
{
    for (Animation* c: animations)
    {
        if( c -> currentTick == c -> ticksPerAnimation) 
        {   
            if( c -> objPointer -> getComponent<Renderer>())
            {
                if(!c -> textures.empty())
                {
                    //c -> objPointer -> getComponent<Renderer>() -> setTexture(c -> textures[c->currentTexture]);
                    c -> objPointer -> getComponent<Renderer>() -> shape . setTexture(c -> textures[c->currentTexture]);

                    if( (c -> currentTexture) < (c -> textures.size() - 1) )
                        c -> currentTexture += 1;
                    else
                        c -> currentTexture = 0;
                    
                }
            }

            else
            {
                std::cout << c -> objPointer ->name << " must have renderer" << '\n';
            }
            
            c ->currentTick = 0;
        }

        else

          c -> currentTick += 1;  
        
    }
}

std::string Animation::writeDown()
{
  std::string s = "***Animation";
  s += '\n';
  s += std::to_string(ticksPerAnimation);
  s += '\n';
  s += std::to_string(currentTick);
  s += '\n';
  s += std::to_string(currentTexture);
  s += '\n';
  for (std::string path: texturePaths)
    s += path + '\n';
  return s;
}







