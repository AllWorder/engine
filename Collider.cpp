#include "Head.hpp"
#include "Collider.hpp"

#include "GameObject.hpp"
#include "math.h"
#include "Renderer.hpp"
#include "ScriptController.hpp"
#include "GraphicManager.hpp"
#include "Singleton.h"
#include "Script.hpp"


bool checkCrossing(std::vector<float> v11, std::vector<float> v12, std::vector<float> v21, std::vector<float> v22, std::vector<float> c1, std::vector<float> c2)
{
  v11[0] += c1[0];
  v11[1] += c1[1];
  v12[0] += c1[0];
  v12[1] += c1[1];
  v21[0] += c2[0];
  v21[1] += c2[1];
  v22[0] += c2[0];
  v22[1] += c2[1];

  bool flag1 = ((((v12[0]-v11[0])*(v21[1]-v11[1])-(v21[0]-v11[0])*(v12[1]-v11[1]))*((v12[0]-v11[0])*(v22[1]-v11[1])-(v12[1]-v11[1])*(v22[0]-v11[0]))) <= 0);
  bool flag2 = ((((v21[0]-v22[0])*(v11[1]-v22[1])-(v21[1]-v22[1])*(v11[0]-v22[0]))*((v21[0]-v22[0])*(v12[1]-v22[1])-(v21[1]-v22[1])*(v12[0]-v22[0]))) <= 0);
  if (flag1 and flag2)
    return true;
  return false;
}

bool Collider::checkCollision(Collider* obj2)
{
  if ((this -> shape.ifCircle == true) and (obj2 -> shape.ifCircle == true))
    if ((this -> shape.r + obj2 -> shape.r >= sqrt(pow(this -> objPointer -> x - obj2 -> objPointer -> x, 2) + pow(this -> objPointer -> y - obj2 -> objPointer -> y, 2))))
      return true;
    else
      return false;
  
  //if (((this -> shape.ifCircle == false) and (obj2 -> shape.ifCircle == true)) or ((this -> shape.ifCircle == true) and (obj2 -> shape.ifCircle == false)))
  {
    
   //WRITE  
  }
  
  if ((this -> shape.ifCircle == false) and (obj2 -> shape.ifCircle == false))
  {
    std::vector<std::vector<float>> v1 = this-> shape.vertex;
    int n1 = v1.size();
    v1.push_back(v1[0]);

    std::vector<std::vector<float>> v2 = obj2-> shape.vertex;
    int n2 = v2.size();
    v2.push_back(v2[0]);
    
    std::vector<float> c1 = {this -> objPointer -> x, this -> objPointer -> y};
    std::vector<float> c2 = {obj2 -> objPointer -> x, obj2 -> objPointer -> y};
    for (int i = 0; i < n1; i++)
      for (int j = 0; j < n2; j++)
        if (checkCrossing(v1[i], v1[i+1], v2[j], v2[j+1], c1, c2))
          return true;
    return false;
  }
}

bool Collider::checkDiverge(Collider* obj2)
{
  std::vector<float> V = {this -> shape.velocityS[0] - obj2 -> shape.velocityS[0], this -> shape.velocityS[1] - obj2 -> shape.velocityS[1]};
  
  std::vector<std::vector<float>> vert1 = this -> shape.vertex;
  vert1.push_back({0, 0});
  std::vector<std::vector<float>> vert2 = obj2 -> shape.vertex;
  vert2.push_back({0, 0});
  std::vector<float> c1 = {this -> objPointer -> x, this -> objPointer -> y};
  std::vector<float> c2 = {obj2 -> objPointer -> x, obj2 -> objPointer -> y};
  
  for (int i = 0; i < this -> shape.vertex.size() -1; i++)
    for (int j = 0; j < obj2 -> shape.vertex.size() -1; j++)
      if (checkCrossing(vert1[i], vert1[i+1], vert2[j], vert2[j+1], c1, c2))
      {
        std::vector<float> border = {-vert2[j+1][1] + vert2[j][1], vert2[j+1][0] - vert2[j][0]}; 
        if ((((border[0])*(-vert2[j][0])+(border[1])*(-vert2[j][1]))*((border[0])*(V[0])+(border[1])*(V[1]))) > 0) 
          return false;
      }
  return true;
}

void Collider::resolveCollision(Collider* obj2, Singleton* sing)
{
  if (this -> objPointer -> getComponent<BWCollided_player>())
    this -> objPointer -> getComponent<BWCollided_player>() -> collisionResolving(this, obj2);
  if (this -> objPointer -> getComponent<BWCollided_wall>())
    this -> objPointer -> getComponent<BWCollided_wall>() -> collisionResolving(this, obj2);
}

