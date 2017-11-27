#ifndef WRITER_H
#define WRITER_H

#include <assert.h>
#include "common.h"

class Writer {
  public:
    Writer(worker_t& work) : work_(work) {}
    void write(const std::vector<char> chunk);

  private:
    worker_t& work_;
};

#endif
