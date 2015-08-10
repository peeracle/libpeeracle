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

#include "third_party/webrtc/testing/gtest/include/gtest/gtest.h"
#include "TrackerClient.h"

namespace peeracle {

class TrackerClientTest : public testing::Test {
 protected:
  virtual void SetUp() {
    _client = new TrackerClient("ws://127.0.0.1:8080", NULL);
  }

  virtual void TearDown() {
    delete _client;
  }

  TrackerClient *_client;
};

TEST_F(TrackerClientTest, Connect) {
  bool ret;

  std::cout << "init" << std::endl;
  ret = _client->Init();
  EXPECT_TRUE(ret);

  std::cout << "conn" << std::endl;
  ret = _client->Connect();
  EXPECT_TRUE(ret);

  std::cout << "update" << std::endl;
  ret = _client->Update();
  EXPECT_TRUE(ret);
}

}  // namespace peeracle
