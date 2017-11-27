#include <fstream>
#include <vector>
#include <assert.h>
#include <unistd.h>
#include <uv.h>
#include "reader.h"


// http://roxlu.com/2013/016/consumer---producer-model-with-libuv
void write_chunks(const char* file, worker_t& work) {

  std::ifstream ifs(file);
  std::vector<char> buffer (64000, 0); // 64K bytes chunk size

  while(ifs.read(buffer.data(), buffer.size())) {
    std::streamsize size = ifs.gcount();

    uv_mutex_lock(&work.mutex);
    work.chunks.push_back(buffer);
    uv_cond_signal(&work.cv);
    uv_mutex_unlock(&work.mutex);

    fprintf(stderr, "pushed chunk of length %ld\n", size);
    sleep(1);
  }
}

int main(int argc, const char* argv[]) {
  const char* file = argv[1];

  Reader reader;
  worker_t* work = reader.start();

  // the writer runs on main thread
  write_chunks(file, *work);
}
