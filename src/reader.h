#ifndef READER_H
#define READER_H

#include <assert.h>
#include "common.h"

class Reader {
  public:
    worker_t* start();

  private:
    worker_t work_;
    uv_thread_t thread_;
    static void read_(void* data);
};

#endif
