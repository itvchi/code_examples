SHELL:=/bin/bash
BUILD_DIR:=build

all: main_malloc main_object_pool main_object_pool_freelist

MILLION:=1000000
DEFINES:= -DTEST_ELEMENTS_NUM=500*$(MILLION) -DMAX_PER_LOOP=5000

main_malloc: | build_dir
	gcc -o $(BUILD_DIR)/$@ $@.c $(DEFINES)

main_object_pool: | build_dir
	gcc -o $(BUILD_DIR)/$@ $@.c $(DEFINES)

main_object_pool_freelist: | build_dir
	gcc -o $(BUILD_DIR)/$@ $@.c $(DEFINES)

test:
	@echo -n "Testing main_malloc"
	@time $(BUILD_DIR)/main_malloc
	@echo -n "Testing main_object_pool"
	@time $(BUILD_DIR)/main_object_pool
	@echo -n "Testing main_object_pool_freelist"
	@time $(BUILD_DIR)/main_object_pool_freelist

build_dir:
	mkdir -p $(BUILD_DIR)