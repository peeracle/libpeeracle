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

#ifndef PEERACLE_DATASTREAM_DATASTREAMINTERFACE_H_
#define PEERACLE_DATASTREAM_DATASTREAMINTERFACE_H_

#include <ios>
#include <cstdint>

/**
 * \addtogroup peeracle
 * @{
 * @namespace peeracle
 * @brief peeracle namespace
 */
namespace peeracle {

/**
 * \addtogroup DataStream
 * DataStream module interface.
 */
class DataStreamInterface {
 public:
  /**
   * Open the DataStream for reading.
   * \return The number of bytes that can be read from the DataStream.
   */
  virtual bool open() = 0;

  /**
   * Close the DataStream.
   */
  virtual void close() = 0;

  /**
   * Get the stream's length in bytes.
   * \return The opened stream's length.
   */
  virtual std::streamsize length() const = 0;

  /**
   * Get the stream's cursor's current position.
   * \return The stream's cursor's current position in bytes.
   */
  virtual std::streamsize tell() const = 0;

  /**
   * Move the cursor to an absolution \p position.
   * It will set the cursor at the same value as the length of the DataStream
   * if the \p position value is higher than it's length.
   * @param position the position to move the cursor to.
   * \return The new cursor's position.
   */
  virtual std::streamsize seek(std::streamsize position) = 0;

  /**
   * Read up to \p length bytes of data at the cursor and store these into
   * the \p buffer. The cursor will be increased to \p length bytes.
   * @param buffer a pointer to the buffer which will receive the data.
   * @param length the number of bytes to read.
   * \return The number of bytes read.
   */
  virtual std::streamsize read(uint8_t **buffer,
                               std::streamsize length) = 0;

  /**
   * Read a signed char at the cursor and store the value into the \p buffer.
   * @param buffer a pointer to store the read data. The cursor will be
   * increased to 1 byte.
   * \return The number of bytes read.
   */
  virtual std::streamsize read(int8_t *buffer) = 0;

  /**
   * Read an unsigned char at the cursor and store the value into the
   * \p buffer. The cursor will be increased to 1 byte.
   * @param buffer a pointer to store the read data.
   * \return The number of bytes read.
   */
  virtual std::streamsize read(uint8_t *buffer) = 0;

  /**
   * Read a signed short at the cursor and store the value into the
   * \p buffer. The cursor will be increased to 2 bytes.
   * @param buffer a pointer to store the read data.
   * \return The number of bytes read.
   */
  virtual std::streamsize read(int16_t *buffer) = 0;

  /**
   * Read an unsigned short at the cursor and store the value into the
   * \p buffer. The cursor will be increased to 2 bytes.
   * @param buffer a pointer to store the read data.
   * \return The number of bytes read.
   */
  virtual std::streamsize read(uint16_t *buffer) = 0;

  /**
   * Read a signed integer at the cursor and store the value into the
   * \p buffer. The cursor will be increased to 4 bytes.
   * @param buffer a pointer to store the read data.
   * \return The number of bytes read.
   */
  virtual std::streamsize read(int32_t *buffer) = 0;

  /**
   * Read an unsigned integer at the cursor and store the value into the
   * \p buffer. The cursor will be increased to 4 bytes.
   * @param buffer a pointer to store the read data.
   * \return The number of bytes read.
   */
  virtual std::streamsize read(uint32_t *buffer) = 0;

  /**
   * Read a float at the cursor and store the value into the \p buffer.
   * The cursor will be increased to 4 bytes.
   * @param buffer a pointer to store the read data.
   * \return The number of bytes read.
   */
  virtual std::streamsize read(float *buffer) = 0;

  /**
   * Read a double at the cursor and store the value into the \p buffer.
   * The cursor will be increased to 4 bytes.
   * @param buffer a pointer to store the read data.
   * \return The number of bytes read.
   */
  virtual std::streamsize read(double *buffer) = 0;

  /**
   * Read up to \p length bytes of data at the cursor and store these into
   * the \p buffer. The cursor won't move.
   * @param buffer a pointer to the buffer which will receive the data.
   * @param length the number of bytes to read.
   * \return The number of bytes read.
   */
  virtual std::streamsize peek(uint8_t **buffer,
                               std::streamsize length) = 0;

  /**
   * Read a signed char at the cursor and store the value into the
   * \p buffer. The cursor won't move.
   * @param buffer a pointer to store the read data.
   * \return The number of bytes read.
   */
  virtual std::streamsize peek(int8_t *buffer) = 0;

