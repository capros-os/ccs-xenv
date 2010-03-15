/* -*- Mode: c -*- */
/*
 * Copyright (C) 2008, The EROS Group, LLC.
 * All rights reserved.
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

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

#include <unicode/uchar.h>
#include <libsherpa/LexLoc.hxx>
#include <libsherpa/utf8.hxx>

#include "AMlexer.hxx"
#include "AMparser.hxx"

using namespace std;
using namespace sherpa;

struct KeyWord {
  const char *nm;
  int  tokValue;
} keywords[] = {
  { "%construct",  tk_CONSTRUCT },
  { "%copyright",  tk_COPYRIGHT },
  { "%header",     tk_HEADER },
  { "%include",    tk_INCLUDE },
  { "%members",    tk_MEMBERS },
  { "%namespace",  tk_NAMESPACE },
  { "%source",     tk_SOURCE },
  { "%sourcetop",  tk_SOURCETOP },
  { "AST",         tk_AST },
  { "GROUP",       tk_GROUP },
  { "LEAF",        tk_LEAF },

  { 0,                  0 }	// sentinal
};

static int
kwstrcmp(const void *vKey, const void *vCandidate)
{
  const char *key = ((const KeyWord *) vKey)->nm;
  const char *candidate = ((const KeyWord *) vCandidate)->nm;

  if (candidate == 0)
    return -1;

  return strcmp(key, candidate);
}

int
AMlexer::kwCheck(const char *s)
{
#if 0
  if (ifIdentMode) {
    if (!valid_ifident_start(*s))
      return tk_Reserved;

    for (++s; *s; s++)
      if (!valid_ifident_continue(*s))
	return tk_Reserved;

    return tk_Ident;
  }
#endif

  KeyWord key = { s, 0 };
  KeyWord *entry = 
    (KeyWord *)bsearch(&key, keywords,
		       sizeof(keywords)/sizeof(keywords[0]), 
		       sizeof(keywords[0]), kwstrcmp);

  // If it is in the token table, return the indicated token type:
  if (entry)
    return entry->tokValue;

  return tk_Ident;
}

AMlexer::AMlexer(std::istream& _in, const std::string& origin)
  : UCSLexer(_in, origin)
{
}

#define BAD_TOKEN EOF
int
AMlexer::amlex(ParseType *lvalp)
{
  ucs4_t c;

 startOver:
  thisToken.erase();
  nDigits = 0;			// until otherwise proven
  radix = 10;			// until otherwise proven

  c = getChar();

  switch (c) {
  case '/':			// Possible comment start, else divide
    c = getChar();
    if (c == '/') {
      if (slurpCxxComment() == false)
	return EOF;
      goto startOver;


    } 
    if (c == '*') {
      if (slurpCComment() == false)
	return EOF;
      goto startOver;

    }
    ungetChar(c);
    c = '/';

    lvalp->tok = LToken(here, thisToken);
    here.updateWith(thisToken);

    // FIX: Malformed token
    return BAD_TOKEN;
 
  case ' ':			// White space
  case '\t':
  case '\r':
  case '\n':
    here.updateWith(thisToken);
    goto startOver;

  case '{':
    {
      here.updateWith(thisToken);
      thisToken.clear();

      LexLoc codeStart = here;

      size_t curlyDepth = 1;
      ParseType tmp;
      std::string theCode;

      // This code originally called the lexer recursively, with the
      // result that there were a lot of tokens recognized by the
      // lexer that were completely unneeded and undesired. The reason
      // for that horrible kludge was to get comment processing for
      // free, but in hindsight the right thing to do here is just
      // call the appropriate versions of slurpComment():

      while (curlyDepth > 0) {
	c = getChar();

	if (c == EOF)
	  break;

	if (c == '{') curlyDepth++;
	if (c == '}') {
	  curlyDepth--;
	  if (curlyDepth == 0) {
	    // Back it out of thisToken temporarily, so that we can
	    // capture theCode without it:
	    ungetChar(c);

	    theCode = thisToken;

	    c = getChar();
	    break;
	  }
	}

	if (c == '/') {
	  /* Might be looking at a comment. Need to check. */
	  c = getChar();
	  if (c == '/') {
	    bool more = slurpCxxComment();
	    here = codeStart;
	    if (!more)
	      goto got_eof;
	  }
	  else if (c == '*') {
	    bool more = slurpCComment();
	    here = codeStart;
	    if (!more)
	      goto got_eof;
	  }
	  else
	    ungetChar(c);
	}

	continue;

      got_eof:
	theCode = thisToken;
	c = EOF;
	curlyDepth = 0;
	break;
      }

      if (c == EOF)
	ReportParseError(here,
			 "End of file in code fragment starting here.\n");

      here.updateWith(thisToken);
      lvalp->tok = LToken(codeStart, theCode);
      return tk_CodeFragment;
    }

  case '=':
  case '|':
  case ';':
  case '*':
  case '+':
  case '?':
  case '(':
  case ')':
    goto single_character_token;

  case '"':
    {
      do {
	c = getChar();

	if (c == '\\')
	  (void) getChar();	// just ignore it -- will validate later

      } while (c != '"' && c != EOF);

      if (!validateString())
	return BAD_TOKEN;

      LexLoc tokStart = here;
      here.updateWith(thisToken);
      lvalp->tok = LToken(here, thisToken);
      return tk_StringLiteral;
    }

  case '%':
    goto identifier;

  case EOF:
    return EOF;

  default:
    if (validIdentStart(c))
      goto identifier;

    lvalp->tok = LToken(here, thisToken);
    here.updateWith(thisToken);

    // FIX: Malformed token
    return BAD_TOKEN;
  }

 single_character_token:
  lvalp->tok = LToken(here, thisToken);
  here.updateWith(thisToken);
  return c;

 identifier:
  do {
    c = getChar();
  } while (validIdentContinue(c));
  ungetChar(c);

  lvalp->tok = LToken(here, thisToken);
  here.updateWith(thisToken);
  return kwCheck(thisToken.c_str());
}
