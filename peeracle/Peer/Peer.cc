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

#include "third_party/webrtc/talk/app/webrtc/test/fakeconstraints.h"
#include "third_party/webrtc/talk/app/webrtc/peerconnectioninterface.h"
#include "peeracle/Peer/Peer.h"

namespace peeracle {

Peer::Peer() {
  webrtc::PeerConnectionInterface::IceServers iceServers;
  webrtc::PeerConnectionInterface::IceServer iceServer;
  iceServer.uri = "stun:stun.l.google.com:19302";
  iceServers.push_back(iceServer);

  webrtc::FakeConstraints constr;
  constr.AddOptional(webrtc::MediaConstraintsInterface::kEnableDtlsSrtp,
                     webrtc::MediaConstraintsInterface::kValueTrue);
  constr.AddMandatory(webrtc::MediaConstraintsInterface::kOfferToReceiveAudio,
                      webrtc::MediaConstraintsInterface::kValueFalse);
  constr.AddMandatory(webrtc::MediaConstraintsInterface::kOfferToReceiveVideo,
                      webrtc::MediaConstraintsInterface::kValueFalse);
}

}  // namespace peeracle
