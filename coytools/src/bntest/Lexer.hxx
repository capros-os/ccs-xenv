#ifndef LEXER_HXX
#define LEXER_HXX

/*
 * Copyright (C) 2005, The EROS Group, LLC.
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

#include <iostream>

#include <libsherpa/Path.hxx>
#include "ParseType.hxx"

typedef long ucs4_t;

class Lexer {
  int nDigits;
  int radix;

public:
  sherpa::LexLoc here;
  int num_errors;
  bool debug;
  bool isRuntimeUoc;
  bool ifIdentMode;

  std::istream& inStream;
  std::ostream& errStream;

  std::string thisToken;

  ucs4_t putbackChar;		// -1 or UCS4

  long digitValue(ucs4_t);

  ucs4_t getChar();
  void ungetChar(ucs4_t);

  Lexer(std::ostream& _err, std::istream& _in, 
	    sherpa::Path *inputPath);

  void ReportParseError();
  void ReportParseError(std::string  /* msg */);
  void ReportParseWarning(std::string  /* msg */);

  inline void setDebug(bool showlex)
  {
    debug = (showlex ? true : false);
  }

  inline void setIfIdentMode(bool arg)
  {
    ifIdentMode = arg;
  }

  int lex(ParseType *yylvalp);

  int kwCheck(const char *s);

  ~Lexer() {}
};

#endif /* LEXER_HXX */

