CC:=gcc
CFLAGS:=-c -g

BUILD_DIR:=build

SRCS:=main.c
OBJS:=$(patsubst %.c, build/%.o, $(SRCS))

LIB_PATH:=libmem
LIB_SRCS:=alloc.c common.c free.c heap.c
LIB_OBJS:=$(patsubst %.c, $(BUILD_DIR)/$(LIB_PATH)/%.o, $(LIB_SRCS))

all: libmem main

.PHONY: clean dir_build dir_libmem

run:
	LD_LIBRARY_PATH=$(BUILD_DIR)/$(LIB_PATH):$(LD_LIBRARY_PATH) ./build/main

main: $(OBJS) 
	$(CC) $^ -o build/$@ -L$(BUILD_DIR)/$(LIB_PATH) -lmem

$(BUILD_DIR)/%.o: %.c | dir_build
	$(CC) $(CFLAGS) $< -o $@

libmem: $(LIB_OBJS)
	$(CC) -shared $^ -o $(BUILD_DIR)/$(LIB_PATH)/$@.so

$(BUILD_DIR)/$(LIB_PATH)/%.o: $(LIB_PATH)/%.c | dir_libmem
	$(CC) $(CFLAGS) -fpic $< -o $@ -DHEAP_SIZE_BYTES=256

clean:
	rm -r $(BUILD_DIR)

dir_build:
	mkdir -p $(BUILD_DIR)

dir_libmem: dir_build
	mkdir -p $(BUILD_DIR)/$(LIB_PATH)