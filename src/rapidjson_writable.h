#ifndef RAPIDJSON_WRITABLE_H
#define RAPIDJSON_WRITABLE_H

#include "common.h"
#include <assert.h>

class Writable {
  public:
    Writable();
    void write(const std::vector<char> chunk);

  private:
    worker_t work_;
    uv_thread_t thread_;
    static void read_(void* data);
};
#endif
