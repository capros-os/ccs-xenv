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
#include "ofBinaryStream.hxx"

using namespace std;
using namespace sherpa;

ofBinaryStream::ofBinaryStream()
  : oBinaryStream(new std::filebuf)
{
}

ofBinaryStream::ofBinaryStream(const char *filename, ios_base::openmode mode)
  : oBinaryStream(new std::filebuf)
{
  ((std::filebuf *)rdbuf())->open(filename, mode);
}

ofBinaryStream::~ofBinaryStream()
{
  std::filebuf *fb = (std::filebuf *) rdbuf(0);

  if (fb) {
    if (fb->is_open())
      fb->close();
    delete fb;
  }
}

void
ofBinaryStream::open(const char *filename, ios_base::openmode mode)
{
  std::filebuf *fb = (std::filebuf *) rdbuf();

  if (fb) {
    if (fb->is_open())
      fb->close();
    fb->open(filename, mode);
    seekp(0);
  }
}

void
ofBinaryStream::close()
{
  std::filebuf *fb = (std::filebuf *) rdbuf();

  if (fb) {
    if (fb->is_open())
      fb->close();
  }
}
