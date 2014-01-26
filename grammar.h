#ifndef GRAMMAR_H
#define GRAMMAR_H

#define BOOST_SPIRIT_USE_PHOENIX_V3

#include <boost/spirit/include/qi.hpp>
#include <boost/phoenix/phoenix.hpp>

#include "ast.h"
#include "operators.h"

namespace phx = boost::phoenix;
namespace qi = boost::spirit::qi;

using qi::double_;
using qi::on_error;
using qi::fail;
using phx::val;
using phx::construct;

template <typename Iterator>
struct calculator_ast: qi::grammar<Iterator, ast_node(), qi::space_type>
{
  calculator_ast(): calculator_ast::base_type(expr)
  {
    expr =      term[qi::_val = qi::_1] >>
       *( '+' > term[qi::_val = binaryFunc(qi::_val, qi::_1, ops::add)]
        | '-' > term[qi::_val = binaryFunc(qi::_val, qi::_1, ops::sub)]
        );

    term =      factor[qi::_val = qi::_1] >>
       *( '*' > factor[qi::_val = binaryFunc(qi::_val, qi::_1, ops::mul)]
        | '/' > factor[qi::_val = binaryFunc(qi::_val, qi::_1, ops::div)]
        | '^' > factor[qi::_val = binaryFunc(qi::_val, qi::_1, pow)]
        );

    factor = double_  [qi::_val = qi::_1]
        | '(' > expr  [qi::_val = qi::_1] > ')'
        | '-' > factor[qi::_val = unaryFunc(qi::_1, ops::neg)]
        | '+' > factor[qi::_val = qi::_1]
        | qi::no_case["cos"] >> '(' >> expr[qi::_val = unaryFunc(qi::_1, cos)] >> ')'
        | qi::no_case["sin"] >> '(' >> expr[qi::_val = unaryFunc(qi::_1, sin)] >> ')'
        | qi::no_case["log"] >> '(' >> expr[qi::_val = unaryFunc(qi::_1, log)] >> ')'
        | qi::no_case["exp"] >> '(' >> expr[qi::_val = unaryFunc(qi::_1, exp)] >> ')'
        | qi::no_case["sqrt"] >> '(' >> expr[qi::_val = unaryFunc(qi::_1, sqrt)] >> ')'
        | qi::no_case["cbrt"] >> '(' >> expr[qi::_val = unaryFunc(qi::_1, cbrt)] >> ')'
        | qi::char_("a-zA-Z_")[qi::_val = qi::_1]
        ;

    expr.name("expr");
    term.name("term");
    factor.name("factor");

    on_error<fail>(expr, std::cout << val("Error! Expecting ") << qi::_4 << " at: \""
                   << construct<std::string>(qi::_3, qi::_2) << "\"\n\n");
  }

  qi::rule<Iterator, ast_node(), qi::space_type> expr, term, factor;
};

#endif // GRAMMAR_H
