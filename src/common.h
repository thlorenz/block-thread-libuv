#ifndef COMMON_H
#define COMMON_H

#include <uv.h>
#include <vector>

typedef struct {
  uv_cond_t cv;
  uv_mutex_t mutex;
  uv_thread_t thread;
  std::vector<std::vector<char>> chunks;
} worker_t;

#endif
