#ifndef LIBSHERPA_BITSET_HXX
#define LIBSHERPA_BITSET_HXX

/*
 * Copyright (c) 2007, The EROS Group, LLC.
 * All rights reserved.
 * 
 * This software was developed to support the EROS secure operating
 * system project (http://www.eros-os.org). The latest version of
 * the OpenCM software can be found at http://www.opencm.org.
 * 
 * Redistribution and use in source and binary forms, with or
 * without modification, are permitted provided that the following
 * conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 * 
 * 3. Neither the name of the The EROS Group, LLC nor the name of
 *    Johns Hopkins University, nor the names of its contributors
 *    may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

namespace sherpa {
  class BitSet {
    uint64_t bits;
  public:
    struct BoolConversionSupport {
      int dummy;
    };

    BitSet()
    {
      bits = 0;
    }

    BitSet(uint64_t u)
    {
      bits = u;
    }

    BitSet(const BitSet& that)
    {
      bits = that.bits;
    }

    BitSet operator&(const BitSet& that) const // bitwise and
    {
      return BitSet(bits & that.bits);
    }
    BitSet operator|(const BitSet& that) const // bitwise or
    {
      return BitSet(bits | that.bits);
    }
    BitSet operator+(const BitSet& that) const // set sum
    {
      return BitSet(bits | that.bits);
    }
    BitSet operator-(const BitSet& that) const // set difference
    {
      return BitSet(bits & ~that.bits);
    }
    BitSet operator~() const		// bitwise invert
    {
      return BitSet(~bits);
    }

    BitSet& operator=(const BitSet& that) // assignment
    {
      bits = that.bits;
      return *this;
    }

    BitSet& operator&=(const BitSet& that) // bitwise and
    {
      bits &= that.bits;
      return *this;
    }
    BitSet& operator|=(const BitSet& that) // bitwise or
    {
      bits |= that.bits;
      return *this;
    }
    BitSet& operator+=(const BitSet& that) // set sum
    {
      bits |= that.bits;
      return *this;
    }
    BitSet& operator-=(const BitSet& that) // set difference
    {
      bits &= ~that.bits;
      return *this;
    }

    bool operator==(const BitSet& that)
    {
      return bits == that.bits;
    }
    bool operator!=(const BitSet& that)
    {
      return bits != that.bits;
    }
    bool operator<=(const BitSet& that);
    {
      return (bits & that.bits) == bits;
    }
    bool operator>=(const BitSet& that);
    {
      return (bits & that.bits) == that.bits;
    }
    bool operator<(const BitSet& that);
    {
      return (*this <= that) && (*this != that);
    }
    bool operator>(const BitSet& that);
    {
      return (*this >= that) && (*this != that);
    }

    /// Sleazy support for if(BitSet):
    inline operator int BoolConversionSupport::* () const
    {
      return bits ? &BoolConversionSupport::dummy : 0;
    }
  }
} /* namespace sherpa */
// Local Variables:
// mode:c++
// End:

#endif /* LIBSHERPA_BITSET_HXX */
