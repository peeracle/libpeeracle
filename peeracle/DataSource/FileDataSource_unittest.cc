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
#include "third_party/googletest/gtest/include/gtest/gtest.h"
#include "peeracle/DataSource/FileDataSource.h"

namespace peeracle {

namespace DataSource {

TEST(FileDataSourceTestInvalid, FileNotFound) {
  std::streampos result;
  char filename[16];
  unsigned int seed;
  FileDataSource *ds;

  seed = (unsigned int)(time(NULL));
  for (size_t i = 0; i < sizeof(filename); i++) {
    filename[i] = (unsigned char)(rand_r(&seed) % (122 - 1) + 97);
  }

  ds = new FileDataSource(filename);
  result = ds->open();
  EXPECT_EQ((std::streampos)0, result);
}

class FileDataSourceTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    unsigned int seed;
    const ::testing::TestInfo* const test_info =
      ::testing::UnitTest::GetInstance()->current_test_info();

    std::stringstream strm;
    strm << test_info->test_case_name() << "_" << test_info->name() << ".bin";
    filename_ = strm.str();

    std::ofstream tmpfile(filename_.c_str(),
                          std::ofstream::out | std::ofstream::binary);

    seed = (unsigned int)(time(NULL));
    for (size_t i = 0; i < sizeof(data_); i++) {
      data_[i] = (unsigned char)(rand_r(&seed) % (255));
    }

    tmpfile << data_;
    tmpfile.close();
  }

  virtual void TearDown() {
    remove(filename_.c_str());
  }

  std::string filename_;
  unsigned char data_[64];
};

TEST_F(FileDataSourceTest, RandomFile) {
  std::streampos fileLength;
  std::streampos result;
  unsigned int seed;
  unsigned char old;
  unsigned char buffer[4];
  unsigned char buffer_full[sizeof(data_)];
  FileDataSource *ds = new FileDataSource(filename_);

  fileLength = ds->open();
  EXPECT_EQ((std::streampos)sizeof(data_), fileLength);

  result = ds->read(0, 0);
  EXPECT_EQ((std::streampos)0, result);

  seed = (unsigned int)(time(NULL));
  buffer[0] = (unsigned char)(rand_r(&seed) % (255));
  old = buffer[0];
  result = ds->read(buffer, 0);
  EXPECT_EQ((std::streampos)0, result);
  EXPECT_EQ(old, buffer[0]);

  result = ds->read(buffer, 1);
  EXPECT_EQ((std::streampos)1, result);
  EXPECT_EQ(data_[0], buffer[0]);

  result = ds->read(buffer, 1);
  EXPECT_EQ((std::streampos)1, result);
  EXPECT_EQ(data_[1], buffer[0]);

  result = ds->read(buffer, 4);
  EXPECT_EQ((std::streampos)4, result);
  EXPECT_EQ(data_[2], buffer[0]);
  EXPECT_EQ(data_[3], buffer[1]);
  EXPECT_EQ(data_[4], buffer[2]);
  EXPECT_EQ(data_[5], buffer[3]);

  ds->seek((std::streampos)4);
  result = ds->read(buffer, 1);
  EXPECT_EQ((std::streampos)1, result);
  EXPECT_EQ(data_[4], buffer[0]);

  ds->seek((std::streampos)(sizeof(data_) + 20));
  result = ds->read(buffer, 1);
  EXPECT_EQ(fileLength, result);
  EXPECT_EQ(data_[4], buffer[0]);

  ds->seek((std::streampos)0);
  result = ds->read(buffer_full, sizeof(data_) + 20);
  EXPECT_EQ((std::streampos)sizeof(data_), result);
  for (size_t i = 0; i < sizeof(data_); ++i) {
    EXPECT_EQ(data_[i], buffer_full[i]);
  }

  result = ds->read(buffer_full, 0);
  EXPECT_EQ((std::streampos)0, result);
  for (size_t i = 0; i < sizeof(data_); ++i) {
    EXPECT_EQ(data_[i], buffer_full[i]);
  }

  delete ds;
}

}  // namespace DataSource

}  // namespace peeracle
