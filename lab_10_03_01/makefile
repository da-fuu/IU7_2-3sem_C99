CC := gcc

OUT_DIR := out
SRCS := $(wildcard ./*.c)
OBJS := $(SRCS:./%.c=$(OUT_DIR)/%.o)
DEPS := $(SRCS:./%.c=$(OUT_DIR)/%.d)

CFLAGS := -std=c99 -Wall -Werror -Wextra -Wpedantic -Wfloat-equal -Wfloat-conversion -Wvla -O0 -g3
LINK_FLAGS := -lcheck -lm
ifeq ($(shell uname -n), deb-laptop)
  LINK_FLAGS += -lrt -lsubunit
endif

all : unit_tests.exe

unit_tests.exe : $(OBJS)
	$(CC) $^ $(LINK_FLAGS) -o ./unit_tests.exe

$(OUT_DIR)/%.o : ./%.c | $(OUT_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT_DIR)/%.d : ./%.c | $(OUT_DIR)
	$(CC) -MM -MF $@ -MT $(OUT_DIR)/$*.o $<

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
