#ifndef PEERACLE_MANAGER_H_
#define PEERACLE_MANAGER_H_

#include <assert.h>

namespace peeracle {

class Manager {
 public:
  Manager();
  ~Manager();

  bool Update();
  void *getWorkerThread();
  void *getSignalingThread();

  static Manager& getSingleton() {
    assert(singleton_ != NULL);
    return *singleton_;
  };

  static Manager* getSingletonPtr() {
    assert(singleton_ != NULL);
    return singleton_;
  };

 protected:
  static Manager* singleton_;

 private:
  class ManagerImpl;
  ManagerImpl *manager_;
};

}

#endif // PEERACLE_MANAGER_H_
