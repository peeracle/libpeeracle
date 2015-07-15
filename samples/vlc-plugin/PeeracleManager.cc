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

#include <iostream>
#include <string>
#include <vector>

#include "peeracle/peeracle.h"
#include "samples/vlc-plugin/PeeracleManager.h"
#include "VLCDataStream.h"
#include "peeracle/Peer/Peer.h"

static peeracle::Peer *peerA;
static peeracle::Peer *peerB;

static bool peerAReady = false;
static bool peerBReady = false;

typedef struct s_iceCandidate {
  std::string sdpMid;
  int sdpMLineIndex;
  std::string candidate;
} t_iceCandidate;

static std::vector<t_iceCandidate> iceCandidatesA;
static std::vector<t_iceCandidate> iceCandidatesB;

class MyPeerObserverA : public peeracle::PeerInterface::Observer {
 public:
  void onIceCandidate(const std::string &sdpMid,
                      int sdpMLineIndex,
                      const std::string &candidate) {
    std::cout << "[MyPeerObserverA::onIceCandidate] " << candidate << std::endl;

    if (peerBReady) {
      std::cout << "[MyPeerObserverA::onIceCandidate] peerB is ready." <<
      std::endl;
      peerB->AddICECandidate(sdpMid, sdpMLineIndex, candidate);
      return;
    }

    t_iceCandidate ic;
    ic.sdpMid = sdpMid;
    ic.sdpMLineIndex = sdpMLineIndex;
    ic.candidate = candidate;
    iceCandidatesB.push_back(ic);
  }

  void onSignalingChange(int state) {
    std::cout << "[MyPeerObserverA::onSignalingChange] " << state << std::endl;
  }

  void onStateChange(int state) {
    std::cout << "[MyPeerObserverA::onStateChange] " << state << std::endl;
  }

  void onIceConnectionChange(int state) {
    std::cout << "[MyPeerObserverA::onIceConnectionChange] " << state <<
    std::endl;
  }

  void onIceGatheringChange(int state) {
    std::cout << "[MyPeerObserverA::onIceGatheringChange] " << state <<
    std::endl;
  }
};

class MySetSDPObserverA : public peeracle::PeerInterface::SetSDPObserver {
 public:
  void onSuccess() {
    std::cout << "[MySetSDPObserverA::onSuccess]" << std::endl;
    peerAReady = true;
    peerBReady = true;

    for (std::vector<t_iceCandidate>::iterator it = iceCandidatesA.begin();
         it != iceCandidatesA.end(); ++it) {
      t_iceCandidate ic = (*it);
      peerA->AddICECandidate(ic.sdpMid, ic.sdpMLineIndex, ic.candidate);
    }

    iceCandidatesA.clear();

    peerBReady = true;
    for (std::vector<t_iceCandidate>::iterator it = iceCandidatesB.begin();
         it != iceCandidatesB.end(); ++it) {
      t_iceCandidate ic = (*it);
      peerB->AddICECandidate(ic.sdpMid, ic.sdpMLineIndex, ic.candidate);
    }

    iceCandidatesB.clear();
  }

  void onFailure(const std::string &error) {
    std::cout << "[MySetSDPObserverA::onFailure] " << error << std::endl;
  }
};

class MyCreateSDPObserverB : public peeracle::PeerInterface::CreateSDPObserver {
 public:
  void onSuccess(const std::string &sdp,
                 const std::string &type) {
    std::cout << "[MyCreateSDPObserverB::onSuccess] type " << type << std::endl;
    std::cout << "SDP data {" << sdp << "}" << std::endl;

    MySetSDPObserverA *setSDPObserverA;
    setSDPObserverA = new MySetSDPObserverA();

    peerA->SetAnswer(sdp, setSDPObserverA);
  }

  void onFailure(const std::string &error) {
    std::cout << "[MyCreateSDPObserverB::onFailure] " << error << std::endl;
  }
};

class MyCreateSDPObserverA : public peeracle::PeerInterface::CreateSDPObserver {
 public:
  void onSuccess(const std::string &sdp,
                 const std::string &type) {
    std::cout << "[MyCreateSDPObserverA::onSuccess] type " << type << std::endl;
    std::cout << "SDP data {" << sdp << "}" << std::endl;

    MyCreateSDPObserverB *createAnswerObserverB;
    createAnswerObserverB = new MyCreateSDPObserverB();

    peerB->CreateAnswer(sdp, createAnswerObserverB);
  }

