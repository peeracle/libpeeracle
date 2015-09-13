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
#include <vector>

#include "peeracle/Peer/PeerMessage.h"

namespace peeracle {

PeerMessage::PeerMessage(uint8_t type) : _type(type) {
}

PeerMessage::~PeerMessage() {
  _keys.clear();
}

uint8_t PeerMessage::getType() const {
  return _type;
}

void PeerMessage::get(const std::string &key, int8_t *value, int8_t def) {
  _get(key, value, def);
}

void PeerMessage::get(const std::string &key, uint8_t *value, uint8_t def) {
  _get(key, value, def);
}

void PeerMessage::get(const std::string &key, int16_t *value, int16_t def) {
  _get(key, value, def);
}

void PeerMessage::get(const std::string &key, uint16_t *value,
                      uint16_t def) {
  _get(key, value, def);
}

void PeerMessage::get(const std::string &key, int32_t *value, int32_t def) {
  _get(key, value, def);
}

void PeerMessage::get(const std::string &key, uint32_t *value,
                      uint32_t def) {
  _get(key, value, def);
}

void PeerMessage::get(const std::string &key, std::string *value,
                      const std::string &def) {
  if (_keys.find(key) == _keys.end()) {
    *value = def;
    return;
  }

  *value = _keys[key];
}


template<typename T>
void PeerMessage::_get(const std::string &key, T *value, T def) {
  std::stringstream strm;

  if (_keys.find(key) == _keys.end()) {
    *value = def;
    return;
  }

  strm << _keys[key];
  strm >> *value;
}

void PeerMessage::set(const std::string &key, int8_t value) {
  _set(key, value);
}

void PeerMessage::set(const std::string &key, uint8_t value) {
  _set(key, value);
}

void PeerMessage::set(const std::string &key, int16_t value) {
  _set(key, value);
}

void PeerMessage::set(const std::string &key, uint16_t value) {
  _set(key, value);
}

void PeerMessage::set(const std::string &key, int32_t value) {
  _set(key, value);
}

void PeerMessage::set(const std::string &key, uint32_t value) {
  _set(key, value);
}

void PeerMessage::set(const std::string &key, const std::string &value) {
  _keys[key] = value;
}

template<typename T>
void PeerMessage::_set(const std::string &key, T value) {
  std::stringstream strm;

  strm << value;
  _keys[key] = strm.str();
}

void PeerMessage::unset(const std::string &key) {
  if (_keys.find(key) == _keys.end()) {
    return;
  }

  _keys.erase(key);
}

bool PeerMessage::_serializeFunc(DataStream *dataStream) {
  return false;
}

bool PeerMessage::_serializeChunk(DataStream *dataStream) {
  return false;
}

bool PeerMessage::_serializeRequest(DataStream *dataStream) {
  std::string hash;
  uint32_t segment;
  uint32_t chunk;

  get("hash", &hash, "");
  if (hash == "") {
    return false;
  }

  get("segment", &segment, 0);
  get("chunk", &chunk, 0);

  dataStream->write(hash);
  dataStream->write(segment);
  dataStream->write(chunk);
  return true;
}

bool PeerMessage::serialize(DataStream *dataStream) {
  dataStream->write(_type);

  switch (_type) {
    case kPing:
      return true;
    case kRequest:
      return _serializeRequest(dataStream);
    case kChunk:
      return _serializeChunk(dataStream);
    default:
      break;
  }

  return false;
}

bool PeerMessage::_unserializeFunc(DataStream *dataStream) {
  return false;
}

bool PeerMessage::_unserializeRequest(DataStream *dataStream) {
  std::string hash;
  uint32_t segment;
  uint32_t chunk;

  dataStream->read(&hash);
  dataStream->read(&segment);
  dataStream->read(&chunk);

  set("hash", hash);
  set("segment", segment);
  set("chunk", chunk);
  return true;
}

bool PeerMessage::_unserializeChunk(DataStream *dataStream) {
  std::string hash;
  uint32_t segment;
  uint32_t chunk;
  uint32_t offset;
  uint32_t length;

  dataStream->read(&hash);
  dataStream->read(&segment);
  dataStream->read(&chunk);
  dataStream->read(&offset);
  dataStream->read(&length);

  set("hash", hash);
  set("segment", segment);
  set("chunk", chunk);
  set("offset", offset);
  set("length", length);
  return true;
}

bool PeerMessage::unserialize(DataStream *dataStream) {
  dataStream->read(&_type);

  switch (_type) {
    case kPing:
      return true;
    case kRequest:
      return _unserializeRequest(dataStream);
    case kChunk:
      return _unserializeChunk(dataStream);
    default:
      break;
  }

  return false;
}

}  // namespace peeracle
