CC			:= gcc
CFLAGS	:= -Wall -Wextra -Iinclude
LDFLAGS := 

SRC_DIR	:= src
INC_DIR	:= include
OBJ_DIR := build
BIN_DIR	:= bin

TARGET	:= $(BIN_DIR)/gameboy


SRCS		:= $(wildcard $(SRC_DIR)/*.c)
OBJS 		:= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(TARGET)

# Link
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# Compile
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Phony targets
.PHONY: all clean