#ifndef LIBSHERPA_LEXLOC_HXX
#define LIBSHERPA_LEXLOC_HXX

/**************************************************************************
 *
 * Copyright (C) 2000, 2001, 2002, 2003, 2004, 2005, 2006, The EROS
 *   Group, LLC. 
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

#include "Path.hxx"

namespace sherpa {

  struct LexLoc {
    GCPtr<Path> path;
    unsigned line;		// 0 indicates no real line
    unsigned offset;

    LexLoc()
    {
      this->path = 0;
      this->line = 0;
      this->offset = 0;
    }

    ~LexLoc()
    {
      path = 0;
    }

    LexLoc(GCPtr<Path> filePath, unsigned line, unsigned offset)
    {
      this->path = filePath;
      this->line = line;
      this->offset = offset;
    }

    LexLoc(const LexLoc& ll)
    {
      path = ll.path;
      line = ll.line;
      offset = ll.offset;
    }

    LexLoc& operator=(const LexLoc& ll)
    {
      path = ll.path;
      line = ll.line;
      offset = ll.offset;
      return *this;
    }

    std::string asString() const;
    std::string encode() const;

    static LexLoc decode(const std::string& s);
    static size_t skip(const std::string& s, size_t start);

    inline const char *c_str() const
    {
      return asString().c_str();
    }

    static LexLoc Unspecified;

    LexLoc operator+(size_t sz) const
    {
      return LexLoc(path, line, offset + sz);
    }

    void updateWith(const std::string& s);
  };

  inline
  std::ostream& operator<<(std::ostream& strm, const LexLoc& ll)
  {
    strm << ll.asString();
    return strm;
  }

}

#endif /* LIBSHERPA_LEXLOC_HXX */
