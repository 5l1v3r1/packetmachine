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

TEST_F(ModuleTesterData1, TCP_packet) {
  const pm::Property* p;
  p = get_property(4);   // # packet #5

  EXPECT_TRUE(p->has_value("TCP.src_port"));
  EXPECT_TRUE(p->has_value("TCP.dst_port"));
  EXPECT_TRUE(p->has_value("TCP.hdr.seq"));
  EXPECT_TRUE(p->has_value("TCP.hdr.ack"));
  EXPECT_TRUE(p->has_value("TCP.hdr.offset"));
  EXPECT_TRUE(p->has_value("TCP.hdr.flags"));
  EXPECT_TRUE(p->has_value("TCP.hdr.window"));
  EXPECT_TRUE(p->has_value("TCP.hdr.chksum"));
  EXPECT_TRUE(p->has_value("TCP.hdr.urgptr"));
  EXPECT_TRUE(p->has_value("TCP.optdata"));
  EXPECT_TRUE(p->has_value("TCP.segment"));

  // Flags
  EXPECT_TRUE(p->has_value("TCP.hdr.flag_fin"));
  EXPECT_TRUE(p->has_value("TCP.hdr.flag_syn"));
  EXPECT_TRUE(p->has_value("TCP.hdr.flag_rst"));
  EXPECT_TRUE(p->has_value("TCP.hdr.flag_push"));
  EXPECT_TRUE(p->has_value("TCP.hdr.flag_ack"));
  EXPECT_TRUE(p->has_value("TCP.hdr.flag_urg"));
  EXPECT_TRUE(p->has_value("TCP.hdr.flag_ece"));
  EXPECT_TRUE(p->has_value("TCP.hdr.flag_cwr"));

  // TCP header values
  EXPECT_EQ(443u,         p->value("TCP.src_port").uint());
  EXPECT_EQ(61301u,       p->value("TCP.dst_port").uint());
  EXPECT_EQ(0x310f035eu,  p->value("TCP.hdr.seq").uint());
  EXPECT_EQ(0xf597c00au,  p->value("TCP.hdr.ack").uint());
  EXPECT_EQ(32u,          p->value("TCP.hdr.offset").uint());
  EXPECT_EQ(0x08u|0x10u,  p->value("TCP.hdr.flags").uint());  // PUSH|ACK
  EXPECT_EQ(66u,          p->value("TCP.hdr.window").uint());
  EXPECT_EQ(0xb820u,      p->value("TCP.hdr.chksum").uint());
  EXPECT_EQ(0u,           p->value("TCP.hdr.urgptr").uint());

  EXPECT_EQ(0u, p->value("TCP.hdr.flag_fin").uint());
  EXPECT_EQ(0u, p->value("TCP.hdr.flag_syn").uint());
  EXPECT_EQ(0u, p->value("TCP.hdr.flag_rst").uint());
  EXPECT_LT(0u, p->value("TCP.hdr.flag_push").uint());
  EXPECT_LT(0u, p->value("TCP.hdr.flag_ack").uint());
  EXPECT_EQ(0u, p->value("TCP.hdr.flag_urg").uint());
  EXPECT_EQ(0u, p->value("TCP.hdr.flag_ece").uint());
  EXPECT_EQ(0u, p->value("TCP.hdr.flag_cwr").uint());

  size_t optlen, seglen;
  const pm::byte_t *opt = p->value("TCP.optdata").raw(&optlen);
  EXPECT_EQ(12u, optlen);
  EXPECT_EQ(0x01u, opt[0]);  // NOP

  const pm::byte_t *seg = p->value("TCP.segment").raw(&seglen);
  EXPECT_EQ(1045u, seglen);
  EXPECT_EQ(0x17u, seg[0]);  // SSL Content Type: Application Data
}

