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
#include <vector>
#include "third_party/webrtc/testing/gtest/include/gtest/gtest.h"
#include "peeracle/Metadata/Metadata.h"
#include "peeracle/Metadata/MetadataStreamInterface.h"
#include "peeracle/DataStream/MemoryDataStream.h"

namespace peeracle {

class MetadataTest : public testing::Test {
 protected:
  MetadataTest() : _metadata(NULL) {
  }

  virtual void SetUp() {
    DataStreamInit dsInit;

    _metadata = new Metadata();
    _ds = new MemoryDataStream(dsInit);
  }

  void TEST_CORRUPTED_READ() {
    std::streamsize pos = _ds->tell();
    std::streamsize s;
    bool result;

    s = _ds->seek(0);
    EXPECT_EQ(0, s);

    result = _metadata->unserialize(_ds);
    EXPECT_FALSE(result);

    s = _ds->seek(pos);
    EXPECT_EQ(pos, s);
  }

  void TEST_VALID_READ() {
    std::streamsize pos = _ds->tell();
    std::streamsize s;
    bool result;

    s = _ds->seek(0);
    EXPECT_EQ(0, s);

    result = _metadata->unserialize(_ds);
    EXPECT_TRUE(result);

    s = _ds->seek(pos);
    EXPECT_EQ(pos, s);
  }

  virtual void TearDown() {
    delete _ds;
    delete _metadata;
  }

