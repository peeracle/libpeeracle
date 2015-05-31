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

#include "third_party/googletest/gtest/include/gtest/gtest.h"
#include "peeracle/Hash/Crc32Hash.h"

namespace peeracle {

namespace Hash {

class Crc32HashTest : public testing::Test {
 protected:
  virtual void SetUp() {
    hash_ = new Crc32Hash();
  }

  virtual void TearDown() {
    delete hash_;
  }

  Crc32Hash *hash_;
};

TEST_F(Crc32HashTest, EmptyCheck) {
  unsigned char *src = 0;
  unsigned char result[4] = { 0, 0, 0, 0 };

  hash_->final(result);

  EXPECT_EQ(result[0], 0);
  EXPECT_EQ(result[1], 0);
  EXPECT_EQ(result[2], 0);
  EXPECT_EQ(result[3], 0);

  hash_->update(src, 0);
  hash_->final(result);

  EXPECT_EQ(result[0], 0);
  EXPECT_EQ(result[1], 0);
  EXPECT_EQ(result[2], 0);
  EXPECT_EQ(result[3], 0);

  hash_->update(src, 12);
  hash_->final(result);

  EXPECT_EQ(result[0], 0);
  EXPECT_EQ(result[1], 0);
  EXPECT_EQ(result[2], 0);
  EXPECT_EQ(result[3], 0);

  hash_->update(src, -10);
  hash_->final(result);

  EXPECT_EQ(result[0], 0);
  EXPECT_EQ(result[1], 0);
  EXPECT_EQ(result[2], 0);
  EXPECT_EQ(result[3], 0);

  hash_->init();
  hash_->final(result);

  EXPECT_EQ(result[0], 0);
  EXPECT_EQ(result[1], 0);
  EXPECT_EQ(result[2], 0);
  EXPECT_EQ(result[3], 0);

  hash_->init();
  hash_->update(src, 0);
  hash_->final(result);

  EXPECT_EQ(result[0], 0);
  EXPECT_EQ(result[1], 0);
  EXPECT_EQ(result[2], 0);
  EXPECT_EQ(result[3], 0);

  hash_->update(src, 12);
  hash_->final(result);

  EXPECT_EQ(result[0], 0);
  EXPECT_EQ(result[1], 0);
  EXPECT_EQ(result[2], 0);
  EXPECT_EQ(result[3], 0);

  hash_->update(src, -10);
  hash_->final(result);

  EXPECT_EQ(result[0], 0);
  EXPECT_EQ(result[1], 0);
  EXPECT_EQ(result[2], 0);
  EXPECT_EQ(result[3], 0);

  hash_->final(result);

  EXPECT_EQ(result[0], 0);
  EXPECT_EQ(result[1], 0);
  EXPECT_EQ(result[2], 0);
  EXPECT_EQ(result[3], 0);
}

TEST_F(Crc32HashTest, HashPeeracleStr) {
  const unsigned char srcA[] = { 0x50, 0x65, 0x65, 0x72,
                                 0x61, 0x63, 0x6C, 0x65 };
  const unsigned char resA[] = { 0x0F, 0x3A, 0x36, 0xC8 };
  unsigned char result[4];

  hash_->init();
  hash_->update(srcA, 8);
  hash_->final(result);

  EXPECT_EQ(resA[0], result[0]);
  EXPECT_EQ(resA[1], result[1]);
  EXPECT_EQ(resA[2], result[2]);
  EXPECT_EQ(resA[3], result[3]);

  hash_->final(result);

  EXPECT_EQ(resA[0], result[0]);
  EXPECT_EQ(resA[1], result[1]);
  EXPECT_EQ(resA[2], result[2]);
  EXPECT_EQ(resA[3], result[3]);

  hash_->update(0, 0);
  hash_->final(result);

  EXPECT_EQ(resA[0], result[0]);
  EXPECT_EQ(resA[1], result[1]);
  EXPECT_EQ(resA[2], result[2]);
  EXPECT_EQ(resA[3], result[3]);

  hash_->init();
  hash_->final(result);

  EXPECT_EQ(0, result[0]);
  EXPECT_EQ(0, result[1]);
  EXPECT_EQ(0, result[2]);
  EXPECT_EQ(0, result[3]);
}

TEST_F(Crc32HashTest, HashPeeracleStrTwice) {
  const unsigned char srcA[] = { 0x50, 0x65, 0x65, 0x72,
                                 0x61, 0x63, 0x6C, 0x65 };
  const unsigned char resA[] = { 0x0F, 0x3A, 0x36, 0xC8 };
  const unsigned char resB[] = { 0x4A, 0x7B, 0x49, 0x38 };
  unsigned char result[4];

  hash_->init();
  hash_->update(srcA, 8);
  hash_->final(result);

  EXPECT_EQ(resA[0], result[0]);
  EXPECT_EQ(resA[1], result[1]);
  EXPECT_EQ(resA[2], result[2]);
  EXPECT_EQ(resA[3], result[3]);

  hash_->final(result);

  EXPECT_EQ(resA[0], result[0]);
  EXPECT_EQ(resA[1], result[1]);
  EXPECT_EQ(resA[2], result[2]);
  EXPECT_EQ(resA[3], result[3]);

  hash_->update(srcA, 8);
  hash_->final(result);

  EXPECT_EQ(resB[0], result[0]);
  EXPECT_EQ(resB[1], result[1]);
  EXPECT_EQ(resB[2], result[2]);
  EXPECT_EQ(resB[3], result[3]);

  hash_->update(0, 0);
  hash_->final(result);

  EXPECT_EQ(resB[0], result[0]);
  EXPECT_EQ(resB[1], result[1]);
  EXPECT_EQ(resB[2], result[2]);
  EXPECT_EQ(resB[3], result[3]);
}

TEST_F(Crc32HashTest, CallChecksum) {
  const unsigned char srcA[] = { 0x50, 0x65, 0x65, 0x72,
                                 0x61, 0x63, 0x6C, 0x65 };
  const unsigned char resB[] = { 0x4A, 0x7B, 0x49, 0x38 };
  unsigned char result[4];

  hash_->checksum(0, 8, 0);
  hash_->checksum(srcA, 8, 0);
  hash_->checksum(srcA, 8, result);

  EXPECT_EQ(resB[0], result[0]);
  EXPECT_EQ(resB[1], result[1]);
  EXPECT_EQ(resB[2], result[2]);
  EXPECT_EQ(resB[3], result[3]);

  hash_->checksum(srcA, 8, result);

  EXPECT_EQ(resB[0], result[0]);
  EXPECT_EQ(resB[1], result[1]);
  EXPECT_EQ(resB[2], result[2]);
  EXPECT_EQ(resB[3], result[3]);
}

}  // namespace Hash

}  // namespace peeracle
