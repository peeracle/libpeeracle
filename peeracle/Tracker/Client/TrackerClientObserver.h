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

#ifndef PEERACLE_TRACKER_CLIENT_TRACKERCLIENTOBSERVER_H_
#define PEERACLE_TRACKER_CLIENT_TRACKERCLIENTOBSERVER_H_

#include <string>

namespace peeracle {

class TrackerClientObserver {
 public:
  virtual void onConnect(const std::string &id) = 0;
  virtual void onDisconnect() = 0;
  virtual void onConnectionError() = 0;
  virtual void onPeerConnect(const std::string &hash, const std::string &peerId,
                             uint32_t got, bool poke) = 0;

 protected:
  virtual ~TrackerClientObserver() { }
};

}  // namespace peeracle

#endif  // PEERACLE_TRACKER_CLIENT_TRACKERCLIENTOBSERVER_H_
