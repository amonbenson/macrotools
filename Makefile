CC = gcc
CFLAGS = -Wall -Werror -O3 -Iinclude

BUILD_DIR = build
TEST_DIR = tests
TEST_TARGET = main

TEST_SOURCES = $(wildcard $(TEST_DIR)/*.c)
TEST_BINARY = $(BUILD_DIR)/$(TEST_DIR)/$(TEST_TARGET)

$(TEST_BINARY): $(TEST_SOURCES)
	mkdir -p $(BUILD_DIR)/$(TEST_DIR)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: all
all: dir $(TEST_BINARY)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

.PHONY: test
test: $(TEST_BINARY)
	$(TEST_BINARY)