  /**
   * Read an unsigned char at the cursor and store the value into the
   * \p buffer. The cursor won't move.
   * @param buffer a pointer to store the read data.
   * \return The number of bytes read.
   */
  virtual std::streamsize peek(uint8_t *buffer) = 0;

  /**
   * Read a signed short at the cursor and store the value into the
   * \p buffer. The cursor won't move.
   * @param buffer a pointer to store the read data.
   * \return The number of bytes read.
   */
  virtual std::streamsize peek(int16_t *buffer) = 0;

  /**
   * Read an unsigned short at the cursor and store the value into the
   * \p buffer. The cursor won't move.
   * @param buffer a pointer to store the read data.
   * \return The number of bytes read.
   */
  virtual std::streamsize peek(uint16_t *buffer) = 0;

  /**
   * Read a signed integer at the cursor and store the value into the
   * \p buffer. The cursor won't move.
   * @param buffer a pointer to store the read data.
   * \return The number of bytes read.
   */
  virtual std::streamsize peek(int32_t *buffer) = 0;

  /**
   * Read an unsigned integer at the cursor and store the value into the
   * \p buffer. The cursor won't move.
   * @param buffer a pointer to store the read data.
   * \return The number of bytes read.
   */
  virtual std::streamsize peek(uint32_t *buffer) = 0;

  /**
   * Read a float at the cursor and store the value into the \p buffer.
   * The cursor won't move.
   * @param buffer a pointer to store the read data.
   * \return The number of bytes read.
   */
  virtual std::streamsize peek(float *buffer) = 0;

  /**
   * Read a double at the cursor and store the value into the \p buffer.
   * The cursor won't move.
   * @param buffer a pointer to store the read data.
   * \return The number of bytes read.
   */
  virtual std::streamsize peek(double *buffer) = 0;

  /**
   * Write up to \p length bytes of data at the cursor and store these into
   * the \p buffer. The cursor will be increased to \p length bytes.
   * @param buffer a pointer to the buffer which will receive the data.
   * @param length the number of bytes to read.
   * \return The number of bytes read.
   */
  virtual std::streamsize write(uint8_t **buffer,
                               std::streamsize length) = 0;

  /**
   * Write a signed char at the cursor and store the value into the \p buffer.
   * @param buffer a pointer to store the read data. The cursor will be
   * increased to 1 byte.
   * \return The number of bytes read.
   */
  virtual std::streamsize write(int8_t value) = 0;

  /**
   * Write an unsigned char at the cursor and store the value into the
   * \p buffer. The cursor will be increased to 1 byte.
   * @param buffer a pointer to store the read data.
   * \return The number of bytes read.
   */
  virtual std::streamsize write(uint8_t value) = 0;

  /**
   * Write a signed short at the cursor and store the value into the
   * \p buffer. The cursor will be increased to 2 bytes.
   * @param buffer a pointer to store the read data.
   * \return The number of bytes read.
   */
  virtual std::streamsize write(int16_t value) = 0;

  /**
   * Write an unsigned short at the cursor and store the value into the
   * \p buffer. The cursor will be increased to 2 bytes.
   * @param buffer a pointer to store the read data.
   * \return The number of bytes read.
   */
  virtual std::streamsize write(uint16_t value) = 0;

  /**
   * Write a signed integer at the cursor and store the value into the
   * \p buffer. The cursor will be increased to 4 bytes.
   * @param buffer a pointer to store the read data.
   * \return The number of bytes read.
   */
  virtual std::streamsize write(int32_t value) = 0;

  /**
   * Write an unsigned integer at the cursor and store the value into the
   * \p buffer. The cursor will be increased to 4 bytes.
   * @param buffer a pointer to store the read data.
   * \return The number of bytes read.
   */
  virtual std::streamsize write(uint32_t value) = 0;

  /**
   * Write a float at the cursor and store the value into the \p buffer.
   * The cursor will be increased to 4 bytes.
   * @param buffer a pointer to store the read data.
   * \return The number of bytes read.
   */
  virtual std::streamsize write(float value) = 0;

  /**
   * Write a double at the cursor and store the value into the \p buffer.
   * The cursor will be increased to 4 bytes.
   * @param buffer a pointer to store the read data.
   * \return The number of bytes read.
   */
  virtual std::streamsize write(double value) = 0;

 protected:
  virtual ~DataStreamInterface() { }
};

/**
 * @}
 */
}  // namespace peeracle

#endif  // PEERACLE_DATASTREAM_DATASTREAMINTERFACE_H_
