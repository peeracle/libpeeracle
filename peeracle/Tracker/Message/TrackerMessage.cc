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

#include <sstream>
#include <iostream>
#include "peeracle/Tracker/Message/TrackerMessage.h"

namespace peeracle {

TrackerMessage::TrackerMessage(uint8_t type) : _type(type) {
}

TrackerMessage::~TrackerMessage() {
}

uint8_t TrackerMessage::getType() const {
  return _type;
}

void TrackerMessage::get(const std::string &key, int8_t *value, int8_t def) {
  _get(key, value, def);
}

void TrackerMessage::get(const std::string &key, uint8_t *value, uint8_t def) {
  _get(key, value, def);
}

void TrackerMessage::get(const std::string &key, int16_t *value, int16_t def) {
  _get(key, value, def);
}

void TrackerMessage::get(const std::string &key, uint16_t *value,
                         uint16_t def) {
  _get(key, value, def);
}

void TrackerMessage::get(const std::string &key, int32_t *value, int32_t def) {
  _get(key, value, def);
}

void TrackerMessage::get(const std::string &key, uint32_t *value,
                         uint32_t def) {
  _get(key, value, def);
}

void TrackerMessage::get(const std::string &key, std::string *value,
                         const std::string &def) {
  if (_keys.find(key) == _keys.end()) {
    *value = def;
    return;
  }

  *value = _keys[key];
}


template<typename T>
void TrackerMessage::_get(const std::string &key, T *value, T def) {
  std::stringstream strm;

  if (_keys.find(key) == _keys.end()) {
    *value = def;
    return;
  }

  strm << _keys[key];
  strm >> *value;
}

void TrackerMessage::set(const std::string &key, int8_t value) {
  _set(key, value);
}

void TrackerMessage::set(const std::string &key, uint8_t value) {
  _set(key, value);
}

void TrackerMessage::set(const std::string &key, int16_t value) {
  _set(key, value);
}

void TrackerMessage::set(const std::string &key, uint16_t value) {
  _set(key, value);
}

void TrackerMessage::set(const std::string &key, int32_t value) {
  _set(key, value);
}

void TrackerMessage::set(const std::string &key, uint32_t value) {
  _set(key, value);
}

void TrackerMessage::set(const std::string &key, const std::string &value) {
  _keys[key] = value;
}

template<typename T>
void TrackerMessage::_set(const std::string &key, T value) {
  std::stringstream strm;

  strm << value;
  _keys[key] = strm.str();
}

void TrackerMessage::unset(const std::string &key) {
  if (_keys.find(key) == _keys.end()) {
    return;
  }

  _keys.erase(key);
}

bool TrackerMessage::_serializeWelcome(DataStreamInterface *dataStream) {
  std::string id;

  get("id", &id, "");
  if (id == "") {
    return false;
  }

  dataStream->write(id);
  return true;
}

bool TrackerMessage::_serializeAnnounce(DataStreamInterface *dataStream) {
  std::string hash;
  uint32_t got;

  get("hash", &hash, "");
  if (hash == "") {
    return false;
  }

  get("got", &got, 0);
  dataStream->write(hash);
  dataStream->write(got);
  return true;
}

bool TrackerMessage::_serializeEnter(DataStreamInterface *dataStream) {
  return false;
}

bool TrackerMessage::_serializePoke(DataStreamInterface *dataStream) {
  std::string hash;
  std::string peer;
  uint32_t got;

  get("hash", &hash, "");
  if (hash == "") {
    return false;
  }

  get("peer", &peer, "");
  if (peer == "") {
    return false;
  }

  get("got", &got, 0);

  dataStream->write(hash);
  dataStream->write(peer);
  dataStream->write(got);
  return true;
}

bool TrackerMessage::serialize(DataStreamInterface *dataStream) {
  dataStream->write(_type);

  switch (_type) {
    case kKeepAlive:
    case kHello:
      break;
    case kWelcome:
      return _serializeWelcome(dataStream);
    case kAnnounce:
      return _serializeAnnounce(dataStream);
    case kEnter:
      return _serializeEnter(dataStream);
    case kPoke:
      return _serializePoke(dataStream);
    default:
      break;
  }

  return false;
}

bool TrackerMessage::_unserializeWelcome(DataStreamInterface *dataStream) {
  std::string id;

  dataStream->read(&id);
  set("id", id);
  return true;
}

bool TrackerMessage::_unserializeAnnounce(DataStreamInterface *dataStream) {
  std::string hash;
  uint32_t got;

  dataStream->read(&hash);
  dataStream->read(&got);

  set("hash", hash);
  set("got", got);
  return true;
}

bool TrackerMessage::_unserializeEnter(DataStreamInterface *dataStream) {
  return false;
}

bool TrackerMessage::_unserializePoke(DataStreamInterface *dataStream) {
  std::string hash;
  std::string peer;
  uint32_t got;

  dataStream->read(&hash);
  dataStream->read(&peer);
  dataStream->read(&got);

  set("hash", hash);
  set("peer", peer);
  set("got", got);
  return true;
}

bool TrackerMessage::unserialize(DataStreamInterface *dataStream) {
  dataStream->read(&_type);

  switch (_type) {
    case kKeepAlive:
    case kHello:
      break;
    case kWelcome:
      return _unserializeWelcome(dataStream);
    case kAnnounce:
      return _unserializeAnnounce(dataStream);
    case kEnter:
      return _unserializeEnter(dataStream);
    case kPoke:
      return _unserializePoke(dataStream);
    default:
      break;
  }

  return false;
}

}  // namespace peeracle
