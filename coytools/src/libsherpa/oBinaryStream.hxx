#ifndef LIBSHERPA_OBINARYSTREAM_HXX
#define LIBSHERPA_OBINARYSTREAM_HXX

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
#include "bs_base.hxx"
#include "ByteString.hxx"

namespace sherpa {
  class oBinaryStream {
    bs_base::Endian byteOrder;

    void setByteOrder(bs_base::Endian _byteOrder);

    std::streambuf *sb;
  public:
    explicit oBinaryStream(std::streambuf *_sb = 0)
    {
      sb = _sb;
      setByteOrder(bs_base::HostEndian);
    }

    inline oBinaryStream& putByte(uint8_t b)
    {
      sb->sputc(b);
      return *this;
    }

    inline oBinaryStream& write(const ByteString& bs)
    {
      for (size_t i = 0; i < bs.size(); i++)
	putByte(bs[i]);
      return *this;
    }

    inline oBinaryStream& write(size_t len, const void *vp)
    {
      for (size_t i = 0; i < len; i++)
	putByte(((uint8_t *) vp)[i]);
      return *this;
    }

    inline oBinaryStream& flush()
    {
      sb->pubsync();
      return *this;
    }

    inline std::streambuf *rdbuf() const
    {
      return sb;
    };

    inline std::streambuf *rdbuf(std::streambuf *_newsbuf)
    {
      std::streambuf *oldsb = sb;
      sb = _newsbuf;
      return oldsb;
    };

    std::streampos tellp();
    oBinaryStream& seekp(std::streampos pos);
    oBinaryStream& seekp(std::streamoff off, std::ios_base::seekdir dir);

    void align(size_t off);

    inline oBinaryStream& operator<<(bs_base::Endian _byteOrder)
    {
      setByteOrder(_byteOrder);
      return *this;
    }

    oBinaryStream& operator<<(uint8_t val) 
    {
      return putByte(val);
    }

    oBinaryStream& operator<<(uint16_t val);
    oBinaryStream& operator<<(uint32_t val);
    oBinaryStream& operator<<(uint64_t val);

    /// @brief Emit string @em without terminating null:
    oBinaryStream& operator<<(const std::string& s)
    {
      for (size_t i = 0; i < s.size(); i++)
	putByte(s[i]);
      return *this;
    }

    inline oBinaryStream& operator<<(const ByteString& bs)
    {
      return write(bs);
    }
  };

} /* namespace sherpa */
#endif /* LIBSHERPA_OBINARYSTREAM_HXX */
