#include "Head.hpp"
#include "Collider.hpp"

#include "GameObject.hpp"
#include "math.h"
#include "Renderer.hpp"
#include "ScriptController.hpp"
#include "GraphicManager.hpp"
#include "Singleton.h"
#include "Script.hpp"
#include "DataStorage.hpp"

void resolveInelasticHit(std::vector<float> norm, Collider* source, Collider* obj2)
{
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
  
  if ((obj2 -> shape.ifMoveable == true) and (source -> shape.ifMoveable == false))
  {
    obj2 -> shape.velocityS[0] = (v1n) *norm[0] + v2t*tau[0];
    obj2 -> shape.velocityS[1] = (v1n) *norm[1] + v2t*tau[1];
  }

  if ((obj2 -> shape.ifMoveable == true) and (source -> shape.ifMoveable == true))
  {
    source -> shape.velocityS[0] = vn * norm[0] + v1t*tau[0];
    source -> shape.velocityS[1] = vn * norm[1] + v1t*tau[0];
    obj2 -> shape.velocityS[0] = vn * norm[0] + v2t*tau[0];
    obj2 -> shape.velocityS[1] = vn * norm[1] + v2t*tau[0];
  }
}

void resolveElasticHit(std::vector<float> norm, Collider* source, Collider* obj2)
{
  float module = sqrt(pow(norm[0], 2) + pow(norm[1], 2));
  norm[0] = norm[0]/module;
  norm[1] = norm[1]/module;
  
  std::vector<float> tau = {-norm[1], norm[0]}; 
 
  float v1n = source -> shape.velocityS[0] * norm[0] + source -> shape.velocityS[1] * norm[1];
  float v2n = obj2 -> shape.velocityS[0] * norm[0] + obj2 -> shape.velocityS[1] * norm[1];     
  float v1t = source -> shape.velocityS[0] * tau[0] + source -> shape.velocityS[1] * tau[1];
  float v2t = obj2 -> shape.velocityS[0] * tau[0] + obj2 -> shape.velocityS[1] * tau[1];

  float k = source -> shape.mass / obj2 -> shape.mass;
  if (obj2 -> shape.ifMoveable == false)
    k = 0;
  
  float a = k+1;
  float b = -2*v2n - 2*k*v1n;
  float c = (k-1)*v1n*v1n + 2*v1n*v2n;
        
  if ( (source -> shape.ifMoveable == true))
  {
    if (pow(b, 2) - 4*a*c < 0)
    {
      std::cout << "discriminant in elasticCollision < 0" << '\n';
      return;
    }
    float v1n_ = (-b + sqrt(pow(b, 2) - 4*a*c))/(2*a);
    float v2n_ = k*(v1n - v1n_) + v2n;
    source -> shape.velocityS[0] = v1n_*norm[0] + v1t*tau[0];
    source -> shape.velocityS[1] = v1n_*norm[1] + v1t*tau[1];
          
    obj2 -> shape.velocityS[0] = v2n_*norm[0] + v2t*tau[0];
    obj2 -> shape.velocityS[1] = v2n_*norm[1] + v2t*tau[1];        
  }
  
  if (source -> shape.ifMoveable == false)
  {
    obj2 -> shape.velocityS[0] = 2*(v1n) *norm[0] + v2t*tau[0];
    obj2 -> shape.velocityS[1] = 2*(v1n) *norm[1] + v2t*tau[1];
  }
}
 
float scMul(std::vector<float> v1, std::vector<float> v2)
{
  return v1[0]*v2[0] + v1[1]*v2[1];
}

std::vector<float> vecMul(std::vector<float> v1, std::vector<float> v2)
{
  std::vector<float> v = {0, v1[0]*v2[1] - v1[1]*v2[0]};
  return v;
}

