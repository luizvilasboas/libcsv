CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic
LIB_NAME = libcsv
TEST_EXECUTABLE = test_libcsv

SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
LIB_DIR = /usr/local/lib
INSTALL_INCLUDE_DIR = /usr/local/include

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))

ALL_SOURCE_FILES = $(shell find $(SRC_DIR) $(TEST_DIR) $(INCLUDE_DIR) -name "*.c" -o -name "*.h")

TEST_DIR = tests
TEST_SRC_FILES = $(wildcard $(TEST_DIR)/*.c)
TEST_OBJ_FILES = $(patsubst $(TEST_DIR)/%.c, $(BUILD_DIR)/%.o, $(TEST_SRC_FILES))

CHECK_LIBS = -lcheck -lm -lpthread -lrt -lsubunit

all: $(BUILD_DIR) $(LIB_NAME)

$(LIB_NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) -shared -o $(BUILD_DIR)/$(LIB_NAME).so $(OBJ_FILES)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

$(BUILD_DIR):
	mkdir $@

install: $(LIB_NAME)
	install -d $(LIB_DIR)
	install -m 644 $(BUILD_DIR)/$(LIB_NAME).so $(LIB_DIR)
	install -d $(INSTALL_INCLUDE_DIR)
	install -m 644 $(INCLUDE_DIR)/$(LIB_NAME).h $(INSTALL_INCLUDE_DIR)

uninstall:
	rm -f $(LIB_DIR)/lib$(LIB_NAME).so
	rm -f $(INSTALL_INCLUDE_DIR)/$(LIB_NAME).h

test: $(BUILD_DIR) $(LIB_NAME) $(TEST_EXECUTABLE)
	./$(BUILD_DIR)/$(TEST_EXECUTABLE)

leak: $(TEST_EXECUTABLE)
	valgrind --leak-check=full \
		--show-leak-kinds=all \
		--track-origins=yes  \
		--errors-for-leak-kinds=all \
		./$(BUILD_DIR)/$(TEST_EXECUTABLE);

format: $(ALL_SOURCE_FILES)
	clang-format -i $(ALL_SOURCE_FILES)

lint: $(ALL_SOURCE_FILES)
	clang-format --dry-run --Werror $(ALL_SOURCE_FILES)

$(TEST_EXECUTABLE): $(TEST_OBJ_FILES)
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/$(TEST_EXECUTABLE) $(TEST_OBJ_FILES) $(OBJ_FILES) $(CHECK_LIBS)

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all install uninstall clean test format lint
