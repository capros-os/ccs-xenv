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

#include <stdint.h>
#include <dirent.h>

#include <string>
#include <sstream>

#include "AstInfo.hxx"

ChildNode::~ChildNode()
{
}

AstInfo::AstInfo(DeclType _dt, const sherpa::LToken& _nm)
{
  nm = _nm;
  printName = _nm.str;
  dt = _dt;
  members = 0;
  children = new sherpa::CVector<ChildNode *>;

  if (dt == dt_group)
    printName = "{" + printName + "}";
}

AstInfo::AstInfo(DeclType _dt, const sherpa::LToken& _nm,
		 const sherpa::LToken& _printName)
{
  nm = _nm;
  printName = _printName.str;
  dt = _dt;
  members = 0;
  children = new sherpa::CVector<ChildNode *>;
}

AstInfo::~AstInfo()
{
  children = 0;
  members = 0;
}

std::string
AstInfo::tagName() const
{
  return (((dt == dt_group) ? "agt_" : "at_") + nm.str);
}

std::string
AstInfo::GenerateGroupName()
{
  static unsigned groupCounter = 0;

  std::ostringstream nm;

  nm << "_AnonGroup" << groupCounter;
  groupCounter++;

  return nm.str();
}
