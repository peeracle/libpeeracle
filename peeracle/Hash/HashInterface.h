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

#ifndef PEERACLE_HASH_HASHINTERFACE_H_
#define PEERACLE_HASH_HASHINTERFACE_H_

#include <cstdlib>

/**
 * \addtogroup peeracle
 * @{
 */
namespace peeracle {

/**
 * \addtogroup Hash
 * @{
 */
namespace Hash {

/**
 * Hash module interface.
 */
class HashInterface {
 public:
  /**
   * Initialize the hash algorithm module.
   */
  virtual void init() = 0;

  /**
   * Append some bytes inside the hash module's internal buffer.
   * @param buffer a pointer to a buffer containing the bytes to hash.
   * @param length the number of bytes to hash inside the buffer.
   */
  virtual void update(unsigned char const *buffer, unsigned int length) = 0;

  /**
   * Execute the hash operation from the bytes inside the internal buffer.
   * @param result a pointer to the buffer which will receive the checksum.
   */
  virtual void final(unsigned char *result) = 0;

  /**
   * Execute init, update and final methods at once.
   * @param buffer a pointer to a buffer containing the bytes to hash.
   * @param length the number of bytes to hash inside the buffer.
   * @param result a pointer to the buffer which will receive the checksum.
   */
  virtual void checksum(unsigned char const *buffer, unsigned int length,
                        unsigned char *result) = 0;

 protected:
  virtual ~HashInterface() {}
};

}  // namespace Hash

}  // namespace peeracle

#endif  // PEERACLE_HASH_HASHINTERFACE_H_
