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
#include "peeracle/DataSource/FileDataSource.h"
#include "peeracle/DataSource/HttpDataSource.h"

namespace peeracle {

#ifdef _MSC_VER
int rand_r(unsigned int *seed) {
  srand(*seed);
  return rand();
}
#endif

typedef ::testing::Types<FileDataSource, HttpDataSource> DataSourceTypes;
TYPED_TEST_CASE(DataSourceTest, DataSourceTypes);

template <typename T>
class DataSourceTest : public ::testing::Test {
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

    tmpfile.write(reinterpret_cast<char*>(data_), sizeof(data_));
    tmpfile.close();
  }

  virtual void TearDown() {
    remove(filename_.c_str());
  }

  std::string filename_;
  unsigned char data_[64];
};

TYPED_TEST(DataSourceTest, OpenShouldFail) {
}

}  // namespace peeracle
