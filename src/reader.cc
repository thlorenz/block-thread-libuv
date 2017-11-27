#include "reader.h"

void Reader::read_(void* data) {
  Reader* self = static_cast<Reader*>(data);
  worker_t& work = self->work_;
  while(1) {
    // access shared buffer
    uv_mutex_lock(&work.mutex);

    // if we are out, wait until the next chunk arrives
    while (work.chunks.size() == 0) {
      uv_cond_wait(&work.cv, &work.mutex);
    }

    std::vector<char> chunk = work.chunks.front();
    fprintf(stderr, "Processing chunk of size %ld\n", chunk.size());
    work.chunks.erase(work.chunks.begin());

    uv_mutex_unlock(&work.mutex);
  }
}

worker_t* Reader::start() {
  assert(0 == uv_mutex_init(&work_.mutex));
  assert(0 == uv_cond_init(&work_.cv));
  uv_thread_create(&thread_, read_, this);
  work_.thread = thread_;
  return &work_;
}
