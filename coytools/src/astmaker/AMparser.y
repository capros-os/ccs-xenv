%{
/*
 * Copyright (C) 2008, The EROS Group, LLC.
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
#include <sstream>

#include "config.h"
#include "ParseType.hxx"
#include <libsherpa/rpmversion.hxx>

extern bool showparse;	/* global debugging flag */

#define YYSTYPE ParseType
#define YYLEX_PARAM (AMlexer *)lexer
#undef yyerror
#define yyerror(lexer, pr, s) ((AMlexer *)lexer)->ReportParseError(s)

#include "AMlexer.hxx"

void
diag_printf(const std::string &s)
{
  std::cerr << s << std::endl;
}

void
diag_printf(const std::string &s, const std::string &t) 
{
  std::cerr << s << "  " << t << std::endl;
}

#define SHOWPARSE(s) if (showparse) diag_printf(s)
#define SHOWPARSE1(s,x) if (showparse) diag_printf(s,x)

int num_errors = 0;  /* hold the number of syntax errors encountered. */

inline int amlex(YYSTYPE *lvalp, AMlexer *lexer)
{
  return lexer->amlex(lvalp);
}

void
check_ifbound(ParseResult *pr, AstInfo *aInfo)
{
  for (size_t i = 0; i < pr->asts.size(); i++) {
    if (pr->asts[i]->nm.str == aInfo->nm.str) {
      std::cerr << aInfo->nm.loc.asString();
      std::cerr << ": Error: \""
		<< aInfo->nm.str
		<< "\" is already bound."
		<< std::endl;
      exit(1);
    }
  }
}

%}


%lex-param {AMlexer *lexer}
%pure-parser
%parse-param {AMlexer *lexer}
%parse-param {ParseResult *pr}

%token <tok>      tk_MEMBERS;
%token <tok>      tk_CONSTRUCT;
%token <tok>      tk_COPYRIGHT;
%token <tok>      tk_ASTMAKER;
%token <tok>      tk_SOURCE;
%token <tok>      tk_SOURCETOP;
%token <tok>      tk_HEADER;
%token <tok>      tk_INCLUDE;
%token <tok>      tk_NAMESPACE;
%token <tok>      tk_CodeFragment;

/* Following are not used, but are needed internally by the lexer. */
%token <tok>      tk_IntegerLiteral
%token <tok>      tk_CharLiteral
%token <tok>      tk_WhiteSpace

%token <tok>      tk_StringLiteral
%token <tok>      tk_Ident
%token <tok>      tk_Version
%token <tok>      tk_AST
%token <tok>      tk_GROUP
%token <tok>      tk_LEAF
%token <tok>      '+' '*' '=' '|' ';' '?'

%type <NONE>      start
%type <NONE>      definition
%type <NONE>      definitions

%type  <children> childList groupMembers
%type  <child>    child
%type  <tok>      ast
%%

start: definitions {
};

definitions: definitions definition {
};

definitions: definition {
};

definition: tk_NAMESPACE tk_Ident {
  if (pr->nmspace.size()) {
    std::cerr << $1.loc.asString();
    std::cerr << ": Error: at most one namespace declaration "
	      << "is permitted per input file" << std::endl;
    exit(1);
  }
  pr->nmspace = $2.str;
};

definition: tk_ASTMAKER tk_Version {
  if (pr->needsAstVersion.size()) {
    std::cerr << $1.loc.asString();
    std::cerr << ": Error: the required astmaker version should be" 
              << std::endl
	      << "   specified in at most one location." 
              << std::endl;
    exit(1);
  }

  if (sherpa::compare_rpm_versions(ASTMAKER_VERSION, $2.str) < 0) {
    std::cerr << $1.loc.asString();
    std::cerr << ": Error: This is astmaker version " 
              << ASTMAKER_VERSION << std::endl;
    std::cerr << "  The input file requires astmaker version >= "
              << $2.str
	      << std::endl
              << "  Consider checking for astmaker updates."
              << std::endl;
    exit(1);
  }
  pr->needsAstVersion = $2.str;
};

definition: tk_COPYRIGHT tk_CodeFragment {
  pr->copyright << $2.str;
};

definition: tk_MEMBERS tk_CodeFragment {
  pr->members << $2.str;
};

definition: tk_SOURCE tk_CodeFragment {
  pr->source << $2.str;
};

definition: tk_SOURCETOP tk_CodeFragment {
  pr->sourceTop << $2.str;
};

definition: tk_HEADER tk_CodeFragment {
  pr->header << $2.str;
};

definition: tk_INCLUDE tk_CodeFragment {
  pr->include << $2.str;
};

definition: tk_CONSTRUCT tk_CodeFragment {
  pr->construct << $2.str;
};

definition: tk_GROUP tk_Ident '=' groupMembers ';' {
  AstInfo *aInfo = new AstInfo(dt_group, $2);
  aInfo->children = $4;

  check_ifbound(pr, aInfo);
  pr->asts.push_back(aInfo);
};

definition: tk_AST tk_Ident '=' childList ';' {
  sherpa::LToken astName($2.loc, "<" + $2.str + ">");
  AstInfo *aInfo = new AstInfo(dt_ast, $2, astName);
  aInfo->children = $4;

  check_ifbound(pr, aInfo);
  pr->asts.push_back(aInfo);
};

definition: tk_AST tk_Ident '(' tk_StringLiteral ')' '=' childList ';' {
  AstInfo *aInfo = new AstInfo(dt_ast, $2, $4);
  aInfo->children = $7;

  check_ifbound(pr, aInfo);
  pr->asts.push_back(aInfo);
};

definition: tk_LEAF tk_Ident ';' {
  sherpa::LToken astName($2.loc, "<" + $2.str + ">");
  AstInfo *aInfo = new AstInfo(dt_leaf, $2, astName);

  check_ifbound(pr, aInfo);
  pr->asts.push_back(aInfo);
}

definition: tk_LEAF tk_Ident '(' tk_StringLiteral ')' ';' {
  AstInfo *aInfo = new AstInfo(dt_leaf, $2, $4);

  check_ifbound(pr, aInfo);
  pr->asts.push_back(aInfo);
}

groupMembers: tk_Ident {
  $$ = new ChildVec;
  $$->push_back(new ChildNode($1));
};

groupMembers: groupMembers '|' tk_Ident {
  $$ = $1;
  $$->push_back(new ChildNode($3));
};

childList: child {
  $$ = new ChildVec;
  $$->push_back($1);
};

childList: childList child {
  $$ = $1;
  $$->push_back($2);
};

child: ast {
  $$ = new ChildNode($1);
};

child: ast '*' {
  $$ = new ChildNode($1, '*');
};

child: ast '+' {
  $$ = new ChildNode($1, '+');
};

child: ast '?' {
  $$ = new ChildNode($1, '?');
};

ast: tk_Ident {
  $$ = $1;
};

ast : '(' groupMembers ')' {
  std::string nm = AstInfo::GenerateGroupName();
  AstInfo *aInfo = new AstInfo(dt_group, nm);
  aInfo->children = $2;

  check_ifbound(pr, aInfo);
  pr->asts.push_back(aInfo);
  $$ = sherpa::LToken(nm);
}
%%
