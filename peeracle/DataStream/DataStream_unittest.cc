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

#include <fstream>
#include "third_party/webrtc/testing/gtest/include/gtest/gtest.h"
#include "peeracle/DataStream/FileDataStream.h"
#include "peeracle/DataStream/MemoryDataStream.h"
#include "peeracle/Utils/RandomGenerator.h"

namespace peeracle {

/*typedef ::testing::Types<int8_t, uint8_t, int16_t, uint16_t, int32_t,
  uint32_t, float, double> DataStreamTypes;*/
typedef ::testing::Types<int8_t> DataStreamTypes;
TYPED_TEST_CASE(DataStreamTest, DataStreamTypes);

template <typename T>
class DataStreamTest
  : public ::testing::Test {
 protected:
  virtual void SetUp() {
    RandomGenerator rng;

    EXPECT_TRUE(rng.Init(time(NULL)));
    rng.Generate(&_randValueA, sizeof(_randValueA));
    rng.Generate(&_randValueB, sizeof(_randValueB));

    _ds = new peeracle::MemoryDataStream(_dsInit);
  }

  void TEST_WRITEVALUE(T value) {
    std::streamsize oldpos;
    std::streamsize newpos;
    std::streamsize len = 800;

    oldpos = this->_ds->tell();
    len = this->_ds->write(value);
    newpos = this->_ds->tell();
    EXPECT_EQ(sizeof(T), len);
    EXPECT_EQ(oldpos + sizeof(T), newpos);
  }

  void TEST_READVALUE(T *value) {
    std::streamsize oldpos;
    std::streamsize newpos;
    std::streamsize len = 800;

    oldpos = this->_ds->tell();
    len = this->_ds->read(value);
    newpos = this->_ds->tell();
    EXPECT_EQ(sizeof(T), len);
    EXPECT_EQ(oldpos + sizeof(T), newpos);
  }

  void TEST_READVALUE_FAIL(T *value) {
    T original = *value;
    std::streamsize oldpos;
    std::streamsize newpos;
    std::streamsize len = 800;

    oldpos = this->_ds->tell();
    len = this->_ds->read(value);
    newpos = this->_ds->tell();
    ASSERT_EQ(-1, len);
    EXPECT_EQ(original, *value);
    EXPECT_EQ(oldpos, newpos);
  }

  void TEST_SEEK(std::streamsize position) {
    std::streamsize oldpos;
    std::streamsize newpos;
    std::streamsize result;

    oldpos = this->_ds->tell();
    result = this->_ds->seek(-1);
    newpos = this->_ds->tell();
    EXPECT_EQ(-1, result);
    EXPECT_EQ(oldpos, newpos);

    oldpos = this->_ds->tell();
    result = this->_ds->seek(this->_ds->length() * 2);
    newpos = this->_ds->tell();
    EXPECT_EQ(-1, result);
    EXPECT_EQ(oldpos, newpos);

    oldpos = this->_ds->tell();
    result = this->_ds->seek(position);
    newpos = this->_ds->tell();
    EXPECT_EQ(position, result);
    EXPECT_EQ(newpos, result);
  }

  void TEST_GETBYTES(uint8_t *buffer, std::streamsize length) {
    std::streamsize result = this->_ds->read(reinterpret_cast<char*>(buffer),
                                             length);
    EXPECT_EQ(this->_ds->length(), result);
  }

  virtual void TearDown() {
    delete _ds;
  }

  unsigned int _seed;

  T _randValueA;
  T _randValueB;

  peeracle::MemoryDataStream *_ds;
  peeracle::DataStreamInit _dsInit;
};

TYPED_TEST(DataStreamTest, Write) {
  TypeParam valueA = this->_randValueA;

  this->TEST_READVALUE_FAIL(&valueA);
  this->TEST_WRITEVALUE(valueA);
  this->TEST_SEEK(0);

  valueA = this->_randValueA - 1;
  this->TEST_READVALUE(&valueA);
  EXPECT_EQ(this->_randValueA, valueA);
}

TYPED_TEST(DataStreamTest, DoubleWrite) {
  TypeParam valueA = this->_randValueA;
  TypeParam valueB = this->_randValueB;

  this->TEST_READVALUE_FAIL(&valueA);
  this->TEST_WRITEVALUE(valueA);
  this->TEST_WRITEVALUE(valueB);
  this->TEST_SEEK(0);

  valueA = this->_randValueA - 1;
  valueB = this->_randValueB - 1;

  this->TEST_READVALUE(&valueA);
  EXPECT_EQ(this->_randValueA, valueA);

  this->TEST_READVALUE(&valueB);
  EXPECT_EQ(this->_randValueB, valueB);

  this->TEST_SEEK(0);

  this->TEST_READVALUE(&valueA);
  EXPECT_EQ(this->_randValueA, valueA);

  this->TEST_SEEK(0);

  this->TEST_READVALUE(&valueA);
  EXPECT_EQ(this->_randValueA, valueA);
}

}  // namespace peeracle
