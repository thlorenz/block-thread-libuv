#include "writer.h"

void Writer::write(const std::vector<char> chunk) {
  const size_t size = chunk.size();

  uv_mutex_lock(&work_.mutex);
  work_.chunks.push_back(chunk);
  uv_cond_signal(&work_.cv);
  uv_mutex_unlock(&work_.mutex);

  fprintf(stderr, "pushed chunk of length %ld\n", size);
}
