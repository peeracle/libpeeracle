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

#include <map>
#include <string>
#include "peeracle/DataStream/DataStreamInterface.h"
#include "peeracle/Tracker/Message/TrackerMessageInterface.h"

namespace peeracle {

class TrackerMessage : public TrackerMessageInterface {
 public:
  explicit TrackerMessage(uint8_t type = kKeepAlive);
  ~TrackerMessage();

  uint8_t getType() const;

  void set(const std::string &key, int8_t value);
  void set(const std::string &key, uint8_t value);
  void set(const std::string &key, int16_t value);
  void set(const std::string &key, uint16_t value);
  void set(const std::string &key, int32_t value);
  void set(const std::string &key, uint32_t value);
  void set(const std::string &key, const std::string &value);

  void get(const std::string &key, int8_t *value, int8_t def);
  void get(const std::string &key, uint8_t *value, uint8_t def);
  void get(const std::string &key, int16_t *value, int16_t def);
  void get(const std::string &key, uint16_t *value, uint16_t def);
  void get(const std::string &key, int32_t *value, int32_t def);
  void get(const std::string &key, uint32_t *value, uint32_t def);
  void get(const std::string &key, std::string *value, const std::string& def);

  void unset(const std::string &key);

  bool serialize(DataStreamInterface *dataStream);
  bool unserialize(DataStreamInterface *dataStream);

 private:
  uint8_t _type;
  std::map<std::string, std::string> _keys;

  template<typename T>
  void _get(const std::string &key, T *value, T def);

  template<typename T>
  void _set(const std::string &key, T value);

  bool _serializeWelcome(DataStreamInterface *dataStream);
  bool _serializeAnnounce(DataStreamInterface *dataStream);
  bool _serializeEnter(DataStreamInterface *dataStream);
  bool _serializePoke(DataStreamInterface *dataStream);

  bool _unserializeWelcome(DataStreamInterface *dataStream);
  bool _unserializeAnnounce(DataStreamInterface *dataStream);
  bool _unserializeEnter(DataStreamInterface *dataStream);
  bool _unserializePoke(DataStreamInterface *dataStream);
};

}  // namespace peeracle

#endif  // PEERACLE_TRACKER_MESSAGE_TRACKERMESSAGE_H_
