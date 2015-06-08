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

#ifndef PEERACLE_TRACKER_MESSAGE_TRACKERMESSAGEINTERFACE_H_
#define PEERACLE_TRACKER_MESSAGE_TRACKERMESSAGEINTERFACE_H_

#include <string>

/**
 * \addtogroup peeracle
 * @{
 * @namespace peeracle
 * @brief peeracle namespace
 */
namespace peeracle {

/**
 * \addtogroup Tracker
 * @{
 * A class that deals with messages sent to and received from the Tracker.
 */
class TrackerMessageInterface {
 public:
  enum Type {
    kNone,
    kHello,
    kWelcome,
    kEnter,
    kLeave,
    kAnnounce,
    kOffer,
    kAnswer,
    kIce
  };

  /*
   * Set a parameter named \p key to a \p value.
   * @param key the parameter's name
   * @param value the parameter's value
   */
  virtual void set(const std::string& key, int value) = 0;

  /*
   * @copydoc #set(const std::string& key, int value)
   */
  virtual void set(const std::string& key, const std::string& value) = 0;

  /*
   * Unset a parameter \p key, removing it's value completely from the memory.
   * @param key the parameter's name
   */
  virtual void unset(const std::string& key) = 0;

  /*
   * Get the \p value of the parameter named \p key. This method should set
   * \p value to \p def if the parameter \p key has never been set before
   * with the #set method.
   * @param key the parameter's name
   * @param value point to write the parameter's value to
   */
  virtual void get(const std::string& key, int *value, int def) = 0;

  /*
   * @copydoc #get(const std::string& key, int *value)
   */
  virtual void get(const std::string& key, std::string *value,
                   const std::string& def) = 0;

  /*
   * Calculate the length of a serialized TrackerMessage in bytes. Calling
   * this method is required in order to allocated a buffer properly before
   * calling #serialize.
   * \return the length of the serialized buffer in bytes
   */
  virtual unsigned int getByteLength() = 0;

  /*
   * Serialize the message into \p buffer. The resulting bytes could be used
   * for sending messages to a client or a server using the Tracker protocol.
   * @param buffer the buffer into which the bytes should be stored
   * @param length the buffer's length
   */
  virtual void serialize(unsigned char *buffer, unsigned int length) = 0;

  /*
   * Unserialize the bytes located inside the \p buffer. The parameters will
   * be restored, depending on the message type and the validity of the buffer.
   * @param buffer the buffer containing the serialized TrackerMessage
   */
  virtual void unserialize(const unsigned char *buffer,
                           unsigned int length) = 0;

 protected:
  virtual ~TrackerMessageInterface() { }
};

/**
 * @}
 */
}  // namespace peeracle

#endif  // PEERACLE_TRACKER_MESSAGE_TRACKERMESSAGEINTERFACE_H_
