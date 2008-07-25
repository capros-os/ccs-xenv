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
#include <libsherpa/oBinaryStream.hxx>

using namespace std;
using namespace sherpa;

void
oBinaryStream::setByteOrder(bs_base::Endian _byteOrder)
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
oBinaryStream::align(size_t off)
{
  while (offset % off)
    putByte(0);
}

oBinaryStream& 
oBinaryStream::operator<<(uint16_t val)
{
  align(2);

  if (byteOrder == bs_base::LittleEndian) {
    putByte(val & 0xffu);
    putByte((val >> 8) & 0xffu);
  }
  else {
    putByte((val >> 8) & 0xffu);
    putByte(val & 0xffu);
  }
  return *this;
}

oBinaryStream& 
oBinaryStream::operator<<(uint32_t val)
{
  align(4);

  if (byteOrder == bs_base::LittleEndian) {
    putByte(val & 0xffu);
    putByte((val >> 8) & 0xffu);
    putByte((val >> 16) & 0xffu);
    putByte((val >> 24) & 0xffu);
  }
  else {
    putByte((val >> 24) & 0xffu);
    putByte((val >> 16) & 0xffu);
    putByte((val >> 8) & 0xffu);
    putByte(val & 0xffu);
  }
  return *this;
}

oBinaryStream& 
oBinaryStream::operator<<(uint64_t val)
{
  align(8);

  if (byteOrder == bs_base::LittleEndian) {
    putByte(val & 0xffu);
    putByte((val >> 8) & 0xffu);
    putByte((val >> 16) & 0xffu);
    putByte((val >> 24) & 0xffu);
    putByte((val >> 32) & 0xffu);
    putByte((val >> 40) & 0xffu);
    putByte((val >> 48) & 0xffu);
    putByte((val >> 56) & 0xffu);
  }
  else {
    putByte((val >> 56) & 0xffu);
    putByte((val >> 48) & 0xffu);
    putByte((val >> 40) & 0xffu);
    putByte((val >> 32) & 0xffu);
    putByte((val >> 24) & 0xffu);
    putByte((val >> 16) & 0xffu);
    putByte((val >> 8) & 0xffu);
    putByte(val & 0xffu);
  }
  return *this;
}
