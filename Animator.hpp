#ifndef ANIMATOR
#define ANIMATOR

#include "Head.hpp"

class Animation: public Component
{
    public:

        int ticksPerAnimation = 30;
        int currentTick = 0;
        int currentTexture = 0;

        void addTexture(std::string texturePath);
        void deleteTexture(int textureNum);

        std::vector<sf::Texture*> textures;

        Animation()
        {
            this -> name = typeid(Animation).name();
        }


};

class AnimationConroller
{
    public:

        void registerAnimation(Component* animation);
        void unregisterAnimation(Component* animation);
        
        void doAllAnimations(Singleton* sing);

        std::vector<Animation*> animations;

};

#endif