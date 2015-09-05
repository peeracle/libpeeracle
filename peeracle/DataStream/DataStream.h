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

#ifndef PEERACLE_DATASTREAM_DATASTREAM_H_
#define PEERACLE_DATASTREAM_DATASTREAM_H_

#include <stdint.h>
#include <cstring>
#include <ios>
#include <string>
#include <sstream>

#include "third_party/webrtc/webrtc/typedefs.h"

/**
 * \addtogroup peeracle
 * @{
 * @namespace peeracle
 * @brief peeracle namespace
 */
namespace peeracle {

struct DataStreamInit {
  DataStreamInit()
    : bigEndian(true),
      path(""),
      buffer(NULL),
      bufferLength(0) {
  }

  bool bigEndian;
  std::string path;
  uint8_t *buffer;
  std::streamsize bufferLength;
};

/**
 * \addtogroup DataStream
 * DataStream module abstract class.
 */
class DataStream {
 public:
  /**
   * Get the stream's length in bytes.
   * \return The opened stream's length.
   */
  virtual std::streamsize length() = 0;

  /**
   * Get the stream's cursor's current position.
   * \return The stream's cursor's current position in bytes.
   */
  virtual std::streamsize tell() = 0;

  /**
   * Move the cursor to an absolution \p position.
   * It will set the cursor at the same value as the length of the DataStream
   * if the \p position value is higher than it's length.
   * @param position the position to move the cursor to.
   * \return The new cursor's position.
   */
  virtual std::streamsize seek(std::streamsize position) = 0;

  std::streamsize read(char *buffer, std::streamsize length) {
    return _read(buffer, length);
  }

  std::streamsize read(int8_t *value) {
    return _read(value);
  }

  std::streamsize read(uint8_t *value) {
    return _read(value);
  }

  std::streamsize read(int16_t *value) {
    return _readSwap(value);
  }

  std::streamsize read(uint16_t *value) {
    return _readSwap(value);
  }

  std::streamsize read(int32_t *value) {
    return _readSwap(value);
  }

  std::streamsize read(uint32_t *value) {
    return _readSwap(value);
  }

  std::streamsize read(float *value) {
    return _readSwap(value);
  }

  std::streamsize read(double *value) {
    return _readSwap(value);
  }

  /**
   * Read a string at the cursor and store the value into the \p buffer.
   * The cursor will be increased to 4 bytes.
   * @param buffer a pointer to store the read data.
   * \return The number of bytes read.
   */
  std::streamsize read(std::string *buffer) {
    char c;
    std::streamsize i;
    std::stringstream strm;

    for (i = 0; i < 32768; ++i) {
      if (_read(&c, 1) < 1 || c == '\0') {
        break;
      }
      strm << c;
    }

    *buffer = strm.str();
    return i;
  }

  std::streamsize peek(uint8_t *buffer, std::streamsize length) {
    return _peek(buffer, length);
  }

  std::streamsize peek(int8_t *buffer) {
    return _peek(buffer);
  }

  std::streamsize peek(uint8_t *buffer) {
    return _peek(buffer);
  }

  std::streamsize peek(int16_t *buffer) {
    return _peekSwap(buffer);
  }

  std::streamsize peek(uint16_t *buffer) {
    return _peekSwap(buffer);
  }

  std::streamsize peek(int32_t *buffer) {
    return _peekSwap(buffer);
  }

  std::streamsize peek(uint32_t *buffer) {
    return _peekSwap(buffer);
  }

  std::streamsize peek(float *buffer) {
    return _peekSwap(buffer);
  }

  std::streamsize peek(double *buffer) {
    return _peekSwap(buffer);
  }

  /**
   * Read a string at the cursor and store the value into the \p buffer.
   * The cursor won't move.
   * @param buffer a pointer to store the read data.
   * \return The number of bytes read.
   */
  std::streamsize peek(std::string *buffer) {
    char c;
    std::streamsize i;
    std::stringstream strm;

    for (i = 0; i < 32768; ++i) {
      if (_peek(&c, 1) < 1 || c == '\0') {
        break;
      }
      strm << c;
    }

    *buffer = strm.str();
    return i;
  }