  Metadata *_metadata;
  MemoryDataStream *_ds;
};

TEST_F(MetadataTest, EmptyDataStream) {
  bool result;

  result = _metadata->unserialize(_ds);
  EXPECT_FALSE(result);
}

TEST_F(MetadataTest, CorruptedHeader) {
  bool result;
  std::streamsize s;

  result = _metadata->unserialize(_ds);
  EXPECT_FALSE(result);

  s = _ds->write(static_cast<int8_t>('P'));
  EXPECT_EQ(sizeof(int8_t), s);

  this->TEST_CORRUPTED_READ();

  s = _ds->write("RCL", 3);
  // write the magic (PRCL)
  EXPECT_EQ(3, s);

  this->TEST_CORRUPTED_READ();

  s = _ds->write(static_cast<int32_t>(2));
  // write the version
  EXPECT_EQ(sizeof(int32_t), s);

  this->TEST_CORRUPTED_READ();

  s = _ds->write("crc32", 6);
  // write the hash algorithm
  EXPECT_EQ(6, s);

  this->TEST_CORRUPTED_READ();

  s = _ds->write(1000000);
  // write the timecode scale
  EXPECT_EQ(sizeof(uint32_t), s);

  this->TEST_CORRUPTED_READ();

  s = _ds->write(794000.0);
  // write the duration
  EXPECT_EQ(sizeof(double), s);

  this->TEST_CORRUPTED_READ();

  s = _ds->write(1);
  // write the number of trackers
  EXPECT_EQ(sizeof(uint32_t), s);

  this->TEST_CORRUPTED_READ();

  s = _ds->write("ws://127.0.0.1:8080", 20);
  // write the tracker's address
  EXPECT_EQ(20, s);

  this->TEST_CORRUPTED_READ();

  s = _ds->write(0);
  EXPECT_EQ(sizeof(uint32_t), s);
  // write the number of streams

  this->TEST_VALID_READ();
}

TEST_F(MetadataTest, CorrectHeader) {
  uint32_t magic;
  uint32_t version;
  uint32_t timecodeScale;
  double duration;

  bool res;
  std::streamsize s;

  s = _ds->write("PRCL", 4);
  EXPECT_EQ(4, s);

  s = _ds->write(static_cast<int32_t>(2));
  EXPECT_EQ(sizeof(int32_t), s);

  s = _ds->write("crc32", 6);
  EXPECT_EQ(6, s);

  s = _ds->write(1000000);
  EXPECT_EQ(sizeof(uint32_t), s);

  s = _ds->write(794000.0);
  EXPECT_EQ(sizeof(double), s);

  s = _ds->write(1);
  EXPECT_EQ(sizeof(uint32_t), s);

  s = _ds->write("ws://127.0.0.1:8080", 20);
  EXPECT_EQ(20, s);

  s = _ds->write(0);
  EXPECT_EQ(sizeof(uint32_t), s);

  res = _metadata->unserialize(_ds);
  EXPECT_FALSE(res);

  _ds->seek(0);
  res = _metadata->unserialize(_ds);
  EXPECT_TRUE(res);

  magic = _metadata->getMagic();
  version = _metadata->getVersion();
  const std::string &hashName = _metadata->getHashAlgorithmName();
  timecodeScale = _metadata->getTimecodeScale();
  duration = _metadata->getDuration();

  const std::vector<std::string> &trackers =
    _metadata->getTrackerUrls();
  const std::vector<MetadataStreamInterface *> &streams =
    _metadata->getStreams();

  EXPECT_EQ(0x5052434C, magic);
  EXPECT_EQ(2, version);
  EXPECT_EQ("crc32", hashName);
  EXPECT_EQ(1000000, timecodeScale);
  EXPECT_EQ(794000.0, duration);
  ASSERT_EQ(1, trackers.size());
  EXPECT_EQ("ws://127.0.0.1:8080", trackers[0]);
  EXPECT_EQ(0, streams.size());
}

TEST_F(MetadataTest, Serialize) {
  uint32_t magic;
  uint32_t version;
  uint32_t timecodeScale;
  double duration;
  uint32_t numTrackers;
  uint32_t numStreams;
  std::streamsize s;
  peeracle::MemoryDataStream *expectedDs;

  _metadata->setHashAlgorithmName("crc32");
  _metadata->setTimecodeScale(1000000);
  _metadata->setDuration(794000.0);
  _metadata->addTracker("ws://127.0.0.1:8080");

  s = _ds->write("PRCL", 4);
  EXPECT_EQ(4, s);

  s = _ds->write(static_cast<int32_t>(2));
  EXPECT_EQ(sizeof(int32_t), s);

  s = _ds->write("crc32", 6);
  EXPECT_EQ(6, s);

  s = _ds->write(1000000);
  EXPECT_EQ(sizeof(uint32_t), s);

  s = _ds->write(794000.0);
  EXPECT_EQ(sizeof(double), s);

  s = _ds->write(1);
  EXPECT_EQ(sizeof(uint32_t), s);

  s = _ds->write("ws://127.0.0.1:8080", 20);
  EXPECT_EQ(20, s);

  s = _ds->write(0);
  EXPECT_EQ(sizeof(uint32_t), s);

  DataStreamInit dsInit;
  expectedDs = new MemoryDataStream(dsInit);
  _metadata->serialize(expectedDs);

  s = expectedDs->seek(0);
  EXPECT_EQ(0, s);

  s = expectedDs->tell();
  EXPECT_EQ(0, s);

  s = expectedDs->read(&magic);
  EXPECT_EQ(sizeof(magic), s);
  EXPECT_EQ(0x5052434C, magic);

  s = expectedDs->read(&version);
  EXPECT_EQ(sizeof(version), s);
  EXPECT_EQ(2, version);

  std::string hashAlgorithm;
  s = expectedDs->read(&hashAlgorithm);
  EXPECT_EQ(5, s);
  EXPECT_EQ("crc32", hashAlgorithm);

  s = expectedDs->read(&timecodeScale);
  EXPECT_EQ(sizeof(timecodeScale), s);
  EXPECT_EQ(1000000, timecodeScale);

  s = expectedDs->read(&duration);
  EXPECT_EQ(sizeof(duration), s);
  EXPECT_EQ(794000.0, duration);

  s = expectedDs->read(&numTrackers);
  EXPECT_EQ(sizeof(numTrackers), s);
  EXPECT_EQ(1, numTrackers);

  std::string tracker;
  s = expectedDs->read(&tracker);
  EXPECT_EQ(19, s);
  EXPECT_EQ("ws://127.0.0.1:8080", tracker);

  s = expectedDs->read(&numStreams);
  EXPECT_EQ(sizeof(numStreams), s);
  EXPECT_EQ(0, numStreams);
}

}  // namespace peeracle