  void onFailure(const std::string &error) {
    std::cout << "[MyCreateSDPObserverA::onFailure] " << error << std::endl;
  }
};

class MyPeerObserverB : public peeracle::PeerInterface::Observer {
 public:
  void onIceCandidate(const std::string &sdpMid,
                      int sdpMLineIndex,
                      const std::string &candidate) {
    std::cout << "[MyPeerObserverB::onIceCandidate] " << candidate << std::endl;

    if (peerAReady) {
      std::cout << "[MyPeerObserverB::onIceCandidate] peerA is ready." <<
      std::endl;
      peerA->AddICECandidate(sdpMid, sdpMLineIndex, candidate);
      return;
    }

    t_iceCandidate ic;
    ic.sdpMid = sdpMid;
    ic.sdpMLineIndex = sdpMLineIndex;
    ic.candidate = candidate;
    iceCandidatesA.push_back(ic);
  }

  void onSignalingChange(int state) {
    std::cout << "[MyPeerObserverB::onSignalingChange] " << state << std::endl;
  }

  void onStateChange(int state) {
    std::cout << "[MyPeerObserverB::onStateChange] " << state << std::endl;
  }

  void onIceConnectionChange(int state) {
    std::cout << "[MyPeerObserverB::onIceConnectionChange] " << state <<
    std::endl;
  }

  void onIceGatheringChange(int state) {
    std::cout << "[MyPeerObserverB::onIceGatheringChange] " << state <<
    std::endl;
  }
};

PeeracleManager::PeeracleManager(demux_t *demux) : _initiated(false),
                                                   _vlc(demux) {
}

PeeracleManager::~PeeracleManager() {
  if (peerA) {
    delete peerA;
  }
  if (peerB) {
    delete peerB;
  }
  if (_initiated) {
    peeracle::cleanup();
  }
}

bool PeeracleManager::Init() {
  stream_t *metadataStream = this->_vlc->s;

  this->_metadataDataStream = new VLCDataStream(metadataStream);
  this->_metadata = new peeracle::Metadata();

  return this->_metadata->unserialize(this->_metadataDataStream);
}

