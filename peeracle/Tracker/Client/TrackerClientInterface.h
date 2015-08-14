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

#ifndef PEERACLE_TRACKER_CLIENT_TRACKERCLIENTINTERFACE_H_
#define PEERACLE_TRACKER_CLIENT_TRACKERCLIENTINTERFACE_H_

#include <stdint.h>
#include <string>

namespace peeracle {

class TrackerClientInterface {
 public:
  virtual ~TrackerClientInterface() {}

  virtual bool Init() = 0;
  virtual bool Connect() = 0;
  virtual bool Update() = 0;

  virtual void announce(const std::string id, uint32_t got) = 0;
  virtual const std::string &getUrl() const = 0;
};

}  // namespace peeracle

#endif  // PEERACLE_TRACKER_CLIENT_TRACKERCLIENTINTERFACE_H_
