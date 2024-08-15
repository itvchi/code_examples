AS=arm-linux-gnueabihf-as
LD=arm-linux-gnueabihf-ld

BUILD_DIR=build
TMP_OBJ=$(BUILD_DIR)/tmp.o

SRCS=$(wildcard *.s)
TARGETS=$(patsubst %.s, $(BUILD_DIR)/%, $(SRCS))

all: $(TARGETS) clean_tmp

$(BUILD_DIR)/%: %.s | mk_build
	$(AS) -o $(TMP_OBJ) $^
	$(LD) -o $@ $(TMP_OBJ)

mk_build:
	mkdir -p $(BUILD_DIR)

clean_tmp:
	rm $(TMP_OBJ)

clean:
	rm -rf $(BUILD_DIR)