int PeeracleManager::Control(int i_query, va_list args) {
  switch (i_query) {
    case DEMUX_GET_POSITION:
      msg_Dbg(this->_vlc, "[Peeracle::Control] DEMUX_GET_POSITION");
      break;
    case DEMUX_SET_POSITION:
      msg_Dbg(this->_vlc, "[Peeracle::Control] DEMUX_SET_POSITION");
      break;
    case DEMUX_GET_LENGTH:
      msg_Dbg(this->_vlc, "[Peeracle::Control] DEMUX_GET_LENGTH");
      break;
    case DEMUX_GET_TIME:
      msg_Dbg(this->_vlc, "[Peeracle::Control] DEMUX_GET_TIME");
      break;
    case DEMUX_SET_TIME:
      msg_Dbg(this->_vlc, "[Peeracle::Control] DEMUX_SET_TIME");
      break;
    case DEMUX_GET_TITLE_INFO:
      msg_Dbg(this->_vlc, "[Peeracle::Control] DEMUX_GET_TITLE_INFO");
      break;
    case DEMUX_SET_TITLE:
      msg_Dbg(this->_vlc, "[Peeracle::Control] DEMUX_SET_TITLE");
      break;
    case DEMUX_SET_SEEKPOINT:
      msg_Dbg(this->_vlc, "[Peeracle::Control] DEMUX_SET_SEEKPOINT");
      break;
    case DEMUX_SET_GROUP:
      msg_Dbg(this->_vlc, "[Peeracle::Control] DEMUX_SET_GROUP");
      break;
#ifdef DEMUX_SET_ES
    case DEMUX_SET_ES:
      msg_Dbg(this->_vlc, "[Peeracle::Control] DEMUX_SET_ES");
      break;
#endif
    case DEMUX_SET_NEXT_DEMUX_TIME:
      msg_Dbg(this->_vlc, "[Peeracle::Control] DEMUX_SET_NEXT_DEMUX_TIME");
      break;
    case DEMUX_GET_FPS:
      msg_Dbg(this->_vlc, "[Peeracle::Control] DEMUX_GET_FPS");
      break;
    case DEMUX_GET_META:
    {
      vlc_meta_t *p_meta = va_arg(args, vlc_meta_t*);
      vlc_meta_t *meta = vlc_meta_New();

      msg_Dbg(this->_vlc, "[Peeracle::Control] DEMUX_GET_META");
      if (meta == NULL)
        return VLC_EGENERIC;

      vlc_meta_SetTitle(meta, "Metadata Title");
      vlc_meta_SetPublisher(meta, "Metadata Publisher");
      vlc_meta_SetCopyright(meta, "Metadata Copyright");
      vlc_meta_SetURL(meta, "Metadata URL");

      vlc_meta_Merge(p_meta, meta);
      vlc_meta_Delete(meta);
      return VLC_SUCCESS;
    }

    case DEMUX_HAS_UNSUPPORTED_META:
      msg_Dbg(this->_vlc, "[Peeracle::Control] DEMUX_HAS_UNSUPPORTED_META");
      break;
    case DEMUX_GET_ATTACHMENTS:
      msg_Dbg(this->_vlc, "[Peeracle::Control] DEMUX_GET_ATTACHMENTS");
      break;
    case DEMUX_CAN_RECORD:
      msg_Dbg(this->_vlc, "[Peeracle::Control] DEMUX_CAN_RECORD");
      break;
    case DEMUX_SET_RECORD_STATE:
      msg_Dbg(this->_vlc, "[Peeracle::Control] DEMUX_SET_RECORD_STATE");
      break;
#ifdef DEMUX_GET_SIGNAL
    case DEMUX_GET_SIGNAL:
      msg_Dbg(this->_vlc, "[Peeracle::Control] DEMUX_GET_SIGNAL");
      break;
#endif
    case DEMUX_CAN_PAUSE:
      msg_Dbg(this->_vlc, "[Peeracle::Control] DEMUX_CAN_PAUSE = 0x1000");
      break;
    case DEMUX_SET_PAUSE_STATE:
      msg_Dbg(this->_vlc, "[Peeracle::Control] DEMUX_SET_PAUSE_STATE");
      break;
    case DEMUX_GET_PTS_DELAY:
      msg_Dbg(this->_vlc, "[Peeracle::Control] DEMUX_GET_PTS_DELAY");
      break;
    case DEMUX_CAN_CONTROL_PACE:
      *(va_arg(args, bool *)) = true;
      return VLC_SUCCESS;
    case DEMUX_CAN_CONTROL_RATE:
      msg_Dbg(this->_vlc, "[Peeracle::Control] DEMUX_CAN_CONTROL_RATE");
      break;
    case DEMUX_SET_RATE:
      msg_Dbg(this->_vlc, "[Peeracle::Control] DEMUX_SET_RATE");
      break;
    case DEMUX_CAN_SEEK:
      msg_Dbg(this->_vlc, "[Peeracle::Control] DEMUX_CAN_SEEK");
      break;
#ifdef DEMUX_IS_PLAYLIST
    case DEMUX_IS_PLAYLIST:
      msg_Dbg(this->_vlc, "[Peeracle::Control] DEMUX_IS_PLAYLIST");
      break;
#endif
    case DEMUX_NAV_ACTIVATE:
      msg_Dbg(this->_vlc, "[Peeracle::Control] DEMUX_NAV_ACTIVATE");
      break;
    case DEMUX_NAV_UP:
      msg_Dbg(this->_vlc, "[Peeracle::Control] DEMUX_NAV_UP");
      break;
    case DEMUX_NAV_DOWN:
      msg_Dbg(this->_vlc, "[Peeracle::Control] DEMUX_NAV_DOWN");
      break;
    case DEMUX_NAV_LEFT:
      msg_Dbg(this->_vlc, "[Peeracle::Control] DEMUX_NAV_LEFT");
      break;
    case DEMUX_NAV_RIGHT:
      msg_Dbg(this->_vlc, "[Peeracle::Control] DEMUX_NAV_RIGHT");
      break;
    default:
      break;
  }
  return VLC_EGENERIC;
}

int PeeracleManager::Demux() {
  return VLC_DEMUXER_SUCCESS;
}
