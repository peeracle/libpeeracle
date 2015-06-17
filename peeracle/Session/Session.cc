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

#include "third_party/webrtc/talk/app/webrtc/peerconnectioninterface.h"
#include "third_party/webrtc/webrtc/base/thread.h"
#include "peeracle/Session/Session.h"

namespace peeracle {

Session::Session() : _signalingThread(new rtc::Thread()),
                     _workerThread(new rtc::Thread()),
                     _pcfi(NULL) {
  rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> pcfi;

  rtc::ThreadManager::Instance()->WrapCurrentThread();

  _signalingThread.get()->SetName("signaling_thread", NULL);
  _workerThread.get()->SetName("worker_thread", NULL);

  ASSERT(_signalingThread.get()->Start() && _workerThread.get()->Start());

  _pcfi = webrtc::CreatePeerConnectionFactory(_signalingThread.get(),
                                              _workerThread.get(),
                                              NULL, NULL, NULL);
}

bool Session::Update() {
  rtc::Thread *thread = rtc::Thread::Current();

  return thread->ProcessMessages(0);
}

void *Session::getSignalingThread() {
  return _signalingThread.get();
}

void *Session::getWorkerThread() {
  return _workerThread.get();
}

}  // namespace peeracle
