CC := gcc

HEADERS_DIR := inc
SRC_LIB_DIR := src
SRC_UNIT_DIR := unit_tests
OUT_DIR := out

UNIT_SRCS := $(wildcard $(SRC_UNIT_DIR)/*.c)
LIB_SRCS := $(wildcard $(SRC_LIB_DIR)/*.c)

UNIT_OBJS := $(UNIT_SRCS:$(SRC_UNIT_DIR)/%.c=$(OUT_DIR)/%.o)
LIB_OBJS := $(LIB_SRCS:$(SRC_LIB_DIR)/%.c=$(OUT_DIR)/%.o)
UNIT_DEPS := $(UNIT_OBJS:%.o=%.d)
LIB_DEPS := $(LIB_OBJS:%.o=%.d)

LIB = $(OUT_DIR)/libarray.so

CFLAGS := -std=c99 -Wall -Werror -Wextra -Wpedantic -Wfloat-equal -Wfloat-conversion -Wvla -g -O0 -I$(HEADERS_DIR)

UNIT_LINK_FLAGS := -lcheck -lm
ifeq ($(shell uname -n), deb-laptop)
  UNIT_LINK_FLAGS += -lrt -lsubunit
endif

all : unit_tests.exe lib

app : lib
	python3 ./app.py

lib : $(LIB)

unit_tests.exe : $(UNIT_OBJS) $(LIB)
	$(CC) $(UNIT_OBJS) -L$(OUT_DIR) -larray $(UNIT_LINK_FLAGS) -Wl,-rpath,./$(OUT_DIR) -o $@

$(LIB) : CFLAGS += -fPIC
$(LIB) : $(LIB_OBJS)
	$(CC) -shared $^ -o $@

$(OUT_DIR)/%.o : $(SRC_LIB_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT_DIR)/check_%.o : $(SRC_UNIT_DIR)/check_%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT_DIR)/check_%.d : $(SRC_UNIT_DIR)/check_%.c | $(OUT_DIR)
	$(CC) -I$(HEADERS_DIR) -MM -MF $@ -MT $(OUT_DIR)/check_$*.o $<

$(OUT_DIR)/%.d : $(SRC_LIB_DIR)/%.c | $(OUT_DIR)
	$(CC) -I$(HEADERS_DIR) -MM -MF $@ -MT $(OUT_DIR)/$*.o $<

$(OUT_DIR) :
	mkdir -p $(OUT_DIR)

ifneq (clean, $(MAKECMDGOALS))
  include $(UNIT_DEPS)
  include $(LIB_DEPS)
endif

clean :
	$(RM) ./$(OUT_DIR)/* ./*.exe

.PHONY : clean lib app all
