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

#include "third_party/webrtc/webrtc/base/ssladapter.h"
#include "peeracle/peeracle.h"

namespace peeracle {

static rtc::Thread *_signalingThread = NULL;
static rtc::Thread *_workerThread = NULL;
static webrtc::PeerConnectionFactoryInterface *_peerConnectionFactory = NULL;

rtc::Thread *getSignalingThread() {
  return _signalingThread;
}

rtc::Thread *getWorkerThread() {
  return _workerThread;
}

webrtc::PeerConnectionFactoryInterface *getPeerConnectionFactory() {
  return _peerConnectionFactory;
}

bool init() {
  rtc::InitializeSSL();
  rtc::ThreadManager::Instance()->WrapCurrentThread();

  _signalingThread = new rtc::Thread();
  _workerThread = new rtc::Thread();

  _signalingThread->SetName("signaling_thread", NULL);
  _workerThread->SetName("worker_thread", NULL);

  ASSERT(_signalingThread->Start() && _workerThread->Start());

  _peerConnectionFactory =
    webrtc::CreatePeerConnectionFactory(_signalingThread,
                                        _workerThread,
                                        NULL, NULL, NULL).release();
  return true;
}

bool update() {
  return rtc::Thread::Current()->ProcessMessages(0);
}

bool cleanup() {
  _peerConnectionFactory->Release();
  _peerConnectionFactory = NULL;

  _signalingThread->Stop();
  _workerThread->Stop();

  delete _signalingThread;
  delete _workerThread;

  _signalingThread = NULL;
  _workerThread = NULL;

  return rtc::CleanupSSL();
}

}  // namespace peeracle
