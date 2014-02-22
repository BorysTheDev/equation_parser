#include <iostream>
#include "equation_interpreter.h"

using namespace std;

int main()
{
  EquationInterpreter ei("2+3*(sin(0)-4/2) - t * k");

  for (int i = 0; i < 4000; i++){
  double result = ei.solve({{'t',i}, {'k',0.5}});
  std::cout<< std::endl << result << std::endl;
  }

}

