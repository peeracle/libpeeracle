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

TEST_F(TrackerMessageTest, GetNSetInteger) {
  int type;
  TrackerMessage *msg = new TrackerMessage();

  msg->set("type", TrackerMessage::kHello);
  msg->get("type", &type);
  EXPECT_EQ(type, TrackerMessage::kHello);

  delete msg;
}

TEST_F(TrackerMessageTest, GetNSetString) {
  std::string rev;
  std::stringstream strm;
  TrackerMessage *msg = new TrackerMessage();

  strm << "libpeeracle-" << LIBPEERACLE_REVISION;
  rev = strm.str();

  std::string resultStr;
  msg->set("client", rev);
  msg->get("client", &resultStr);
  EXPECT_EQ(rev, resultStr);

  delete msg;
}

TEST_F(TrackerMessageTest, GetNSetBoth) {
  int type;
  std::string rev;
  std::stringstream strm;
  TrackerMessage *msg = new TrackerMessage();

  strm << "libpeeracle-" << LIBPEERACLE_REVISION;
  rev = strm.str();

  msg->set("type", TrackerMessage::kHello);
  msg->get("type", &type);
  EXPECT_EQ(type, TrackerMessage::kHello);

  std::string resultStr;
  msg->set("client", rev);
  msg->get("client", &resultStr);
  EXPECT_EQ(rev, resultStr);

  type = TrackerMessage::kNone;
  msg->get("type", &type);
  EXPECT_EQ(type, TrackerMessage::kHello);

  resultStr = "";
  msg->get("client", &resultStr);
  EXPECT_EQ(rev, resultStr);

  delete msg;
}

}  // namespace peeracle
