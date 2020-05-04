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
        std::string writeDown();

        std::vector<sf::Texture*> textures;
        std::vector<std::string> texturePaths;
        Animation()
        {
            this -> name = typeid(Animation).name();
        }


};

class AnimationConroller
{
    public:
        
        AnimationConroller()
        {}
        void registerAnimation(Component* animation);
        void unregisterAnimation(Component* animation);
        void deleteData();
        void doAllAnimations(Singleton* sing);

        std::vector<Animation*> animations;

};

void initAnimation(std::string object, Singleton* sing, std::string component);
#endif
