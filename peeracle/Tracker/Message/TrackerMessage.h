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

#ifndef PEERACLE_TRACKER_MESSAGE_TRACKERMESSAGE_H_
#define PEERACLE_TRACKER_MESSAGE_TRACKERMESSAGE_H_

#include <string>
#include "peeracle/Tracker/Message/TrackerMessageInterface.h"

namespace peeracle {

class TrackerMessage : public TrackerMessageInterface {
 public:
  void set(const std::string &key, int value);
  void set(const std::string &key, const std::string &value);
  void unset(const std::string &key);
  void get(const std::string &key, int *value, int def);
  void get(const std::string &key, std::string *value, const std::string& def);

  unsigned int getByteLength();
  void serialize(unsigned char *buffer, unsigned int length);
  void unserialize(const unsigned char *buffer, unsigned int length);

  virtual ~TrackerMessage() {}
};

}  // namespace peeracle

#endif  // PEERACLE_TRACKER_MESSAGE_TRACKERMESSAGE_H_
