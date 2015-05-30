//
// Created by axel on 5/30/15.
//

#ifndef LIBPEERACLE_HTTPDATASOURCE_H
#define LIBPEERACLE_HTTPDATASOURCE_H

#include "DataSourceInterface.h"

namespace peeracle {

namespace DataSource {

class HttpDataSource
  : public DataSourceInterface {

 public:
  size_t open();
  void close();
  int read(unsigned char *buffer, int length);

 protected:
  virtual ~HttpDataSource() {}
};

}

}

#endif //LIBPEERACLE_HTTPDATASOURCE_H
