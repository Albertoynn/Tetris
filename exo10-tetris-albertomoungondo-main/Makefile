CC = gcc
LN = gcc
OPT = -Wextra -Werror -g -finline-functions -std=gnu99
LIB = -lrt -lm -lX11 -lGL -pthread

SRC_DIR = src
TEST_DIR = $(SRC_DIR)/test
BUILD_DIR = build

SRCS = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(TEST_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

TARGET = main

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(LN) $^ -o $@ $(LIB)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(OPT) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR) $(BUILD_DIR)/test

clean:
	rm -rf $(BUILD_DIR) $(TARGET)
	rm -rf *.o
