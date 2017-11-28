#include "rapidjson_writable.h"

Writable::Writable() {
  assert(0 == uv_mutex_init(&work_.mutex));
  assert(0 == uv_cond_init(&work_.cv));
  uv_thread_create(&thread_, read_, this);
  work_.thread = thread_;
}

void Writable::write(const std::vector<char> chunk) {
  const size_t size = chunk.size();

  uv_mutex_lock(&work_.mutex);
  work_.chunks.push_back(chunk);
  uv_cond_signal(&work_.cv);
  uv_mutex_unlock(&work_.mutex);

  fprintf(stderr, "pushed chunk of length %ld\n", size);
}

void Writable::read_(void* data) {
  Writable* self = static_cast<Writable*>(data);
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
