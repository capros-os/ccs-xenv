#ifndef LIBSHERPA_IBINARYSTREAM_HXX
#define LIBSHERPA_IBINARYSTREAM_HXX

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
#include "ByteString.hxx"
#include "bs_base.hxx"

namespace sherpa {
  class iBinaryStream {
    bs_base::Endian byteOrder;

    std::streambuf *sb;

    void setByteOrder(bs_base::Endian _byteOrder);

  public:
    explicit iBinaryStream(std::streambuf *_sb = 0)
    {
      sb = _sb;
      setByteOrder(bs_base::HostEndian);
    }

    inline uint8_t getByte()
    {
      uint8_t b = sb->sbumpc();
      return b;
    }

    inline iBinaryStream& read(size_t len, ByteString& bs)
    {
      bs.erase();
      bs.reserve(len);
      for (size_t i = 0; i < len; i++)
	bs.append(1, getByte());
      return *this;
    }

    inline iBinaryStream& read(size_t len, void *vp)
    {
      for (size_t i = 0; i < len; i++)
	((uint8_t *) vp)[i] = getByte();
      return *this;
    }

    inline iBinaryStream& readString(size_t len, std::string& s)
    {
      s.erase();
      s.reserve(len);
      for (size_t i = 0; i < len; i++)
	s.append(1, (char) getByte());
      return *this;
    }

    inline iBinaryStream& flush()
    {
      sb->pubsync();
      return *this;
    }

    inline std::streambuf *rdbuf() const
    {
      return sb;
    };

    inline std::streambuf *rdbuf(std::streambuf *_sb)
    {
      std::streambuf *oldsb = sb;
      sb = _sb;
      return oldsb;
    };

    std::streampos tellg();
    iBinaryStream& seekg(std::streampos pos);
    iBinaryStream& seekg(std::streamoff off, std::ios_base::seekdir dir);

    void align(size_t off);

    inline iBinaryStream& operator>>(bs_base::Endian _byteOrder)
    {
      setByteOrder(_byteOrder);
      return *this;
    }

    iBinaryStream& operator>>(uint8_t& val) 
    {
      val = getByte();
      return *this;
    }

    iBinaryStream& operator>>(uint16_t& val);
    iBinaryStream& operator>>(uint32_t& val);
    iBinaryStream& operator>>(uint64_t& val);

#if 0
    inline iBinaryStream& operator>>(const ByteString& bs)
    {
      return read(bs);
    }
#endif
  };

} /* namespace sherpa */
#endif /* LIBSHERPA_IBINARYSTREAM_HXX */
