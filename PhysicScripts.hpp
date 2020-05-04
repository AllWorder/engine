#ifndef PHYSSCRIPTS
#define PHYSSCRIPTS

#include "Head.hpp"
#include "PhysController.hpp"


class VelocityPhysic: public PhysicScript
{
    public:

        bool isHasInertion = true;

        VelocityPhysic()
        {
            this->name = typeid(VelocityPhysic).name();
        }

        std::string writeDown()
        {
          std::string s = "***";
          s += this -> name;
          s += '\n';
          s += BTS(isHasInertion);
          s += '\n';
          return s;
        }

        

        void executePhysic(Singleton* sing)
        {
            if(objPointer ->getComponent<Collider>())
            {
                objPointer -> x += objPointer -> getComponent<Collider>() -> shape.velocityS[0];
                objPointer -> y += objPointer -> getComponent<Collider>() -> shape.velocityS[1];
                
                if(isHasInertion)
                {
                    objPointer -> getComponent<Collider>() -> shape.velocityS[0] *= 0.97;
                    objPointer -> getComponent<Collider>() -> shape.velocityS[1] *= 0.97;
                }

            }
        }

};

class GravitationPhysic: public PhysicScript
{
    public:

        GravitationPhysic()
        {
            this->name = typeid(GravitationPhysic).name();
        }

        std::string writeDown()
        {
          std::string s = "***";
          s += this -> name;
          s += '\n';
          return s;
        }

        

        void executePhysic(Singleton* sing)
        {
            if(objPointer ->getComponent<Collider>())
            {
                objPointer -> getComponent<Collider>() -> shape.velocityS[1] += g;
            }
        }
};




#endif
