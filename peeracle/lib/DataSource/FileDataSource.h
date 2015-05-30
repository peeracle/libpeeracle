//
// Created by axel on 5/30/15.
//

#ifndef LIBPEERACLE_FILEDATASOURCE_H
#define LIBPEERACLE_FILEDATASOURCE_H

#include "DataSourceInterface.h"

namespace peeracle {

namespace DataSource {

class FileDataSource
  : public DataSourceInterface {

 public:
  size_t open();
  void close();
  int read(unsigned char *buffer, int length);

 protected:
  virtual ~FileDataSource() {}
};

}

}


#endif //LIBPEERACLE_FILEDATASOURCE_H
