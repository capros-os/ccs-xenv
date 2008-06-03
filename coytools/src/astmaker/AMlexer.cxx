/* -*- Mode: c -*- */
/*
 * Copyright (C) 2007, The EROS Group, LLC.
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

AMlexer::AMlexer(std::istream& _in, GCPtr<Path> inputPath)
  : UCSLexer(_in, inputPath)
{
  percentIsIdentifier = true;
  outermostScope = true;
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
    goto single_char_token;
 
  case ' ':			// White space
  case '\t':
  case '\r':
  case '\n':
    if (outermostScope) {
      here.updateWith(thisToken);
      goto startOver;
    }

    lvalp->tok = LToken(here, thisToken);
    here.updateWith(thisToken);
    return tk_WhiteSpace;

  case '{':
    if (outermostScope) {
      percentIsIdentifier = false;
      outermostScope = false;

      here.updateWith(thisToken);

      LexLoc codeStart = here;

      size_t curlyDepth = 1;
      ParseType tmp;
      std::string theCode;

      do {
	int tok = amlex(&tmp);

	if (tok == '{')
	  curlyDepth++;
	else if (tok == '}')
	  curlyDepth--;

	if (curlyDepth != 0)
	  theCode.append(tmp.tok.str);

      } while (curlyDepth > 0);

      percentIsIdentifier = true;
      outermostScope = true;

      lvalp->tok = LToken(codeStart, theCode);
      return tk_CodeFragment;
    }
    else
      goto single_char_token;

  case '%':
    if (percentIsIdentifier)
      goto identifier;

  case ':':		// single character tokens
  case '<':
  case '>':
  case '=':
  case '-':
  case ',':
  case ';':
  case '.':
  case '(':
  case ')':
  case '[':
  case ']':
  case '}':
  case '*':
  case '+':
  case '|':
  case '?':

  single_char_token:
    lvalp->tok = LToken(here, thisToken);
    here.updateWith(thisToken);
    return c;

  case '"':			// String literal
    {
      do {
	c = getChar();

	if (c == '\\') 
	  (void) getChar();	// just ignore it -- will validate later

      }	while (c != '"');
      
      if (!validateString()) 
	return BAD_TOKEN;

      LexLoc tokStart = here;
      here.updateWith(thisToken);
      // lvalp->tok = LToken(here, thisToken.substr(1, thisToken.size()-2));
      lvalp->tok = LToken(here, thisToken);
      return tk_StringLiteral;
    }


 case '\'':
   {
     // Recall that we do not intend to PROCESS the character!
     do {
       c = getChar();
       if (c == '\\') 
	 (void) getChar();
     } while (c != '\'');

     LexLoc tokStart = here;
     here.updateWith(thisToken);
     // lvalp->tok = LToken(here, thisToken.substr(1, thisToken.size()-2));
     lvalp->tok = LToken(here, thisToken);
     return tk_CharLiteral;
   }
    // We do not (currently) accept character constants.

  case '0':			// Numbers
    {
      radix = 8;		// initial 0 -- until otherwise proven

      c = getChar();
      if (c == 'x' || c == 'X') {
	radix = 16;

	// 0x must be followed by digits. Check that here.

	c = getChar();
	ungetChar(c);

	if (digitValue(c) < 0)
	  return BAD_TOKEN;
      }
      else
	ungetChar(c);

      // FALL THROUGH
    }

  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9':
    {
      do {
	c = getChar();
      } while (digitValue(c) >= 0);
      ungetChar(c);

      /* If we were accepting floating literals, we would check for
	 decimal point here. */

      lvalp->tok = LToken(here, thisToken);
      here.updateWith(thisToken);
      return tk_IntegerLiteral;
    }

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

 identifier:
  do {
    c = getChar();
  } while (validIdentContinue(c));
  ungetChar(c);

  lvalp->tok = LToken(here, thisToken);
  here.updateWith(thisToken);
  return kwCheck(thisToken.c_str());
}