bool checkCrossing_Line_Ball(std::vector<float> v1, std::vector<float> v2, std::vector<float> c1, std::vector<float> c2, float r)
{
  v1[0] += c1[0];
  v1[1] += c1[1];
  v2[0] += c1[0];
  v2[1] += c1[1];
  std::vector<float> V1 = {v2[0] - v1[0], v2[1] - v1[1]};
  std::vector<float> V2 = {c2[0] - v1[0], c2[1] - v1[1]};
  std::vector<float> V3 = {c2[0] - v2[0], c2[1] - v2[1]};
  if (scMul(V1, V2)*scMul(V1, V3) < 0)
    return (((2*sqrt(scMul(vecMul(V1, V2), vecMul(V1, V2))))/sqrt(scMul(V1, V1))) < r);
  
  return (fmin(sqrt(scMul(V2, V2)), sqrt(scMul(V3, V3))) < r); 
}


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
  std::vector<float> c1 = {this -> objPointer -> x, this -> objPointer -> y};
  std::vector<float> c2 = {obj2 -> objPointer -> x, obj2 -> objPointer -> y};

  if ((this -> shape.ifCircle == true) and (obj2 -> shape.ifCircle == true))
    if ((this -> shape.r + obj2 -> shape.r >= sqrt(pow(this -> objPointer -> x - obj2 -> objPointer -> x, 2) + pow(this -> objPointer -> y - obj2 -> objPointer -> y, 2))))
      return true;
    else
      return false;
  
  if ((this -> shape.ifCircle == true) and (obj2 -> shape.ifCircle == false))
  {
    for (int i = 0; i < obj2 -> shape.vertex.size() - 1; i++)
      if (checkCrossing_Line_Ball(obj2 -> shape.vertex[i], obj2 -> shape.vertex[i+1], c2, c1, this -> shape.r))
        return true;
    return false;  
  }
  
  if ((this -> shape.ifCircle == false) and (obj2 -> shape.ifCircle == false))
  {
    std::vector<std::vector<float>> v1 = this-> shape.vertex;
    int n1 = v1.size();
    v1.push_back(v1[0]);

    std::vector<std::vector<float>> v2 = obj2-> shape.vertex;
    int n2 = v2.size();
    v2.push_back(v2[0]);
    
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
  std::vector<float> c1 = {this -> objPointer -> x, this -> objPointer -> y};
  std::vector<float> c2 = {obj2 -> objPointer -> x, obj2 -> objPointer -> y};

  if ((this -> shape.ifCircle == false) and (obj2 -> shape.ifCircle == false))
  {
    std::vector<std::vector<float>> vert1 = this -> shape.vertex;
    vert1.push_back({0, 0});
    std::vector<std::vector<float>> vert2 = obj2 -> shape.vertex;
    vert2.push_back({0, 0});
  
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

  if ((this -> shape.ifCircle == true) and (obj2 -> shape.ifCircle == false))
  {
    std::vector<std::vector<float>> vert2 = obj2 -> shape.vertex;
    for (int j = 0; j < vert2.size() - 1; j++)
      if (checkCrossing_Line_Ball(vert2[j], vert2[j+1], c2, c1, this -> shape.r))
      {
        std::vector<float> border = {-vert2[j+1][1] + vert2[j][1], vert2[j+1][0] - vert2[j][0]};
        if ((((border[0])*(-vert2[j][0])+(border[1])*(-vert2[j][1]))*((border[0])*(V[0])+(border[1])*(V[1]))) > 0) 
            return false;
      }
    return true;
  }
  
  if ((this -> shape.ifCircle == true) and (obj2 -> shape.ifCircle == true))
  {
    return (((obj2 -> objPointer -> x - this -> objPointer -> x)*V[0] + (obj2 -> objPointer -> y - this -> objPointer -> y)*V[1]) < 0);
  }
}

void Collider::resolveCollision(Collider* obj2, Singleton* sing)
{
  if ((this -> shape.ifCollideable == false) or (obj2 -> shape.ifCollideable == false))
    return;
  if (this -> checkDiverge(obj2) == false)                            
    {
      if ((obj2 -> shape.ifElastic == true) and (this -> shape.ifElastic == true))
        this -> elasticHit(this, obj2);
      else
        this -> inelasticHit(this, obj2);
    }
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
  
  if ((this -> shape.ifCircle == false) and (obj2 -> shape.ifCircle == false))
  for (int i = 0; i < vert1.size()-1; i++)
    for (int j = 0; j < vert2.size()-1; j++)
      if (checkCrossing(vert1[i], vert1[i+1], vert2[j], vert2[j+1], c1, c2))
      {
        std::vector<float> norm = {-vert2[j+1][1] + vert2[j][1], vert2[j+1][0] - vert2[j][0]};
        if (((norm[0])*(-vert2[j][0])+(norm[1])*(-vert2[j][1])) > 0)
        {
          norm[0] = -norm[0];
          norm[1] = -norm[1];
        }
        if ((((norm[0])*(-vert2[j][0])+(norm[1])*(-vert2[j][1]))*((norm[0])*(V[0])+(norm[1])*(V[1]))) > 0) 
          resolveElasticHit(norm, source, obj2);
      }
  
  if ((this -> shape.ifCircle == true) and (obj2 -> shape.ifCircle == false))
  for (int j = 0; j < vert2.size() - 1; j++)
    if (checkCrossing_Line_Ball(vert2[j], vert2[j+1], c2, c1, this -> shape.r))
    {
      std::vector<float> norm = {-vert2[j+1][1] + vert2[j][1], vert2[j+1][0] - vert2[j][0]};
      if (((norm[0])*(-vert2[j][0])+(norm[1])*(-vert2[j][1])) > 0)
      {
        norm[0] = -norm[0];
        norm[1] = -norm[1];
      }
      if ((((norm[0])*(-vert2[j][0])+(norm[1])*(-vert2[j][1]))*((norm[0])*(V[0])+(norm[1])*(V[1]))) > 0) 
        resolveElasticHit(norm, source, obj2);
    } 
  if ((this -> shape.ifCircle == true) and (obj2 -> shape.ifCircle == true))
  {
    std::vector<float> norm = {source -> objPointer -> x - obj2 -> objPointer -> x, source -> objPointer -> y - obj2 -> objPointer -> y};
    resolveElasticHit(norm, source, obj2);
  }

}

void Collider::inelasticHit(Collider* source, Collider* obj2)
{

  if ((obj2 -> shape.ifMoveable == false) and (source -> shape.ifMoveable == false)) //do not collide two immoveable objects
    return;
  std::vector<float> V = {this -> shape.velocityS[0] - obj2 -> shape.velocityS[0], this -> shape.velocityS[1] - obj2 -> shape.velocityS[1]};
  
  std::vector<std::vector<float>> vert1 = this -> shape.vertex;
  std::vector<std::vector<float>> vert2 = obj2 -> shape.vertex;
  std::vector<float> c1 = {this -> objPointer -> x, this -> objPointer -> y};
  std::vector<float> c2 = {obj2 -> objPointer -> x, obj2 -> objPointer -> y};
  
  if ((this -> shape.ifCircle == false) and (obj2 -> shape.ifCircle == false))
  for (int i = 0; i < vert1.size()-1; i++)
    for (int j = 0; j < vert2.size()-1; j++)
      if (checkCrossing(vert1[i], vert1[i+1], vert2[j], vert2[j+1], c1, c2))
      {
        std::vector<float> norm = {-vert2[j+1][1] + vert2[j][1], vert2[j+1][0] - vert2[j][0]};
        if (((norm[0])*(-vert2[j][0])+(norm[1])*(-vert2[j][1])) > 0)
        {
          norm[0] = -norm[0];
          norm[1] = -norm[1];
        }
        if ((((norm[0])*(-vert2[j][0])+(norm[1])*(-vert2[j][1]))*((norm[0])*(V[0])+(norm[1])*(V[1]))) > 0) 
          resolveInelasticHit(norm, source, obj2);
      }
  
  if ((this -> shape.ifCircle == true) and (obj2 -> shape.ifCircle == false))
  for (int j = 0; j < vert2.size() - 1; j++)
    if (checkCrossing_Line_Ball(vert2[j], vert2[j+1], c2, c1, this -> shape.r))
    {
      std::vector<float> norm = {-vert2[j+1][1] + vert2[j][1], vert2[j+1][0] - vert2[j][0]};
      if (((norm[0])*(-vert2[j][0])+(norm[1])*(-vert2[j][1])) > 0)
      {
        norm[0] = -norm[0];
        norm[1] = -norm[1];
      }
      if ((((norm[0])*(-vert2[j][0])+(norm[1])*(-vert2[j][1]))*((norm[0])*(V[0])+(norm[1])*(V[1]))) > 0) 
        resolveInelasticHit(norm, source, obj2);
    } 
  if ((this -> shape.ifCircle == true) and (obj2 -> shape.ifCircle == true))
  {
    std::vector<float> norm = {source -> objPointer -> x - obj2 -> objPointer -> x, source -> objPointer -> y - obj2 -> objPointer -> y};
    resolveInelasticHit(norm, source, obj2);
  }
}

bool Collider::checkCrossingBetweenPreviousTics(Collider* source, Collider* obj2)  //use it with checkCollision function
{                                                                                  //source is fast, it hits obj2
  std::vector<std::vector<float>> vert1 = this -> shape.vertex;
  std::vector<std::vector<float>> vert2 = obj2 -> shape.vertex;

  std::vector<float> v11 = {source -> objPointer -> x - source -> shape.velocityS[0], source -> objPointer -> y - source -> shape.velocityS[1]};
  std::vector<float> v12 = {source -> objPointer -> x, source -> objPointer -> y};
  std::vector<float> v21 = {obj2 -> objPointer -> x - obj2 -> shape.velocityS[0], obj2 -> objPointer -> y - obj2 -> shape.velocityS[1]};
  std::vector<float> v22 = {obj2 -> objPointer -> x, obj2 -> objPointer -> y};
  std::vector<float> c1 = {0, 0};
  std::vector<float> c2 = {0, 0};
  for (int i = 0; i < vert1.size(); i++)
    for (int j = 0; j < vert2.size() - 1; j++)
    {
      v11 = {source->objPointer->x + vert1[i][0] - source->shape.velocityS[0], source->objPointer->y + vert1[i][1] - source->shape.velocityS[1]};
      v12 = {source -> objPointer -> x + vert1[i][0], source -> objPointer -> y + vert1[i][1]};
      v21 = {obj2->objPointer->x + vert2[j][0], obj2->objPointer->y + vert2[j][1]};
      v22 = {obj2 -> objPointer -> x + vert2[j+1][0], obj2 -> objPointer -> y + vert2[j+1][1]};
      if (checkCrossing(v11, v12, v21, v22, c1, c2))
        return true;
    }
  return false;
}

std::string Collider::writeDown()
{
  std::string s = "***Collider";
  s += '\n';
  s += BTS(this -> shape.ifMoveable);
  s += '\n';
  s += BTS(this -> shape.ifCollideable);
  s += '\n';
  s += BTS(this -> shape.ifElastic);
  s += '\n';
  s += BTS(this -> shape.ifCircle);
  s += '\n';
  s += std::to_string(shape.mass);
  s += '\n';
  s += std::to_string(shape.r);
  s += '\n';
  s += std::to_string(shape.velocityS[0]);
  s += '\n';
  s += std::to_string(shape.velocityS[1]);
  s += '\n';

  for (std::vector<float> v: this -> shape.vertex)
    s += std::to_string(v[0]) + " " + std::to_string(v[1]) + '\n';

  return s;
}

void initCollider(std::string object, Singleton* sing, std::string component)
{
  sing -> data -> getObject(object) -> addComponent<Collider>(sing);
  if (component.substr(0, component.find('\n')) == "true")
    sing -> data -> getObject(object) -> getComponent<Collider>() -> shape.ifMoveable = true;
  else
    sing -> data -> getObject(object) -> getComponent<Collider>() -> shape.ifMoveable = false;
  component = component.substr(component.find('\n') + 1);

  if (component.substr(0, component.find('\n')) == "true")
    sing -> data -> getObject(object) -> getComponent<Collider>() -> shape.ifCollideable = true;
  else
    sing -> data -> getObject(object) -> getComponent<Collider>() -> shape.ifCollideable = false;
  component = component.substr(component.find('\n') + 1);

  if (component.substr(0, component.find('\n')) == "true")
    sing -> data -> getObject(object) -> getComponent<Collider>() -> shape.ifElastic = true;
  else
    sing -> data -> getObject(object) -> getComponent<Collider>() -> shape.ifElastic = false;
  component = component.substr(component.find('\n') + 1);

  if (component.substr(0, component.find('\n')) == "true")
    sing -> data -> getObject(object) -> getComponent<Collider>() -> shape.ifCircle = true;
  else
    sing -> data -> getObject(object) -> getComponent<Collider>() -> shape.ifCircle = false;
  component = component.substr(component.find('\n') + 1);

  sing -> data -> getObject(object) -> getComponent<Collider>() -> shape.mass = std::stof(component.substr(0, component.find('\n')));
  component = component.substr(component.find('\n') + 1);

  sing -> data -> getObject(object) -> getComponent<Collider>() -> shape.r = std::stof(component.substr(0, component.find('\n')));
  component = component.substr(component.find('\n') + 1);

  sing -> data -> getObject(object) -> getComponent<Collider>() -> shape.velocityS[0] = std::stof(component.substr(0, component.find('\n')));
  component = component.substr(component.find('\n') + 1);

  sing -> data -> getObject(object) -> getComponent<Collider>() -> shape.velocityS[1] = std::stof(component.substr(0, component.find('\n')));
  component = component.substr(component.find('\n') + 1);
  
  int x;
  int y;
  while (component.find("...") > 0)
  {
    x = std::stof(component.substr(0, component.find(' ')));
    y = std::stof(component.substr(component.find(' ') + 1, component.find('\n')));
    sing -> data -> getObject(object) -> getComponent<Collider>() ->shape.addVertex(x, y);
    component = component.substr(component.find('\n') + 1);
  }

}








