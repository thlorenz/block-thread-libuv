#include <fstream>
#include <vector>
#include <unistd.h>
#include <uv.h>
#include "rapidjson_writable.h"


void write_chunks(const char* file, Writable& writable) {
  std::ifstream ifs(file);
  std::vector<char> buffer (64000, 0); // 64K bytes chunk size

  while(ifs.read(buffer.data(), buffer.size())) {
    writable.write(buffer);
    sleep(1);
  }
}

int main(int argc, const char* argv[]) {
  const char* file = argv[1];

  Writable writable;
  write_chunks(file, writable);
}
