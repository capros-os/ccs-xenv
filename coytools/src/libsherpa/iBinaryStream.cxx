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

#include "../config.h"
#include <libsherpa/iBinaryStream.hxx>

using namespace std;
using namespace sherpa;

void
iBinaryStream::setByteOrder(bs_base::Endian _byteOrder)
{
  byteOrder = _byteOrder;

  if (byteOrder == bs_base::HostEndian) {
    union {
      uint32_t u;
      char s[4];
    } bou;

    bou.u = 0x04030201;

    // byte order is host byte order until otherwise set:
    if (bou.s[0] == 0x01)
      byteOrder = bs_base::LittleEndian;
    else
      byteOrder = bs_base::BigEndian;
  }
}

void 
iBinaryStream::align(size_t off)
{
  while(offset % off)
    getByte();
}

iBinaryStream& 
iBinaryStream::operator>>(uint16_t& val)
{
  align(2);

  val = 0;
  if (byteOrder == bs_base::LittleEndian) {
    val += getByte();
    val += ((uint16_t) getByte()) << 8;
  }
  else {
    val += ((uint16_t) getByte()) << 8;
    val += getByte();
  }
  return *this;
}

iBinaryStream& 
iBinaryStream::operator>>(uint32_t& val)
{
  align(4);

  val = 0;
  if (byteOrder == bs_base::LittleEndian) {
    val += getByte();
    val += ((uint32_t) getByte()) << 8;
    val += ((uint32_t) getByte()) << 16;
    val += ((uint32_t) getByte()) << 24;
  }
  else {
    val += ((uint32_t) getByte()) << 24;
    val += ((uint32_t) getByte()) << 16;
    val += ((uint32_t) getByte()) << 8;
    val += getByte();
  }
  return *this;
}

iBinaryStream& 
iBinaryStream::operator>>(uint64_t& val)
{
  align(8);

  val = 0;
  if (byteOrder == bs_base::LittleEndian) {
    val += getByte();
    val += ((uint64_t) getByte()) << 8;
    val += ((uint64_t) getByte()) << 16;
    val += ((uint64_t) getByte()) << 24;
    val += ((uint64_t) getByte()) << 32;
    val += ((uint64_t) getByte()) << 40;
    val += ((uint64_t) getByte()) << 48;
    val += ((uint64_t) getByte()) << 56;
  }
  else {
    val += ((uint64_t) getByte()) << 56;
    val += ((uint64_t) getByte()) << 48;
    val += ((uint64_t) getByte()) << 40;
    val += ((uint64_t) getByte()) << 32;
    val += ((uint64_t) getByte()) << 24;
    val += ((uint64_t) getByte()) << 16;
    val += ((uint64_t) getByte()) << 8;
    val += getByte();
  }
  return *this;
}
