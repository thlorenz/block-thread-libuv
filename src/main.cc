#include <fstream>
#include <vector>
#include <unistd.h>
#include <uv.h>
#include "reader.h"
#include "writer.h"


// http://roxlu.com/2013/016/consumer---producer-model-with-libuv
void write_chunks(const char* file, Writer& writer) {
  std::ifstream ifs(file);
  std::vector<char> buffer (64000, 0); // 64K bytes chunk size

  while(ifs.read(buffer.data(), buffer.size())) {
    writer.write(buffer);
    sleep(1);
  }
}

int main(int argc, const char* argv[]) {
  const char* file = argv[1];

  // reader creates it's own thread
  Reader reader;
  worker_t& work = reader.start();

  // writer runs on main thread
  Writer writer(work);
  write_chunks(file, writer);
}
