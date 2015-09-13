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

#include "third_party/webrtc/third_party/jsoncpp/source/include/json/reader.h"
#include "third_party/webrtc/third_party/jsoncpp/source/include/json/writer.h"

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

bool TrackerMessage::_serializeWelcome(DataStream *dataStream) {
  std::string id;

  get("id", &id, "");
  if (id == "") {
    return false;
  }

  dataStream->write(id);
  return true;
}

bool TrackerMessage::_serializeAnnounce(DataStream *dataStream) {
  std::string hash;
  std::stringstream strm;
  uint32_t got;
  uint32_t gotCount;

  get("hash", &hash, "");
  if (hash == "") {
    return false;
  }

  dataStream->write(hash);

  get("got", &gotCount, 0);
  dataStream->write(gotCount);

  for (uint32_t i = 0; i < gotCount; ++i) {
    strm.clear();
    strm.str("");
    strm << "got" << i;
    get(strm.str(), &got, 0);
    dataStream->write(got);
  }
  return true;
}

bool TrackerMessage::_serializeEnter(DataStream *dataStream) {
  std::string hash;
  std::string peer;
  uint32_t got;
  uint32_t gotCount;
  std::stringstream strm;

  get("hash", &hash, "");
  if (hash == "") {
    return false;
  }

  get("peer", &peer, "");
  if (peer == "") {
    return false;
  }

  get("got", &gotCount, 0);

  dataStream->write(hash);
  dataStream->write(peer);
  dataStream->write(gotCount);

  for (uint32_t i = 0; i < gotCount; ++i) {
    strm.clear();
    strm.str("");
    strm << "got" << i;
    get(strm.str(), &got, 0);
    dataStream->write(got);
  }

  return true;
}

bool TrackerMessage::_serializePoke(DataStream *dataStream) {
  return _serializeEnter(dataStream);
}

bool TrackerMessage::_serializeSdp(DataStream *dataStream) {
  std::string id;
  std::string hash;
  std::string type;

  get("id", &id, "");
  if (id == "") {
    return false;
  }

  dataStream->write(id);

  get("hash", &hash, "");
  if (hash == "") {
    return false;
  }

  dataStream->write(hash);

  get("type", &type, "");
  if (type == "") {
    return false;
  }

  Json::FastWriter writer;
  Json::Value jmessage;

  if (type == "ice") {
    std::string sdpMid;
    uint32_t sdpMLineIndex;
    std::string candidate;
    get("sdpMid", &sdpMid, "");
    get("sdpMLineIndex", &sdpMLineIndex, 0);
    get("candidate", &candidate, "");

    jmessage["sdpMid"] = sdpMid;
    jmessage["sdpMLineIndex"] = sdpMLineIndex;
    jmessage["candidate"] = candidate;

    dataStream->write(writer.write(jmessage));
    return true;
  } else if (type != "offer" && type != "answer") {
    return false;
  }

  std::string sdp;

  jmessage["type"] = type;

  get("sdp", &sdp, "");
  if (sdp == "") {
    return false;
  }

  jmessage["sdp"] = sdp;

  dataStream->write(writer.write(jmessage));
  return true;
}

bool TrackerMessage::serialize(DataStream *dataStream) {
  dataStream->write(_type);

  switch (_type) {
    case kKeepAlive:
    case kHello:
      return true;
    case kWelcome:
      return _serializeWelcome(dataStream);
    case kAnnounce:
      return _serializeAnnounce(dataStream);
    case kEnter:
      return _serializeEnter(dataStream);
    case kPoke:
      return _serializePoke(dataStream);
    case kSdp:
      return _serializeSdp(dataStream);
    default:
      break;
  }

  return false;
}

bool TrackerMessage::_unserializeWelcome(DataStream *dataStream) {
  std::string id;

  dataStream->read(&id);
  set("id", id);
  return true;
}

bool TrackerMessage::_unserializeAnnounce(DataStream *dataStream) {
  std::string hash;
  uint32_t got;
  uint32_t gotCount;
  std::stringstream strm;

  dataStream->read(&hash);
  dataStream->read(&gotCount);

  set("hash", hash);
  set("got", gotCount);

  for (uint32_t i = 0; i < gotCount; ++i) {
    strm.clear();
    strm.str("");
    strm << "got" << i;
    dataStream->read(&got);
    set(strm.str(), got);
  }

  return true;
}

bool TrackerMessage::_unserializeEnter(DataStream *dataStream) {
  std::string hash;
  std::string peer;
  uint32_t got;
  uint32_t gotCount;
  std::stringstream strm;

  dataStream->read(&hash);
  dataStream->read(&peer);
  dataStream->read(&gotCount);

  set("hash", hash);
  set("peer", peer);
  set("got", gotCount);

  std::cout << "unserializeEnter " << hash << " " << peer << " " <<
    gotCount << std::endl;

  for (uint32_t i = 0; i < gotCount; ++i) {
    strm.clear();
    strm.str("");
    strm << "got" << i;
    dataStream->read(&got);
    set(strm.str(), got);
    std::cout << "got" << i << " = " << got << std::endl;
  }

  return true;
}

bool TrackerMessage::_unserializePoke(DataStream *dataStream) {
  return _unserializeEnter(dataStream);
}

bool TrackerMessage::_unserializeSdp(DataStream *dataStream) {
  std::string id;
  std::string hash;
  std::string jsdp;

  dataStream->read(&id);
  dataStream->read(&hash);
  dataStream->read(&jsdp);

  Json::Reader reader;
  Json::Value jmessage;

  if (!reader.parse(jsdp, jmessage) || !jmessage.isObject()) {
    return false;
  }

  set("id", id);
  set("hash", hash);

  if (jmessage.isMember("type") && jmessage.isMember("sdp")) {
    Json::Value vtype;
    Json::Value vsdp;

    vtype = jmessage["type"];
    if (!vtype.isString()) {
      return false;
    }

    vsdp = jmessage["sdp"];
    if (!vsdp.isString()) {
      return false;
    }

    set("type", vtype.asString());
    set("sdp", vsdp.asString());
    return true;
  } else if (jmessage.isMember("candidate") && jmessage.isMember("sdpMid") &&
    jmessage.isMember("sdpMLineIndex")) {
    Json::Value vcandidate;
    Json::Value vsdpMid;
    Json::Value vsdpMLineIndex;

    vcandidate = jmessage["candidate"];
    if (!vcandidate.isString()) {
      return false;
    }

    vsdpMid = jmessage["sdpMid"];
    if (!vsdpMid.isString()) {
      return false;
    }

    vsdpMLineIndex = jmessage["sdpMLineIndex"];
    if (!vsdpMLineIndex.isInt()) {
      return false;
    }

    set("type", "ice");
    set("candidate", vcandidate.asString());
    set("sdpMid", vsdpMid.asString());
    set("sdpMLineIndex", vsdpMLineIndex.asInt());
    return true;
  }

  return false;
}

bool TrackerMessage::unserialize(DataStream *dataStream) {
  dataStream->read(&_type);

  switch (_type) {
    case kKeepAlive:
    case kHello:
      return true;
    case kWelcome:
      return _unserializeWelcome(dataStream);
    case kAnnounce:
      return _unserializeAnnounce(dataStream);
    case kEnter:
      return _unserializeEnter(dataStream);
    case kPoke:
      return _unserializePoke(dataStream);
    case kSdp:
      return _unserializeSdp(dataStream);
    default:
      break;
  }

  return false;
}

}  // namespace peeracle
