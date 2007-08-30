%{
  /*
   * Copyright (C) 2006, The EROS Group, LLC.
   *
   * This file is part of the EROS Operating System runtime library.
   *
   * This library is free software; you can redistribute it and/or
   * modify it under the terms of the GNU Lesser General Public License
   * as published by the Free Software Foundation; either version 2
   * of the License, or (at your option) any later version.
   *
   * This library is distributed in the hope that it will be useful,
   * but WITHOUT ANY WARRANTY; without even the implied warranty of
   * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   * GNU Lesser General Public License for more details.
   *
   * You should have received a copy of the GNU Lesser General Public
   * License along with this library; if not, write to the Free Software
   * Foundation, 59 Temple Place - Suite 330 Boston, MA 02111-1307, USA.
   */

#include <sys/fcntl.h>
#include <sys/stat.h>
#include <getopt.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <dirent.h>
#include <iostream>

#include <string>

#include "ParseType.hxx"
#include <libsherpa/avl.hxx>
  
using namespace sherpa;
using namespace std;  

#define YYSTYPE ParseType
#define YYLEX_PARAM (Lexer *)lexer
#undef yyerror
#define yyerror(lexer, s) lexer->ReportParseError(s)

#include "Lexer.hxx"

#define SHOWPARSE(s) \
  do { \
    if (Options::showParse) \
      lexer->errStream << (s) << std::endl;		\
  } while(false);
#define SHOWPARSE1(s,x) \
  do { \
    if (Options::showParse) \
      lexer->errStream << (s) << " " << (x) << std::endl;	\
  } while(false);


int num_errors = 0;  /* hold the number of syntax errors encountered. */

inline int bntest_lex(YYSTYPE *lvalp, Lexer *lexer)
{
  return lexer->lex(lvalp);
}

AvlMap<std::string, sherpa::BigNum> env;

%}

%pure-parser
%parse-param {Lexer *lexer}

%token <tok> tk_Reserved	/* reserved words */

/* Categorical terminals: */
%token <tok> tk_Ident
%token <val> tk_Int

/* Primary types and associated hand-recognized literals: */
%token <tok> '(' ')'

%token <tok> '\n'		/* input terminated by newline */

/* Assignment, statements */
%token <tok> '='

%token <tok> tk_NOT
%token <tok> tk_TRUE
%token <tok> tk_FALSE

 /* Customary expression operators here. Order of occurrence is
    significant, because it defines precedence. */
%left <tok> '-' '+'
%left <tok> '*' '/'
%left <tok> '%'

 /* %type <> start */
 /* %type <> stmt_seq statement */
%type <val> expr

%%

start: stmt_seq {
};

stmt_seq: statement {
};

stmt_seq: stmt_seq statement {
};

statement: tk_Ident '=' expr '\n' {
  env.set($1.str, $3);
  // std::cout << "# " << $1.str << "=" << $3 << '\n';
};

statement:  expr '\n' {
  std::cout << $1 << '\n';
};

statement:  '\n' {
  
};

expr : expr '+' expr {
  $$ = $1 + $3;
};

expr : expr '-' expr {
  $$ = $1 - $3;
};

expr : expr '*' expr {
  $$ = $1 * $3;
};

expr : expr '/' expr {
  $$ = $1 / $3;
};

expr : expr '%' expr {
  $$ = $1 % $3;
};

expr : '(' expr ')' {
  $$ = $2;
};

expr : '-' expr {
  $$ = $2.neg();
};

expr : tk_Int {
  $$ = $1;
};

expr : tk_Ident {
  AvlMapNode<std::string, BigNum> *nd = env.lookup($1.str);

  if (nd) {
    $$ = nd->value;
  }
  else {
    std::cerr << "Unbound variable \"" << $1.str << "\"\n";
    $$ = 0;
  }
};
%%

int main(int argc, char *argv[])
{
  Lexer lexer(std::cerr, std::cin, new Path("<stdin>"));

  bntest_parse(&lexer);
}
