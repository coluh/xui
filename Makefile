
CC=gcc
CFLAGS := -lSDL2 -lSDL2_ttf -lm
CFLAGS += -I./include
CFLAGS += -g -ggdb
# CFLAGS += -Werror -Wall

srcs := $(shell find src/ -name "*.c")
objs := $(srcs:.c=.o)
lib := build/libxui.a

.PHONY: all test clean

all: $(lib)

$(lib): $(objs)
	@mkdir -p build/
	ar -crv $@ $^

test_srcs := $(shell find test/ -name "*.c")
tests := $(test_srcs:.c=.out)

test/%.out: test/%.c $(lib)
	$(CC) $^ $(CFLAGS) -o $@

test: $(tests)
	for t in $^; do echo "Testing $$t:" && ./$$t; done

clean:
	rm -f $(objs) $(tests) bin/* build/*

