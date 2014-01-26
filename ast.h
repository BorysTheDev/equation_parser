#ifndef AST_H
#define AST_H

#include "node.h"

#include <boost/phoenix/phoenix.hpp>
namespace phx = boost::phoenix;

struct UnaryFuncWrap
{
  template <class T>
  struct result;

  template <class This, class Arg1, class Arg2>
  struct result <This(Arg1, Arg2)>
  {
    typedef ast_node type;
  };

  ast_node operator() (ast_node const & node, char op) const
  {
    return unary_op(node, op);
  }
};

phx::function<UnaryFuncWrap> const unaryFunc = UnaryFuncWrap();

struct BinaryFuncWrap
{
  template <class T>
  struct result;

  template <class This, class Arg1, class Arg2, class Arg3>
  struct result <This(Arg1, Arg2, Arg3)>
  {
    typedef ast_node type;
  };

  ast_node operator()( ast_node const& left, ast_node const& right,
      char op) const
  {
    return binary_op(left, right, op);
  }
};

phx::function<BinaryFuncWrap> const binaryFunc = BinaryFuncWrap();

#endif // AST_H
