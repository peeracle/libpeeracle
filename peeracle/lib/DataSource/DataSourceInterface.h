//
// Created by axel on 5/30/15.
//

#ifndef LIBPEERACLE_DATASOURCEINTERFACE_H
#define LIBPEERACLE_DATASOURCEINTERFACE_H

#include <cstdlib>

namespace peeracle {

namespace DataSource {

class DataSourceInterface {
 public:
  virtual size_t open() = 0;
  virtual void close() = 0;
  virtual int read(unsigned char *buffer, int length) = 0;

 protected:
  virtual ~DataSourceInterface() {}
};

}

}

#endif //LIBPEERACLE_DATASOURCEINTERFACE_H
