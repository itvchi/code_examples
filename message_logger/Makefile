CC:=g++
CFLAGS:=-c

SRCS:=main.cpp
OBJS:=$(patsubst %.cpp, build/%.o, $(SRCS))

LIB_PATH:=liblogger
LIB_SRCS:=message_logger.cpp
LIB_OBJS:=$(patsubst %.cpp, build/liblogger/%.o, $(LIB_SRCS))

all: liblogger main

.PHONY: directories clean dir_build dir_liblogger
directories: dir_build dir_liblogger

test:
	LD_LIBRARY_PATH=./build/$(LIB_PATH):$LD_LIBRARY_PATH ./build/main

main: $(OBJS) 
	$(CC) $^ -o build/$@ -L./build/$(LIB_PATH) -llogger

build/%.o: %.cpp dir_build
	$(CC) $(CFLAGS) $< -o $@

liblogger: $(LIB_OBJS)
	$(CC) -shared $^ -o build/$(LIB_PATH)/$@.so

$(LIB_OBJS): $(LIB_PATH)/$(LIB_SRCS) dir_liblogger
	$(CC) $(CFLAGS) -fpic $< -o $@

clean:
	rm -r build

dir_build:
	mkdir -p build

dir_liblogger: dir_build
	mkdir -p build/liblogger