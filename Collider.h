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
  std::vector<float> V = {0, 0};
  V[0] = this -> shape.velocityS[0] - obj2 -> shape.velocityS[0];
  V[1] = this -> shape.velocityS[1] - obj2 -> shape.velocityS[1];
  bool flag = true;
  std::vector<std::vector<float>> vert1 = this -> shape.vertex;
  vert1.push_back({0, 0});
  std::vector<std::vector<float>> vert2 = obj2 -> shape.vertex;
  vert2.push_back({0, 0});
  std::vector<float> c1 = {this -> objPointer -> x, this -> objPointer -> y};
  std::vector<float> c2 = {obj2 -> objPointer -> x, obj2 -> objPointer -> y};
  int n = 0;
  int m = 0;
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
  if (this -> objPointer -> getComponent<BehaviourWhileCollided>())
    this -> objPointer -> getComponent<BehaviourWhileCollided>() -> collisionResolving(this, obj2);
}










