CC:=g++
CFLAGS:=-c

BUILD_DIR:=build

SRCS:=main.cpp
OBJS:=$(patsubst %.cpp, build/%.o, $(SRCS))

LIB_PATH:=liblogger
LIB_SRCS:=message_logger.cpp logger_format.cpp
LIB_OBJS:=$(patsubst %.cpp, $(BUILD_DIR)/$(LIB_PATH)/%.o, $(LIB_SRCS))

all: liblogger main

.PHONY: directories clean dir_build dir_liblogger
directories: dir_build dir_liblogger

test:
	LD_LIBRARY_PATH=$(LIB_PATH):$LD_LIBRARY_PATH ./build/main

main: $(OBJS) 
	$(CC) $^ -o build/$@ -L$(BUILD_DIR)/$(LIB_PATH) -llogger

$(BUILD_DIR)/%.o: %.cpp dir_build
	$(CC) $(CFLAGS) $< -o $@

liblogger: $(LIB_OBJS)
	$(CC) -shared $^ -o $(BUILD_DIR)/$(LIB_PATH)/$@.so

$(BUILD_DIR)/$(LIB_PATH)/%.o: $(LIB_PATH)/%.cpp dir_liblogger
	$(CC) $(CFLAGS) -fpic $< -o $@

clean:
	rm -r build

dir_build:
	mkdir -p build

dir_liblogger: dir_build
	mkdir -p $(BUILD_DIR)/$(LIB_PATH)