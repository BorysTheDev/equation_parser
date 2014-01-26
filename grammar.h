#ifndef GRAMMAR_H
#define GRAMMAR_H

#define BOOST_SPIRIT_USE_PHOENIX_V3

#include <boost/spirit/include/qi.hpp>
#include <boost/phoenix/phoenix.hpp>

#include "ast.h"

namespace phx = boost::phoenix;
namespace qi = boost::spirit::qi;

using qi::_val;
using qi::_1;
using qi::_2;
using qi::_3;
using qi::_4;
using qi::double_;
using qi::grammar;
using qi::rule;
using qi::on_error;
using qi::fail;
using qi::space_type;
using phx::val;
using phx::construct;

template <typename Iterator>
struct calculator_ast: grammar<Iterator, ast_node(), space_type>
{
  calculator_ast(): calculator_ast::base_type(expr)
  {
    expr =
        term[ _val = _1 ]
        >> *('+' > term
        [ _val = binaryFunc(_val, _1, '+') ]
        |   '-'     > term
        [ _val = binaryFunc(_val, _1, '-') ]
        )
        ;

        term =
        factor                  [ _val = _1 ]
        >> *(   '*'     > factor
        [ _val = binaryFunc(_val, _1, '*') ]
        |   '/'     > factor
        [ _val = binaryFunc(_val, _1, '/') ]
        )
        ;

        factor =
        double_               [ _val = _1 ]
        |   '('     > expr      [ _val = _1 ]   > ')'
        |   '-'     > factor    [ _val = unaryFunc(_1, '-')]
        |   '+'     > factor    [ _val = _1]
        ;

        expr.name("expr");
        term.name("term");
        factor.name("factor");

        on_error<fail>(expr,
        std::cout << val("Error! Expecting ") << _4 << " at: \""
        << construct<std::string>(_3, _2) << "\"\n\n");
  }

        rule<Iterator, ast_node(), space_type> expr, term, factor;
  };

    #endif // GRAMMAR_H
