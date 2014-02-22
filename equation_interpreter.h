#ifndef EQUATION_INTERPRETER_H
#define EQUATION_INTERPRETER_H
#include <map>
#include "node.h"

class EquationInterpreter
{
public:
  EquationInterpreter(std::string expression);
  double solve(const std::map<char,double>& vars);

private:
  typedef std::string     str_t;
  typedef str_t::iterator str_t_it;

  ast_node ast;
};
#endif // EQUATION_INTERPRETER_H
