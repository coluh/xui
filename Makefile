CC      := cc
AR      := ar
CFLAGS  += -I./include
# CFLAGS  := -std=c11
# CFLAGS  += -O2
CFLAGS  += -Wall -Wextra
CFLAGS  += -g -ggdb
CFLAGS  += -lSDL2 -lSDL2_ttf -lm

BUILD   := build
LIB     := $(BUILD)/libxui.a

SRC_C   := $(shell find src -name '*.c')
SRC_O   := $(SRC_C:src/%.c=$(BUILD)/obj/%.o)

TEST_C  := $(wildcard test/*.c)
TEST_EXE:= $(TEST_C:test/%.c=$(BUILD)/test/%)

.PHONY: all clean test

all: $(LIB) $(TEST_EXE)

$(LIB): $(SRC_O)
	@mkdir -p $(dir $@)
	$(AR) rcs $@ $^

$(BUILD)/obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/test/%: test/%.c $(LIB)
	@mkdir -p $(dir $@)
	$(CC) $< $(LIB) $(CFLAGS) -o $@

test: $(TEST_EXE)
	@for t in $^; do echo "==> $$t"; $$t; done

clean:
	rm -rf $(BUILD)
