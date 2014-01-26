#ifndef NODE_H
#define NODE_H

#include <boost/variant.hpp>

struct binary_op;
struct unary_op;

typedef boost::variant<double,
boost::recursive_wrapper<binary_op>,
boost::recursive_wrapper<unary_op>
> ast_node;

struct binary_op
{
  binary_op(ast_node const& left, ast_node const& right, char op)
    : left(left), right(right), op(op) {}

  char op;
  ast_node left;
  ast_node right;
};

struct unary_op
{
  unary_op(ast_node const& subj, char op): subj(subj), op(op){}

  char op;
  ast_node subj;
};

#endif // NODE_H
