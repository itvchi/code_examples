CC:=gcc
CFLAGS:=-c

SRCS:=main.c alloc_stat.c
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