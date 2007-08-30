#ifndef ASTINFO_HXX
#define ASTINFO_HXX

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

#include <libsherpa/LToken.hxx>
#include <libsherpa/CVector.hxx>

struct AstInfo;

struct ChildNode {
  sherpa::LToken tok;
  char ctype;			// one of ' ' '+' '*' '?'
  AstInfo *tokInfo;
  unsigned char *follow;

  ChildNode(const sherpa::LToken& _tok, char _ctype = ' ')
  {
    ctype = _ctype;
    tok = _tok;
    tokInfo = 0;
    follow = 0;
  }

  ~ChildNode();
};

typedef sherpa::CVector<ChildNode *> ChildVec;

enum DeclType {
  dt_leaf,			// leaf ast type
  dt_ast,			// normal ast type
  dt_group			// grouping pseudo-ast
};

struct AstInfo {
  size_t ndx;			// in final asts vector
  sherpa::LToken nm;
  std::string printName;

  DeclType dt;
  ChildVec *children;
  unsigned char *members;

  AstInfo(DeclType _dt, const sherpa::LToken& _nm);
  AstInfo(DeclType _dt, const sherpa::LToken& _nm, 
	  const sherpa::LToken& _printName);
  ~AstInfo();

  std::string tagName() const;

  static std::string GenerateGroupName();
};

#endif /* ASTINFO_HXX */
