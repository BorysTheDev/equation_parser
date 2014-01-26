#include <iostream>
#include "calc.h"
#include "equation_interpreter.h"

using namespace std;

int main()
{
  EquationInterpreter ei("2+3*(sin(0)-4/2)");

  for (int i = 0; i < 4000; i++){
  double result = ei.solve({{'t',i}});
  std::cout<< std::endl << result << std::endl;
  }

}

