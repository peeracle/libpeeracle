#include <iostream>
#include "webrtc/base/ssladapter.h"
#include "webrtc/base/thread.h"
#include "manager.h"

namespace peeracle {

Manager *Manager::singleton_ = NULL;

class Manager::ManagerImpl {
 public:
  rtc::Thread *worker_thread_;
  rtc::Thread *signaling_thread_;
};

Manager::Manager() : manager_(new ManagerImpl) {
  singleton_ = this;

  rtc::InitializeSSL();
  rtc::ThreadManager::Instance()->WrapCurrentThread();

  manager_->worker_thread_ = new rtc::Thread();
  manager_->worker_thread_->SetName("worker_thread", NULL);

  manager_->signaling_thread_ = new rtc::Thread();
  manager_->signaling_thread_->SetName("signaling_thread", NULL);

  if (!manager_->worker_thread_->Start() ||
    !manager_->signaling_thread_->Start())
    std::cerr << "Failed to start threads" << std::endl;
}

Manager::~Manager() {
  delete manager_;
  rtc::CleanupSSL();
}

bool Manager::Update() {
  rtc::Thread *thread = rtc::Thread::Current();

  return thread->ProcessMessages(0);
}

void *Manager::getSignalingThread() {
  return manager_->signaling_thread_;
}

void *Manager::getWorkerThread() {
  return manager_->worker_thread_;
}

}
