#ifndef SCRIPT
#define SCRIPT

#include "Head.hpp"

class Script : public Component
{
  public:
  virtual void execute(Singleton* sing)
  {}
  std::string writeDown()
  {
    std::string s = "@@@";
    s += this -> name;
    s += '\n';
    return s;
  }
};

#endif
