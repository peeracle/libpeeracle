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

#include "gtest/gtest.h"
#include "peeracle/Crypto/Crc32Crypto.h"

namespace peeracle {

namespace Crypto {

class Crc32CryptoTest : public testing::Test {
 protected:
  Crc32CryptoTest() : crypto_(NULL) {
  }

  virtual void SetUp() {
    crypto_ = new Crc32Crypto();
  }

  virtual void TearDown() {
  }

  Crc32Crypto *crypto_;
};

TEST(Crc32CryptoTest, init) {
  EXPECT_FALSE(true);
}

TEST(Crc32CryptoTest, update) {
  EXPECT_FALSE(true);
}

TEST(Crc32CryptoTest, finish) {
  EXPECT_FALSE(true);
}

TEST(Crc32CryptoTest, checksum) {
  EXPECT_FALSE(true);
}

}  // namespace Crypto

}  // namespace peeracle
