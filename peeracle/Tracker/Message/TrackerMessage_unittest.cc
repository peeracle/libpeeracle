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

TEST_F(TrackerMessageTest, SerializeHello) {
  int type;
  std::string client;
  int protocol;
  unsigned char buffer[18];

  /*
   * Hello message format
   * --------------------
   *
   * Numbers must be in BIG ENDIAN
   *
   * Message type :
   * 0x00, 0x01, --> 2 bytes, short and not int
   *
   * There comes the client name, terminated with a \0 :
   * 0x6C, 0x69, 0x62, 0x70, 0x65, 0x65, -> 'l', 'i', 'b', 'p', 'e', 'e'
   * 0x72, 0x61, 0x63, 0x6C, 0x65, 0x00, -> 'r', 'a', 'c', 'l', 'e', '\0'
   *
   * Protocol version :
   * 0x00, 0x00, 0x00, 0x01 --> 4 bytes, int
   */
  unsigned char expected[] = { 0x00, 0x01,
                               0x6C, 0x69, 0x62, 0x70, 0x65, 0x65,
                               0x72, 0x61, 0x63, 0x6C, 0x65, 0x00,
                               0x00, 0x00, 0x00, 0x01 };

  TrackerMessage *msg = new TrackerMessage();

  msg->set("type", TrackerMessage::kHello);
  msg->set("client", "libpeeracle");
  msg->set("protocol", 1);

  msg->get("type", &type, TrackerMessage::kKeepAlive);
  msg->get("client", &client, "undefined");
  msg->get("protocol", &protocol, 0);

  EXPECT_EQ(TrackerMessage::kHello, type);
  EXPECT_EQ("libpeeracle", client);
  EXPECT_EQ(1, protocol);

  /*msg->serialize(buffer, sizeof(buffer));
  for (int i = 0; i < sizeof(expected); ++i) {
    EXPECT_EQ(expected[i], buffer[i]);
  }*/

  delete msg;
}

TEST_F(TrackerMessageTest, UnserializeHello) {
  int type;
  std::string client;
  int protocol;
  unsigned char buffer[] = { 0x00, 0x01,
                             0x6C, 0x69, 0x62, 0x70, 0x65, 0x65,
                             0x72, 0x61, 0x63, 0x6C, 0x65, 0x00,
                             0x00, 0x00, 0x00, 0x01 };

  TrackerMessage *msg = new TrackerMessage();

  // msg->unserialize(buffer, sizeof(buffer));

  msg->get("type", &type, TrackerMessage::kKeepAlive);
  msg->get("client", &client, "undefined");
  msg->get("protocol", &protocol, 0);

  EXPECT_EQ(TrackerMessage::kHello, type);
  EXPECT_EQ("libpeeracle", client);
  EXPECT_EQ(1, protocol);

  // EXPECT_EQ(sizeof(buffer), msg->getByteLength());

  delete msg;
}

}  // namespace peeracle
