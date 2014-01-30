#ifndef CALC_H
#define CALC_H
// bring in the calculator grammar details
#include "grammar.h"

#include <boost/variant.hpp>

struct ast_result_calculator: boost::static_visitor<double>
{
  // evaluate immediate value
  double operator()(double val) const
  {
    return val;
  }

  // evaluate variable value
  double operator()(char t) const
  {
    return vars.at(t);
  }

  // evaluate binary operation
  double operator()(binary_op const & node) const
  {
    // evaluate the left branch
    double left_val  = boost::apply_visitor(*this, node.left);
    // evaluate the right branch
    double right_val = boost::apply_visitor(*this, node.right);

    return node.op(left_val, right_val);
  }

  // evaluate unary operation
  double operator() (unary_op const & node) const
  {
    return node.op(boost::apply_visitor(*this, node.subj));
  }


  ast_result_calculator(const std::map<char, double> &v) : vars(v){}
  const std::map<char, double> &vars;
};
#endif // CALC_H
