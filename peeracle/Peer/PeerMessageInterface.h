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

#ifndef PEERACLE_PEER_PEERMESSAGEINTERFACE_H_
#define PEERACLE_PEER_PEERMESSAGEINTERFACE_H_

#include <string>
#include "peeracle/DataStream/DataStream.h"

/**
 * \addtogroup peeracle
 * @{
 * @namespace peeracle
 * @brief peeracle namespace
 */
namespace peeracle {

/**
 * \addtogroup Peer
 * @{
 * A class that deals with messages sent to and received from the Peer.
 */
class PeerMessageInterface {
 public:
  enum Type {
    kPing,
    kRequest,
    kChunk
  };

  virtual uint8_t getType() const = 0;

  /*
   * Set a parameter named \p key to a \p value.
   * @param key the parameter's name
   * @param value the parameter's value
   */
  virtual void set(const std::string &key, int8_t value) = 0;

  /*
   * @copydoc #set(const std::string& key, int8_t value)
   */
  virtual void set(const std::string &key, uint8_t value) = 0;

  /*
   * @copydoc #set(const std::string& key, int8_t value)
   */
  virtual void set(const std::string &key, int16_t value) = 0;

  /*
   * @copydoc #set(const std::string& key, int8_t value)
   */
  virtual void set(const std::string &key, uint16_t value) = 0;

  /*
   * @copydoc #set(const std::string& key, int8_t value)
   */
  virtual void set(const std::string &key, uint32_t value) = 0;

  /*
   * @copydoc #set(const std::string& key, int8_t value)
   */
  virtual void set(const std::string& key, const std::string& value) = 0;

  /*
   * Get the \p value of the parameter named \p key. This method should set
   * \p value to \p def if the parameter \p key has never been set before
   * with the #set method.
   * @param key the parameter's name
   * @param value point to write the parameter's value to
   */
  virtual void get(const std::string& key, int8_t *value, int8_t def) = 0;

  /*
   * @copydoc #get(const std::string& key, int8_t *value, int8_t def)
   */
  virtual void get(const std::string& key, uint8_t *value, uint8_t def) = 0;

  /*
   * @copydoc #get(const std::string& key, int8_t *value, int8_t def)
   */
  virtual void get(const std::string& key, int16_t *value, int16_t def) = 0;

  /*
   * @copydoc #get(const std::string& key, int8_t *value, int8_t def)
   */
  virtual void get(const std::string& key, uint16_t *value, uint16_t def) = 0;

  /*
   * @copydoc #get(const std::string& key, int8_t *value, int8_t def)
   */
  virtual void get(const std::string& key, int32_t *value, int32_t def) = 0;

  /*
   * @copydoc #get(const std::string& key, int8_t *value, int8_t def)
   */
  virtual void get(const std::string& key, uint32_t *value, uint32_t def) = 0;

  /*
   * @copydoc #get(const std::string& key, int8_t *value, int8_t def)
   */
  virtual void get(const std::string& key, std::string *value,
                   const std::string& def) = 0;

  /*
   * Unset a parameter \p key, removing it's value completely from the memory.
   * @param key the parameter's name
   */
  virtual void unset(const std::string& key) = 0;

  virtual bool serialize(DataStream *dataStream) = 0;
  virtual bool unserialize(DataStream *dataStream) = 0;

  virtual ~PeerMessageInterface() {}
};

/**
 * @}
 */
}  // namespace peeracle

#endif  // PEERACLE_PEER_PEERMESSAGEINTERFACE_H_
