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

#include <assert.h>
#include <string>

#include <unicode/uchar.h>

#include <libsherpa/utf8.hxx>
#include <libsherpa/LexLoc.hxx>

#include "Parser.hxx"

using namespace sherpa;

#include "Lexer.hxx"

#if 0
static bool
valid_char_printable(uint32_t ucs4)
{
  if (strchr("!#$%&`()*+-.,/:;<>=?@_|~^[]'", ucs4))
    return true;
  return false;
}
#endif

static bool
valid_ident_punct(uint32_t ucs4)
{
  if (strchr("_", ucs4))
    return true;
  return false;
}

static bool
valid_ident_start(uint32_t ucs4)
{
  return (u_hasBinaryProperty(ucs4,UCHAR_XID_START) || 
	  valid_ident_punct(ucs4));
}

static bool
valid_ident_continue(uint32_t ucs4)
{
  return (u_hasBinaryProperty(ucs4,UCHAR_XID_CONTINUE) ||
	  valid_ident_punct(ucs4));
}

static bool
valid_ifident_start(uint32_t ucs4)
{
  return (isalpha(ucs4) || ucs4 == '_');
  //  return (u_hasBinaryProperty(ucs4,UCHAR_XID_START));
}

static bool
valid_ifident_continue(uint32_t ucs4)
{
  return (isalpha(ucs4) || isdigit(ucs4) || ucs4 == '_' || ucs4 == '-');
  //  return (u_hasBinaryProperty(ucs4,UCHAR_XID_CONTINUE) ||
  //valid_ifident_punct(ucs4));
}

struct KeyWord {
  const char *nm;
  int  tokValue;
} keywords[] = {
  { "false",            tk_FALSE },
  { "not",              tk_NOT },
  { "true",             tk_TRUE },


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
Lexer::kwCheck(const char *s)
{
  if (ifIdentMode) {
    if (!valid_ifident_start(*s))
      return tk_Reserved;

    for (++s; *s; s++)
      if (!valid_ifident_continue(*s))
	return tk_Reserved;

    return tk_Ident;
  }

  KeyWord key = { s, 0 };
  KeyWord *entry = 
    (KeyWord *)bsearch(&key, keywords,
		       sizeof(keywords)/sizeof(keywords[0]), 
		       sizeof(keywords[0]), kwstrcmp);

  // If it is in the token table, return the indicated token type:
  if (entry)
    return entry->tokValue;

  // Otherwise, check for various reserved words:

  // Things starting with "__":
  if (s[0] == '_' && s[1] == '_') {
    if(!isRuntimeUoc)
      return tk_Reserved;
  }

  return tk_Ident;
}

void
Lexer::ReportParseError()
{
  errStream << here
	    << ": syntax error (via yyerror)" << '\n';
  num_errors++;
}
 
void
Lexer::ReportParseError(std::string msg)
{
  errStream << here
	    << ": "
	    << msg << std::endl;

  num_errors++;
}

void
Lexer::ReportParseWarning(std::string msg)
{
  errStream << here
	    << ": "
	    << msg << std::endl;
}

Lexer::Lexer(std::ostream& _err, std::istream& _in, 
		     sherpa::Path *inputPath)
  :here(inputPath, 1, 0), inStream(_in), errStream(_err)
{
  inStream.unsetf(std::ios_base::skipws);

  num_errors = 0;
  isRuntimeUoc = false;
  ifIdentMode = false;
  debug = false;
  putbackChar = -1;
}

long 
Lexer::digitValue(ucs4_t ucs4)
{
  long l = -1;

  if (ucs4 >= '0' && ucs4 <= '9')
    l = ucs4 - '0';
  if (ucs4 >= 'a' && ucs4 <= 'f')
    l = ucs4 - 'a' + 10;
  if (ucs4 >= 'A' && ucs4 <= 'F')
    l = ucs4 - 'A' + 10;

  if (l > radix)
    l = -1;
  return l;
}

ucs4_t
Lexer::getChar()
{
  char utf[8];
  unsigned char c = 0;

  long ucs4 = putbackChar;

  if (putbackChar != -1) {
    putbackChar = -1;
    utf8_encode(ucs4, utf);
    goto checkDigit;
  }

  memset(utf, 0, 8);

  utf[0] = inStream.get();
  c = utf[0];
  if (utf[0] == EOF)
    return EOF;

  if (c <= 127)
    goto done;

  utf[1] = inStream.get();
  if (utf[1] == EOF)
    return EOF;

  if (c <= 223)
    goto done;

  utf[2] = inStream.get();
  if (utf[2] == EOF)
    return EOF;

  if (c <= 239)
    goto done;

  utf[3] = inStream.get();
  if (utf[3] == EOF)
    return EOF;

  if (c <= 247)
    goto done;
 
  utf[4] = inStream.get();
  if (utf[4] == EOF)
    return EOF;

  if (c <= 251)
    goto done;

  utf[5] = inStream.get();
  if (utf[5] == EOF)
    return EOF;

 done:
  ucs4 = utf8_decode(utf, 0);
 checkDigit:
  thisToken += utf;

  if (digitValue(c) < radix)
    nDigits++;

  return ucs4;
}

void
Lexer::ungetChar(ucs4_t c)
{
  char utf[8];
  assert(putbackChar == -1);
  putbackChar = c;

  unsigned len = utf8_encode(c, utf);
  thisToken.erase( thisToken.length() - len);
}

#if 0
static bool
isCharDelimiter(ucs4_t c)
{
  switch (c) {
  case ' ':
  case '\t':
  case '\n':
  case '\r':
  case ')':
    return true;
  default:
    return false;
  }
}
#endif

#define BAD_TOKEN EOF
int
Lexer::lex(ParseType *lvalp)
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
    if (c != '/') {
      ungetChar(c);
      c = '/';
      goto single_char_token;
    }

    do {
      c = getChar();
    } while (c != '\n' && c != '\r');
    ungetChar(c);
    // FALL THROUGH INTO WHITESPACE HANDLING

  case ' ':			// White space
  case '\t':
  case '\r':
    here.updateWith(thisToken);
    goto startOver;

  case '\n':			// input is newline terminated

  case '(':
  case ')':

  case '=':			// assignment
  case ';':			// statement terminator

  case '+':			// Arithmetic operators. Note '/' handled
  case '*':			// above under comments
  case '-':
  case '%':

  single_char_token:
    lvalp->tok = LToken(here, thisToken);
    here.updateWith(thisToken);
    return c;

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
      lvalp->val = BigNum(thisToken);
      here.updateWith(thisToken);
      return tk_Int;
    }

  case EOF:
    return EOF;

  default:
    if (valid_ident_start(c))
      goto identifier;

    // FIX: Malformed token
    return BAD_TOKEN;
  }

 identifier:
  do {
    c = getChar();
  } while (valid_ident_continue(c));
  ungetChar(c);
  lvalp->tok = LToken(here, thisToken);
  here.updateWith(thisToken);
  return kwCheck(thisToken.c_str());
}
