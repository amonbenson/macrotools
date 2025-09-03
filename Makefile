CC = gcc
CFLAGS = -Wall -Werror -O3 -Iinclude

BUILD_DIR = build
TEST_DIR = tests
EXAMPLE_DIR = examples

TEST_TARGET = main
TEST_SOURCES = $(wildcard $(TEST_DIR)/*.c)
TEST_BINARY = $(BUILD_DIR)/$(TEST_DIR)/$(TEST_TARGET)

$(TEST_BINARY): $(TEST_SOURCES)
	mkdir -p $(BUILD_DIR)/$(TEST_DIR)
	$(CC) $(CFLAGS) -o $@ $^

EXAMPLE_SOURCES = $(wildcard $(EXAMPLE_DIR)/*.c)
EXAMPLE_BINARIES = $(patsubst $(EXAMPLE_DIR)/%.c,$(BUILD_DIR)/$(EXAMPLE_DIR)/%,$(EXAMPLE_SOURCES))

$(BUILD_DIR)/$(EXAMPLE_DIR)/%: $(EXAMPLE_DIR)/%.c
	mkdir -p $(BUILD_DIR)/$(EXAMPLE_DIR)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: test
test: $(TEST_BINARY)
	$(TEST_BINARY)

.PHONY: examples
examples: $(EXAMPLE_BINARIES)

.PHONY: all
all: $(TEST_BINARY) $(EXAMPLE_BINARIES)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
