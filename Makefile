CC = gcc
CFLAGS = -Wall -Werror -O3 -Iinclude

BUILD_DIR = build

TEST_DIR = tests
TEST_BINARY = $(BUILD_DIR)/test

EXAMPLE_DIR = examples



TEST_SOURCES = $(wildcard $(TEST_DIR)/*.c)

$(TEST_BINARY): $(TEST_SOURCES)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: test
test: $(TEST_BINARY)
	$<



EXAMPLE_SOURCES = $(wildcard $(EXAMPLE_DIR)/*.c)
EXAMPLE_BINARIES = $(patsubst $(EXAMPLE_DIR)/%.c,$(BUILD_DIR)/$(EXAMPLE_DIR)/%,$(EXAMPLE_SOURCES))

$(BUILD_DIR)/$(EXAMPLE_DIR)/%: $(EXAMPLE_DIR)/%.c
	mkdir -p $(BUILD_DIR)/$(EXAMPLE_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# $(BUILD_DIR)/$(EXAMPLE_DIR)/%.md: $(EXAMPLE_DIR)/%.c $(BUILD_DIR)/$(EXAMPLE_DIR)/%
# 	printf "\`\`\`c\n$$(cat $<)\n\`\`\`\n**Compile:**:\n\`\`\`bash\nmake examples && ./$(word 2,$^)\n\`\`\`**Output:**\n\`\`\`console\n$$(./$(word 2,$^))\n\`\`\`\n" > $@

.PHONY: examples
examples: $(EXAMPLE_BINARIES)



.PHONY: all
all: $(TEST_BINARY) $(EXAMPLE_BINARIES)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
