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
  float zn1 = v11[1]*v12[0] - v11[0]*v12[1];
  float zn2 = v21[1]*v22[0] - v21[0]*v22[1];
  float x;
  float y;
  float k1;
  float k2;
  float k3;
  float k4;//Lines should not cross centre of coordinates

  k2 = (v11[1] - v12[1])/zn1;
  k4 = (v21[1] - v22[1])/zn2;
  k1 = (v12[0] - v11[0])/zn1;
  k3 = (v22[0] - v21[0])/zn2;
  if (pow((k1-k3)*(k2-k4), 2) < pow(0.00000001, 2)) //parallel lines
  {
    std::cout << "parallel lines" << std::endl;
    return false;
  }
  x = (k1-k3)/(k1*k4 - k3*k2);
  y = (k4-k2)/(k1*k4 - k3*k2);

  if ( (pow((v11[0]+v12[0])/2 - x, 2) < pow((v11[0] -v12[0])/2, 2)) and (pow((v11[1]+v12[1])/2 - y, 2) < pow((v11[1] -v12[1])/2, 2)) )
  {
    std::cout << "true" << std::endl;
    fflush(0);
    return true;
  }
  return false; 
}

bool Collider::checkCollision(Collider* obj2)
{
  std::vector<float> V1 = this -> shape.velocityS;
  std::vector<float> V2 = obj2 -> shape.velocityS;
    
    bool flag = ( (V1[0]-V2[0])*(- this -> objPointer -> x + obj2 -> objPointer -> x) + (V1[1] - V2[1])*(- this -> objPointer -> y + obj2 -> objPointer -> y) > 0);

  if (flag == false)
  {
    //std::cout << "false" << std::endl;
    fflush(0);
    return flag;
  }

  /*if ((this -> shape.ifCircle == true) and (obj2 -> shape.ifCircle == true))
    if ((this -> shape.r + obj2 -> shape.r >= sqrt(pow(this -> objPointer -> x - obj2 -> objPointer -> x, 2) + pow(this -> objPointer -> y - obj2 -> objPointer -> y, 2))))
      return true;
    else
      return false;*/
  
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

void Collider::resolveCollision(Collider* obj2, Singleton* sing)
{
  if (this -> objPointer -> getComponent<BehaviourWhileCollided>())
  {
    this -> objPointer -> getComponent<BehaviourWhileCollided>() -> collisionResolving(this, obj2);
    obj2 -> objPointer -> getComponent<BehaviourWhileCollided>() -> collisionResolving(obj2, this);
    //std::cout << "collision resolving is found" << '\n';
    fflush(0);
  }
}









