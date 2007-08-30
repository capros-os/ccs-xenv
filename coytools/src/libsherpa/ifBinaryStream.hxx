#ifndef LIBSHERPA_IFBINARYSTREAM_HXX
#define LIBSHERPA_IFBINARYSTREAM_HXX

/**************************************************************************
 *
 * Copyright (C) 2007, The EROS Group, LLC. 
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

#include <streambuf>
#include <fstream>
#include "bs_base.hxx"
#include "ByteString.hxx"
#include "iBinaryStream.hxx"

namespace sherpa {
  class ifBinaryStream : public iBinaryStream {
  public:
    explicit ifBinaryStream();
    explicit ifBinaryStream(const char *filename, std::ios_base::openmode);
    ~ifBinaryStream();

    void open(const char *filename, std::ios_base::openmode);
    void close();

    inline bool is_open()
    {
      return rdbuf() && ((std::filebuf *) rdbuf())->is_open();
    }
  };

} /* namespace sherpa */
#endif /* LIBSHERPA_IFBINARYSTREAM_HXX */
