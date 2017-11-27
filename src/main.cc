#include <fstream>
#include <vector>
#include <assert.h>
#include <unistd.h>
#include <uv.h>

// http://roxlu.com/2013/016/consumer---producer-model-with-libuv
typedef struct {
  uv_cond_t cv;
  uv_mutex_t mutex;
  uv_thread_t thread;
  std::vector<std::vector<char>> chunks;
} worker_t;


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

void process_chunks(void* data) {
  worker_t* work = static_cast<worker_t*>(data);
  while(1) {
    // access shared buffer
    uv_mutex_lock(&work->mutex);

    // if we are out, wait until the next chunk arrives
    while (work->chunks.size() == 0) {
      uv_cond_wait(&work->cv, &work->mutex);
    }

    std::vector<char> chunk = work->chunks.front();
    fprintf(stderr, "Processing chunk of size %ld\n", chunk.size());
    work->chunks.erase(work->chunks.begin());

    uv_mutex_unlock(&work->mutex);
  }
}

void initiate_reader(uv_thread_t& thread, worker_t& work) {
  // reader runs on background thread
  assert(0 == uv_mutex_init(&work.mutex));
  assert(0 == uv_cond_init(&work.cv));
  uv_thread_create(&thread, process_chunks, &work);
  work.thread = thread;
}

int main(int argc, const char* argv[]) {
  const char* file = argv[1];

  uv_thread_t thread;
  worker_t work;
  initiate_reader(thread, work);

  // the writer runs on main thread
  write_chunks(file, work);
}
