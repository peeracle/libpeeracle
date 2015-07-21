/*
 * Copyright (c) 2015 peeracle contributors
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <string>
#include <sstream>
#include "third_party/googletest/gtest/include/gtest/gtest.h"
#include "peeracle/Tracker/Message/TrackerMessage.h"

namespace peeracle {

class TrackerMessageTest : public testing::Test {
 protected:
  virtual void SetUp() {
  }

  virtual void TearDown() {
  }
};

TEST_F(TrackerMessageTest, GetNSet) {
  int version;
  std::string type;
  std::string hash;
  std::string empty;
  TrackerMessage *msg = new TrackerMessage();

  msg->set("type", "hello");
  msg->set("version", 130);
  msg->set("hash", "crc32");
  msg->set("iAmEmpty", "");

  msg->get("type", &type, "undefined");
  msg->get("version", &version, 0);
  msg->get("hash", &hash, "undefined");
  msg->get("iAmEmpty", &empty, "notEmpty");

  EXPECT_EQ("hello", type);
  EXPECT_EQ(130, version);
  EXPECT_EQ("crc32", hash);
  EXPECT_EQ("", empty);

  delete msg;
}

}  // namespace peeracle
