/*
 * Copyright (c) 2016 Masayoshi Mizutani <mizutani@sfc.wide.ad.jp> All
 * rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "./fixtures.hpp"

TEST_F(ModuleTesterData1, UDP_packet) {
  const pm::Property* p;
  p = get_property(8);   // # packet #9

  EXPECT_TRUE(p->has_value("UDP.src_port"));
  EXPECT_TRUE(p->has_value("UDP.dst_port"));
  EXPECT_TRUE(p->has_value("UDP.length"));
  EXPECT_TRUE(p->has_value("UDP.chksum"));
  EXPECT_TRUE(p->has_value("UDP.hdr.length"));
  EXPECT_TRUE(p->has_value("UDP.hdr.chksum"));

  EXPECT_EQ(53805u,  p->value("UDP.src_port").uint());
  EXPECT_EQ(443u,    p->value("UDP.dst_port").uint());
  EXPECT_EQ(1358u,   p->value("UDP.length").uint());
  EXPECT_EQ(0x410cu, p->value("UDP.chksum").uint());
  EXPECT_EQ(1358u,   p->value("UDP.hdr.length").uint());
  EXPECT_EQ(0x410cu, p->value("UDP.hdr.chksum").uint());
}

