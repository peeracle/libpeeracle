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
#include <cstdlib>
#include "third_party/googletest/gtest/include/gtest/gtest.h"
#include "peeracle/DataSource/HttpDataSource.h"

#ifdef _MSC_VER
int rand_r(unsigned int *seed) {
	srand(*seed);
	return rand();
}
#endif

namespace peeracle {

namespace DataSource {

TEST(HttpDataSourceTestInvalid, CannotResolve) {
  bool result;
  unsigned int seed;
  HttpDataSource *ds;
  std::stringstream strm;
  strm << "http://";

  const char alphanum[] = "0123456789"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz";

  seed = (unsigned int) (time(NULL));
  for (size_t i = 0; i < 24; i++) {
    strm << alphanum[rand_r(&seed) % (sizeof(alphanum) - 1)];
  }

  ds = new HttpDataSource(strm.str());
  result = ds->open();
  EXPECT_EQ(false, result);
}

class HttpDataSourceTest
  : public ::testing::Test {
 protected:
  virtual void SetUp() {
  }

  virtual void TearDown() {
  }

  const std::string url_ = "http://out.dotstar.fr/media/tears_of_steel_" \
    "1920x856_4000K_192K_webm.peeracle";
};

TEST_F(HttpDataSourceTest, ReadFullRandomFile) {
  bool opened;
  std::streamsize result;
  HttpDataSource *ds = new HttpDataSource(url_);
  unsigned char data_[32] = { 0x50, 0x52, 0x43, 0x4c, 0x00, 0x00, 0x00, 0x02,
	  0x63, 0x72, 0x63, 0x33, 0x32, 0x00, 0x00, 0x0f,
	  0x42, 0x40, 0x00, 0x00, 0x00, 0x00, 0x12, 0x66,
	  0x26, 0x41, 0x00, 0x00, 0x00, 0x01, 0x77, 0x73 };
  unsigned char buffer[sizeof(data_)];

  opened = ds->open();
  EXPECT_EQ(true, opened);

  result = ds->read(buffer, sizeof(data_));
  EXPECT_EQ((std::streamsize) sizeof(data_), result);
  for (size_t i = 0; i < sizeof(data_); ++i) {
    EXPECT_EQ(data_[i], buffer[i]);
  }

  memset(buffer, 0, sizeof(buffer));
  result = ds->read(buffer, sizeof(data_));
  EXPECT_EQ((std::streamsize) 0, result);
  for (size_t i = 0; i < sizeof(data_); ++i) {
    EXPECT_EQ(0, buffer[i]);
  }

  ds->close();
  delete ds;
}

TEST_F(HttpDataSourceTest, ReadFullRandomFileTwice) {
  bool opened;
  std::streamsize result;
  HttpDataSource *ds = new HttpDataSource(url_);
  unsigned char data_[32] = { 0x50, 0x52, 0x43, 0x4c, 0x00, 0x00, 0x00, 0x02,
	  0x63, 0x72, 0x63, 0x33, 0x32, 0x00, 0x00, 0x0f,
	  0x42, 0x40, 0x00, 0x00, 0x00, 0x00, 0x12, 0x66,
	  0x26, 0x41, 0x00, 0x00, 0x00, 0x01, 0x77, 0x73 };
  unsigned char buffer[sizeof(data_)];

  opened = ds->open();
  EXPECT_EQ(true, opened);

  result = ds->read(buffer, sizeof(data_));
  EXPECT_EQ((std::streamsize) sizeof(data_), result);
  for (size_t i = 0; i < sizeof(data_); ++i) {
    EXPECT_EQ(data_[i], buffer[i]);
  }

  ds->close();

  memset(buffer, 0, sizeof(buffer));

  opened = ds->open();
  EXPECT_EQ(true, opened);

  result = ds->read(buffer, sizeof(data_));
  EXPECT_EQ((std::streamsize) sizeof(data_), result);
  for (size_t i = 0; i < sizeof(data_); ++i) {
    EXPECT_EQ(data_[i], buffer[i]);
  }

  ds->close();
  delete ds;
}

TEST_F(HttpDataSourceTest, ReadBeforeOpening) {
  bool opened;
  std::streamsize result;
  HttpDataSource *ds = new HttpDataSource(url_);
  unsigned char data_[32] = { 0x50, 0x52, 0x43, 0x4c, 0x00, 0x00, 0x00, 0x02,
	  0x63, 0x72, 0x63, 0x33, 0x32, 0x00, 0x00, 0x0f,
	  0x42, 0x40, 0x00, 0x00, 0x00, 0x00, 0x12, 0x66,
	  0x26, 0x41, 0x00, 0x00, 0x00, 0x01, 0x77, 0x73 };
  unsigned char buffer[sizeof(data_)];

  memset(buffer, 0, sizeof(buffer));
  result = ds->read(buffer, sizeof(data_));
  EXPECT_EQ((std::streamsize) 0, result);
  for (size_t i = 0; i < sizeof(data_); ++i) {
    EXPECT_EQ(0, buffer[i]);
  }

  opened = ds->open();
  EXPECT_EQ(true, opened);

  result = ds->read(buffer, sizeof(data_));
  EXPECT_EQ((std::streamsize) sizeof(data_), result);
  for (size_t i = 0; i < sizeof(data_); ++i) {
    EXPECT_EQ(data_[i], buffer[i]);
  }

  ds->close();
  delete ds;
}

TEST_F(HttpDataSourceTest, SeekBeforeOpening) {
  bool opened;
  std::streamsize result;
  HttpDataSource *ds = new HttpDataSource(url_);
  unsigned char data_[32] = { 0x50, 0x52, 0x43, 0x4c, 0x00, 0x00, 0x00, 0x02,
	  0x63, 0x72, 0x63, 0x33, 0x32, 0x00, 0x00, 0x0f,
	  0x42, 0x40, 0x00, 0x00, 0x00, 0x00, 0x12, 0x66,
	  0x26, 0x41, 0x00, 0x00, 0x00, 0x01, 0x77, 0x73 };
  unsigned char buffer[sizeof(data_)];

  opened = ds->open();
  EXPECT_EQ(true, opened);

  result = ds->read(buffer, sizeof(data_));
  EXPECT_EQ((std::streamsize) sizeof(data_), result);
  for (size_t i = 0; i < sizeof(data_); ++i) {
    EXPECT_EQ(data_[i], buffer[i]);
  }

  memset(buffer, 0, sizeof(buffer));
  result = ds->read(buffer, sizeof(data_));
  EXPECT_EQ((std::streamsize) 0, result);
  for (size_t i = 0; i < sizeof(data_); ++i) {
    EXPECT_EQ(0, buffer[i]);
  }

  ds->close();
  delete ds;
}

TEST_F(HttpDataSourceTest, RandomFile) {
  bool opened;
  std::streamsize result;
  unsigned int seed;
  unsigned char old;
  unsigned char buffer[4];
  unsigned char data_[32] = { 0x50, 0x52, 0x43, 0x4c, 0x00, 0x00, 0x00, 0x02,
	  0x63, 0x72, 0x63, 0x33, 0x32, 0x00, 0x00, 0x0f,
	  0x42, 0x40, 0x00, 0x00, 0x00, 0x00, 0x12, 0x66,
	  0x26, 0x41, 0x00, 0x00, 0x00, 0x01, 0x77, 0x73 };
  unsigned char buffer_full[sizeof(data_)];
  HttpDataSource *ds = new HttpDataSource(url_);

  opened = ds->open();
  EXPECT_EQ(true, opened);

  result = ds->read(0, 0);
  EXPECT_EQ((std::streamsize) 0, result);

  seed = (unsigned int) (time(NULL));
  buffer[0] = (unsigned char) (rand_r(&seed) % (255));
  old = buffer[0];
  result = ds->read(buffer, 0);
  EXPECT_EQ((std::streamsize) 0, result);
  EXPECT_EQ(old, buffer[0]);

  result = ds->read(buffer, 1);
  EXPECT_EQ((std::streamsize) 1, result);
  EXPECT_EQ(data_[0], buffer[0]);

  result = ds->read(buffer, 1);
  EXPECT_EQ((std::streamsize) 1, result);
  EXPECT_EQ(data_[1], buffer[0]);

  result = ds->read(buffer, 4);
  EXPECT_EQ((std::streamsize) 4, result);
  EXPECT_EQ(data_[2], buffer[0]);
  EXPECT_EQ(data_[3], buffer[1]);
  EXPECT_EQ(data_[4], buffer[2]);
  EXPECT_EQ(data_[5], buffer[3]);

  ds->seek((std::streampos) 4);
  result = ds->read(buffer, 1);
  EXPECT_EQ((std::streampos) 1, result);
  EXPECT_EQ(data_[4], buffer[0]);

  ds->seek((std::streampos) (sizeof(data_) + 20));
  result = ds->read(buffer, 1);
  EXPECT_EQ((std::streampos) 0, result);
  EXPECT_EQ(data_[4], buffer[0]);

  ds->seek((std::streampos) 0);
  result = ds->read(buffer_full, sizeof(data_) + 20);
  EXPECT_EQ((std::streampos) sizeof(data_), result);
  for (size_t i = 0; i < sizeof(data_); ++i) {
    EXPECT_EQ(data_[i], buffer_full[i]);
  }

  result = ds->read(buffer_full, 0);
  EXPECT_EQ((std::streampos) 0, result);
  for (size_t i = 0; i < sizeof(data_); ++i) {
    EXPECT_EQ(data_[i], buffer_full[i]);
  }

  delete ds;
}

}  // namespace DataSource

}  // namespace peeracle
