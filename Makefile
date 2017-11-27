ROOT        = $(shell pwd)
DEPS        = $(ROOT)/deps
UV_PATH     = $(DEPS)/uv
UV_LIB      = $(UV_PATH)/out/Debug/libuv.a
UV_INCLUDES = $(UV_PATH)/include/
UV_SRCS     = $(wildcard $(UV_PATH)/src/*.c) $(wildcard $(UV_PATH)/src/unix/*.c)
UV_FLAGS    = -pthread

LDFLAGS = -v $(UV_LIB)
CCFLAGS = $(UV_FLAGS) -std=c++11 -g

SRC_DIR = $(ROOT)/src
BIN_DIR = $(ROOT)/bin


SRCS := $(wildcard $(SRC_DIR)/*.cc)
OBJS = $(SRCS:.cc=.o)
INCS =	-I$(UV_INCLUDES)

MAIN = $(BIN_DIR)/main

main: $(MAIN)

$(UV_PATH):
	git clone git@github.com:libuv/libuv.git $@ && \
	cd $(UV_PATH) &&                               \
	git checkout tags/v1.16.1

$(UV_LIB): $(UV_PATH)
	cd $(UV_PATH) &&                                                                                            \
    (test -d ./build/gyp ||                                                                                     \
    	(mkdir -p ./build && git clone https://chromium.googlesource.com/external/gyp $(UV_PATH)/build/gyp)) && \
	./gyp_uv.py -f make &&                                                                                      \
	make -C out -j8

$(MAIN): $(UV_LIB) $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(LDFLAGS) $(OBJS) -o $@

.SUFFIXES: .cc .o
.cc.o:
	$(CXX) $< $(CCFLAGS) $(INCS) -c -o $@

clean:
	@rm -f $(OBJS) $(MAIN)

.PHONY: main
