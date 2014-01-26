#ifndef CALC_H
#define CALC_H
// bring in the calculator grammar details
#include "grammar.h"

#include <boost/variant.hpp>

struct ast_result_calculator
    : boost::static_visitor<double>
{

  // evaluate immediate value
  double operator() (double val) const
  {
    return val;
  }

  // evaluate binary operation
  double operator() (binary_op const & node) const
  {
    // evaluate the left branch
    double left_val  = boost::apply_visitor(*this, node.left);
    // evaluate the right branch
    double right_val = boost::apply_visitor(*this, node.right);

    switch(node.op)
    {
    case '+':
      return left_val + right_val;
    case '-':
      return left_val - right_val;
    case '*':
      return left_val * right_val;
    case '/':
      return left_val / right_val;
    default:
      return 0;
    }
  }

  // evaluate unary operation
  double operator() (unary_op const & node) const
  {
    // evaluate the subject
    double subj_val = boost::apply_visitor(*this, node.subj);

    switch(node.op)
    {
    case '-':
      return -subj_val;
    default:
      return 0;
    }
  }
};
#endif // CALC_H
