#ifndef NODE_H
#define NODE_H

#include <boost/variant.hpp>

struct binary_op;
struct unary_op;

namespace impl
{
  typedef double (*unaryFunc)(double);
  typedef double (*binaryFunc)(double, double);
}

typedef boost::variant<double, char,
boost::recursive_wrapper<binary_op>,
boost::recursive_wrapper<unary_op>
> ast_node;

struct binary_op
{
  binary_op(ast_node const& left, ast_node const& right, impl::binaryFunc op)
    : left(left), right(right), op(op) {}

  impl::binaryFunc op;
  ast_node left;
  ast_node right;
};

struct unary_op
{
  unary_op(ast_node const& subj, impl::unaryFunc op): subj(subj), op(op){}

  impl::unaryFunc op;
  ast_node subj;
};

#endif // NODE_H
