CC:=gcc
CFLAGS:=-c

SRCS:=main.c alloc_stat.c
OBJS:=$(patsubst %.c, build/%.o, $(SRCS))


all: directories test

.PHONY: directories clean
directories: build

test: $(OBJS)
	$(CC) $^ -o build/$@

build/%.o: %.c
	$(CC) $(CFLAGS) -g $< -o $@

clean:
	rm -r build

build:
	mkdir -p build