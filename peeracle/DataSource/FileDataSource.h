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

#ifndef PEERACLE_DATASOURCE_FILEDATASOURCE_H_
#define PEERACLE_DATASOURCE_FILEDATASOURCE_H_

#include <string>
#include "DataSourceInterface.h"

/**
 * \addtogroup peeracle
 * @{
 * @namespace peeracle
 * @brief peeracle namespace
 */
namespace peeracle {

/**
 * \addtogroup DataSource
 * @{
 * @namespace peeracle::DataSource
 * @brief DataSource namespace
 */
namespace DataSource {

/**
 * A class that retrieves data from a local file.
 */
class FileDataSource
  : public DataSourceInterface {
 public:
  explicit FileDataSource(const std::string &filename);
  virtual ~FileDataSource() {}

  std::streampos open();
  void close();
  std::streamsize read(unsigned char *buffer, std::streamsize length);
};

/**
 * @}
 */
}  // namespace DataSource

/**
 * @}
 */
}  // namespace peeracle

#endif  // PEERACLE_DATASOURCE_FILEDATASOURCE_H_
