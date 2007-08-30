#ifndef PARSETYPE_HXX
#define PARSETYPE_HXX

/**************************************************************************
 *
 * Copyright (C) 2004, 2005, 2006, Johns Hopkins University.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or
 * without modification, are permitted provided that the following
 * conditions are met:
 *
 *   - Redistributions of source code must contain the above 
 *     copyright notice, this list of conditions, and the following
 *     disclaimer. 
 *
 *   - Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions, and the following
 *     disclaimer in the documentation and/or other materials 
 *     provided with the distribution.
 *
 *   - Neither the names of the copyright holders nor the names of any
 *     of any contributors may be used to endorse or promote products
 *     derived from this software without specific prior written
 *     permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 **************************************************************************/

#include <libsherpa/Path.hxx>
#include <libsherpa/LToken.hxx>

#include "AstInfo.hxx"

#include <sstream>

struct FieldDecl {
  std::string name;
  std::string type;
} ;

struct ParseResult {
  sherpa::CVector<AstInfo *>     asts;

  std::string                    nmspace;

  std::ostringstream             copyright;
  std::ostringstream             construct;

  std::ostringstream             members;
  std::ostringstream             source;
  std::ostringstream             sourceTop;
  std::ostringstream             header;
  std::ostringstream             include;

  ParseResult()
  {
    asts = 0;
  }
};

struct ParseType {
  sherpa::LToken    tok;		/* a literal string from the
				 * tokenizer. Used for strings,
				 * characters, numerical values. */

  ChildNode *child;
  ChildVec  *children;

  ParseType()
  {
    child = 0;
    children = 0;
  }
};

#endif /* PARSETYPE_HXX */