void Collider::elasticHit(Collider* source, Collider* obj2)
{
  if ((obj2 -> shape.ifMoveable == false) and (source -> shape.ifMoveable == false)) //do not collide two immoveable objects
    return;
  std::vector<float> V = {this -> shape.velocityS[0] - obj2 -> shape.velocityS[0], this -> shape.velocityS[1] - obj2 -> shape.velocityS[1]};
  
  std::vector<std::vector<float>> vert1 = this -> shape.vertex;
  std::vector<std::vector<float>> vert2 = obj2 -> shape.vertex;
  std::vector<float> c1 = {this -> objPointer -> x, this -> objPointer -> y};
  std::vector<float> c2 = {obj2 -> objPointer -> x, obj2 -> objPointer -> y};
  
  for (int i = 0; i < vert1.size()-1; i++)
    for (int j = 0; j < vert2.size()-1; j++)
      if (checkCrossing(vert1[i], vert1[i+1], vert2[j], vert2[j+1], c1, c2))
      {
        std::vector<float> norm = {-vert2[j+1][1] + vert2[j][1], vert2[j+1][0] - vert2[j][0]};
        if ((((norm[0])*(-vert2[j][0])+(norm[1])*(-vert2[j][1]))*((norm[0])*(V[0])+(norm[1])*(V[1]))) > 0) 
        {
          
        //std::vector<float> norm = {c2[0] - c1[0], c2[1]-c1[1]};
        float module = sqrt(pow(norm[0], 2) + pow(norm[1], 2));
        norm[0] = norm[0]/module;
        norm[1] = norm[1]/module;
        std::vector<float> tau = {-norm[1], norm[0]}; 
 
        float v1n = source -> shape.velocityS[0] * norm[0] + source -> shape.velocityS[1] * norm[1];
        float v2n = obj2 -> shape.velocityS[0] * norm[0] + obj2 -> shape.velocityS[1] * norm[1];     
        float v1t = source -> shape.velocityS[0] * tau[0] + source -> shape.velocityS[1] * tau[1];
        float v2t = obj2 -> shape.velocityS[0] * tau[0] + obj2 -> shape.velocityS[1] * tau[1];

        float k = source -> shape.mass / obj2 -> shape.mass;
        float a = k+1;
        float b = -2*v2n - 2*k*v1n;
        float c = (k-1)*v1n*v1n + 2*v1n*v2n;
        if ((obj2 -> shape.ifMoveable == false) and (source -> shape.ifMoveable == true))
        {
          source -> shape.velocityS[0] = (-v1n + 2*v2n) *norm[0] + v1t*tau[0];
          source -> shape.velocityS[1] = (-v1n + 2*v2n) *norm[1] + v1t*tau[1];
        }
        if ((obj2 -> shape.ifMoveable == true) and (source -> shape.ifMoveable == true))
        {
          //std::cout << "collision of player" << '\n';
          if (pow(b, 2) - 4*a*c < 0)
          {
            std::cout << "discriminant in elasticCollision < 0" << '\n';
            continue;
          }
          float v1n_ = (-b - sqrt(pow(b, 2) - 4*a*c))/(2*a);
          float v2n_ = k*(v1n - v1n_) + v2n;
          source -> shape.velocityS[0] = v1n_*norm[0] + v1t*tau[0];
          source -> shape.velocityS[1] = v1n_*norm[1] + v1t*tau[1];
          std::cout << "collision of player" << '\n';
          obj2 -> shape.velocityS[0] = v2n_*norm[0] + v2t*tau[0];
          obj2 -> shape.velocityS[1] = v2n_*norm[1] + v2t*tau[1];
          
        }
        } // if diverge
      }
  
}

void Collider::inelasticHit(Collider* source, Collider* obj2)
{
  if ((obj2 -> shape.ifMoveable == false) and (source -> shape.ifMoveable == false)) //do not collide two immoveable objects
    return;

  std::vector<std::vector<float>> vert1 = this -> shape.vertex;
  vert1.push_back({0, 0});
  std::vector<std::vector<float>> vert2 = obj2 -> shape.vertex;
  vert2.push_back({0, 0});
  std::vector<float> c1 = {this -> objPointer -> x, this -> objPointer -> y};
  std::vector<float> c2 = {obj2 -> objPointer -> x, obj2 -> objPointer -> y};
  
  for (int i = 0; i < this -> shape.vertex.size() -1; i++)
    for (int j = 0; j < obj2 -> shape.vertex.size() -1; j++)
      if (checkCrossing(vert1[i], vert1[i+1], vert2[j], vert2[j+1], c1, c2))
      {
        std::vector<float> norm = {-vert2[j+1][1] + vert2[j][1], vert2[j+1][0] - vert2[j][0]};
        float module = sqrt(pow(norm[0], 2) + pow(norm[1], 2));
        norm[0] = norm[0]/module;
        norm[1] = norm[1]/module;
        std::vector<float> tau = {-norm[1], norm[0]}; 
 
        float v1n = source -> shape.velocityS[0] * norm[0] + source -> shape.velocityS[1] * norm[1];
        float v2n = obj2 -> shape.velocityS[0] * norm[0] + obj2 -> shape.velocityS[1] * norm[1];     
        float v1t = source -> shape.velocityS[0] * tau[0] + source -> shape.velocityS[1] * tau[1];
        float v2t = obj2 -> shape.velocityS[0] * tau[0] + obj2 -> shape.velocityS[1] * tau[1];
        float vn = (source -> shape.mass * v1n + obj2 -> shape.mass * v2n)/(source -> shape.mass + obj2 -> shape.mass);
        if ((obj2 -> shape.ifMoveable == false) and (source -> shape.ifMoveable == true))
        {
          source -> shape.velocityS[0] = (v2n) *norm[0] + v1t*tau[0];
          source -> shape.velocityS[1] = (v2n) *norm[1] + v1t*tau[1];
        }

        if ((obj2 -> shape.ifMoveable == true) and (source -> shape.ifMoveable == true))
        {
          source -> shape.velocityS[0] = vn * norm[0] + v1t*tau[0];
          source -> shape.velocityS[1] = vn * norm[1] + v1t*tau[0];
          obj2 -> shape.velocityS[0] = vn * norm[0] + v2t*tau[0];
          obj2 -> shape.velocityS[1] = vn * norm[1] + v2t*tau[0];
        }
      }
}



