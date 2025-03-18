CC := gcc

SRC_DIR := src
UNIT_DIR := unit_tests
HEAD_DIR := inc
OUT_DIR := out

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OUT_DIR)/%.o)
UNITS := $(wildcard $(UNIT_DIR)/*.c)
OBJS += $(UNITS:$(UNIT_DIR)/%.c=$(OUT_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

CFLAGS := -std=c99 -Wall -Werror -Wextra -Wpedantic -Wfloat-equal -Wfloat-conversion -Wvla -O0 -g3 -I$(HEAD_DIR)
LINK_FLAGS := -lcheck -lm
ifeq ($(shell uname -n), deb-laptop)
  LINK_FLAGS += -lrt -lsubunit
endif

all : unit_tests.exe

unit_tests.exe : $(OBJS)
	$(CC) $^ $(LINK_FLAGS) -o ./unit_tests.exe

$(OUT_DIR)/%.o : $(SRC_DIR)/%.c | $(OUT_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT_DIR)/check_%.o : $(UNIT_DIR)/check_%.c | $(OUT_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT_DIR)/%.d : $(SRC_DIR)/%.c | $(OUT_DIR)
	$(CC) $(CFLAGS) -MM -MF $@ -MT $(OUT_DIR)/$*.o $<

$(OUT_DIR)/check_%.d : $(UNIT_DIR)/check_%.c | $(OUT_DIR)
	$(CC) $(CFLAGS) -MM -MF $@ -MT $(OUT_DIR)/check_$*.o $<

$(OUT_DIR) :
	mkdir -p $(OUT_DIR)

ifneq (clean, $(MAKECMDGOALS))
  include $(DEPS)
endif

unit : unit_tests.exe
	./unit_tests.exe

mem : unit_tests.exe
	valgrind -q --leak-check=full ./unit_tests.exe

clean :
	$(RM) ./$(OUT_DIR)/* ./*.exe

.PHONY : clean all mem unit
