CC := gcc

HEADERS_DIR := inc
SRC_DIR := src
OBJ_DIR := out
SRCS := $(wildcard $(SRC_DIR)/*.c)
INCS := $(wildcard $(HEADERS_DIR)/*.h)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CFLAGS := -std=c99 -Wall -Werror -Wextra -Wpedantic -Wfloat-equal -Wfloat-conversion -Wvla -O0 -g -I$(HEADERS_DIR)

app.exe : $(OBJS)
	$(CC) -o $@ $^

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(INCS) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ_DIR) :
	mkdir -p $(OBJ_DIR)

clean :
	$(RM) ./app.exe ./$(OBJ_DIR)/*

.PHONY : clean