  std::streamsize write(const char *buffer, std::streamsize length) {
    return _write(buffer, length);
  }

  std::streamsize write(int8_t value) {
    return _write(&value);
  }

  std::streamsize write(uint8_t value) {
    return _write(&value);
  }

  std::streamsize write(int16_t value) {
    return _write(&value);
  }

  std::streamsize write(uint16_t value) {
    return _write(&value);
  }

  std::streamsize write(int32_t value) {
    return _write(&value);
  }

  std::streamsize write(uint32_t value) {
    return _write(&value);
  }

  std::streamsize write(float value) {
    return _write(&value);
  }

  std::streamsize write(double value) {
    return _write(&value);
  }

  /**
   * Write a string at the cursor and store the value into the \p buffer.
   * The cursor will be increased to 4 bytes.
   * @param buffer a pointer to store the read data.
   * \return The number of bytes read.
   */
  std::streamsize write(const std::string &value) {
    const char *str = value.c_str();
    return _write(str, strlen(str));
  }

  virtual ~DataStream() { }

 private:
  /**
   * Read up to \p length bytes of data at the cursor and store these into
   * the \p buffer. The cursor will be increased to \p length bytes.
   * @param buffer a pointer to the buffer which will receive the data.
   * @param length the number of bytes to read.
   * \return The number of bytes read.
   */
  virtual std::streamsize vread(char *buffer,
                                std::streamsize length) = 0;

  template<typename T>
  std::streamsize _read(T *buffer, std::streamsize length = sizeof(T)) {
    return vread(reinterpret_cast<char *>(buffer), length);
  }

  template<typename T>
  std::streamsize _readSwap(T *buffer, std::streamsize length = sizeof(T)) {
    std::streamsize result = _read(buffer, length);
    _swap(buffer, length);
    return result;
  }

  /**
   * Read up to \p length bytes of data at the cursor and store these into
   * the \p buffer. The cursor won't move.
   * @param buffer a pointer to the buffer which will receive the data.
   * @param length the number of bytes to read.
   * \return The number of bytes read.
   */
  virtual std::streamsize vpeek(char *buffer,
                                std::streamsize length) = 0;

  template<typename T>
  std::streamsize _peek(T *buffer, std::streamsize length = sizeof(T)) {
    return vpeek(reinterpret_cast<char *>(buffer), length);
  }

  template<typename T>
  std::streamsize _peekSwap(T *buffer, std::streamsize length = sizeof(T)) {
    std::streamsize result = _peek(buffer, length);
    _swap(buffer, length);
    return result;
  }

  /**
   * Write up to \p length bytes of data at the cursor and store these into
   * the \p buffer. The cursor will be increased to \p length bytes.
   * @param buffer a pointer to the buffer which will receive the data.
   * @param length the number of bytes to read.
   * \return The number of bytes read.
   */
  virtual std::streamsize vwrite(const char *buffer,
                                 std::streamsize length) = 0;

  template<typename T>
  std::streamsize _write(T *value, std::streamsize length = sizeof(T)) {
    return vwrite(reinterpret_cast<const char*>(value), length);
  }

  template<typename T>
  void _swap(T *buffer, std::streamsize length = sizeof(T)) {
#ifdef WEBRTC_ARCH_LITTLE_ENDIAN
    T value;
    T finalValue;
    uint8_t *originalData;
    uint8_t *finalData;

    value = *(reinterpret_cast<T*>(buffer));
    if (_bigEndian) {
      originalData = reinterpret_cast<uint8_t*>(&value);
      finalData = reinterpret_cast<uint8_t*>(&finalValue);
      for (uint32_t i = 0; i < sizeof(T); ++i) {
        finalData[i] = originalData[(sizeof(T) - i) - 1];
      }
      value = finalValue;
    }
    *buffer = value;
#endif
  }

 protected:
  bool _bigEndian;
};

/**
 * @}
 */
}  // namespace peeracle

#endif  // PEERACLE_DATASTREAM_DATASTREAM_H_
