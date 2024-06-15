CC:=g++
CFLAGS:=-c

SRCS:=main.cpp return_code.cpp
OBJS:=$(patsubst %.cpp, build/%.o, $(SRCS))


all: directories test

.PHONY: directories clean
directories: build

test: $(OBJS)
	$(CC) $^ -o build/$@

build/%.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -r build

build:
	mkdir -p build