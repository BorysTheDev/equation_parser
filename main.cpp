#include <iostream>
#include "calc.h"

using namespace std;

int main()
{
  ast_node ast;

  typedef std::string     str_t;
  typedef str_t::iterator str_t_it;

  str_t expression;

  calculator_ast<str_t_it> calc;

  std::cout << "start\n";
  std::getline(std::cin, expression);
  str_t_it begin = expression.begin(), end = expression.end();

  bool success = qi::phrase_parse( begin, end, calc, qi::space, ast);

  std::cout << "---------------------\n";
  if(success && begin == end)
    std::cout << "Parsing succeeded\n";
  else
    std::cout << "Parsing failed\nstopped at: \""
              << str_t(begin, end) << "\" \n";
  std::cout << "---------------------\n";

  //for (int i = 0; i < 4000; i++){
  double result =
      boost::apply_visitor(ast_result_calculator(2.1), ast);
  std::cout<< std::endl << result << std::endl;
  //}

}

