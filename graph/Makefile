CC:=gcc
CFLAGS:=-c

SRCS:=main.c graph.c
OBJS:=$(patsubst %.c, build/%.o, $(SRCS))
TARGET:=graph

all: $(TARGET)


$(TARGET): $(OBJS)
	$(CC) $^ -o build/$@

build/%.o: %.c | build_dir
	$(CC) $(CFLAGS) -g $< -o $@


.PHONY: visualise clean build_dir

clean:
	rm -r build

visualise: $(TARGET)
	build/$(TARGET) | dot -Tpdf > build/graph.pdf

build_dir:
	mkdir -p build