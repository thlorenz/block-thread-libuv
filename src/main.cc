#include <fstream>
#include <vector>
#include <uv.h>

void read_file(const char* file) {

  std::ifstream ifs(file);
  std::vector<char> buffer (64000, 0); // 64K bytes chunk size

  while(ifs.read(buffer.data(), buffer.size())) {
    std::streamsize size = ifs.gcount();
    fprintf(stderr, "read chunk of length %ld", size);
  }
}

int main(int argc, const char* argv[]) {
  const char* file = argv[1];
  read_file(file);
}
