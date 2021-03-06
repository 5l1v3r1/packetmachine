/*
 * Copyright (c) 2017 Masayoshi Mizutani <mizutani@sfc.wide.ad.jp> All
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

#include <unistd.h>
#include "./gtest/gtest.h"
#include "../src/packetmachine.hpp"

namespace machine_test {

TEST(Handler, ok) {
  pm::Machine *m = new pm::Machine();
  int count = 0;

  m->on("UDP", [&](const pm::Property& p) {
      count++;
    });

  m->add_pcapfile("./test/data1.pcap");
  m->loop();

  EXPECT_EQ(624, count);
  delete m;
}

TEST(Handler, deactivate) {
  pm::Machine *m = new pm::Machine();
  int count = 0;

  auto hdlr = m->on("UDP", [&](const pm::Property& p) {
      count++;
    });

  EXPECT_TRUE(hdlr.is_active());
  EXPECT_TRUE(hdlr.deactivate());
  EXPECT_FALSE(hdlr.deactivate());  // double deactivate
  EXPECT_FALSE(hdlr.is_active());

  m->add_pcapfile("./test/data1.pcap");
  m->loop();

  EXPECT_EQ(0, count);
  delete m;
}

TEST(Handler, reactivate) {
  pm::Machine *m = new pm::Machine();
  int count = 0;

  auto hdlr = m->on("UDP", [&](const pm::Property& p) {
      count++;
    });

  EXPECT_TRUE(hdlr.deactivate());
  EXPECT_TRUE(hdlr.activate());
  EXPECT_FALSE(hdlr.activate());  // double activate

  m->add_pcapfile("./test/data1.pcap");
  m->loop();

  EXPECT_EQ(624, count); 
  delete m;
}

TEST(Handler, destroy) {
  pm::Machine *m = new pm::Machine();
  int count = 0;
  auto hdlr = m->on("UDP", [&](const pm::Property& p) {
      count++;
    });

  EXPECT_TRUE(hdlr.destroy());
  EXPECT_FALSE(hdlr.is_active());
  EXPECT_FALSE(hdlr.activate());

  m->add_pcapfile("./test/data1.pcap");
  m->loop();

  EXPECT_EQ(0, count); 
  delete m;
}

TEST(Handler, clear) {
  pm::Machine *m = new pm::Machine();
  int count = 0;
  pm::Handler hdlr = m->on("UDP", [&](const pm::Property& p) {
      count++;
      if (count > 10) {
        hdlr.destroy();
      }
    });

  EXPECT_TRUE(hdlr.is_active());
  
  m->add_pcapfile("./test/data1.pcap");
  m->loop();

  EXPECT_FALSE(hdlr.is_active());
  EXPECT_FALSE(hdlr.activate());
  
  EXPECT_EQ(11, count); 
  delete m;
}

TEST(Handler, deactivate_async) {
  pm::Machine *m = new pm::Machine();
  int count = 0;
  pm::Handler hdlr = m->on("UDP", [&](const pm::Property& p) {
      count++;
    });

  m->add_pcapfile("./test/data1.pcap");
  m->start();
  usleep(10);
  hdlr.deactivate();
  m->join();

  EXPECT_FALSE(hdlr.is_active());
  EXPECT_GE(624, count); 
  delete m;
}

TEST(Handler, clear_async) {
  pm::Machine *m = new pm::Machine();
  int count = 0;
  pm::Handler hdlr = m->on("UDP", [&](const pm::Property& p) {
      count++;
    });

  m->add_pcapfile("./test/data1.pcap");
  m->start();
  usleep(1);
  hdlr.destroy();
  m->join();

  EXPECT_FALSE(hdlr.is_active());
  EXPECT_FALSE(hdlr.activate());
  EXPECT_GE(624, count); 
  delete m;
}


}   // namespace machine_test
