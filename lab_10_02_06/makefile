COMPILATION_MODE := $(MAKECMDGOALS)
ifneq (1, $(words $(MAKECMDGOALS)))
  ifeq (0, $(words $(MAKECMDGOALS)))
    COMPILATION_MODE := debug
  else
    $(error Only one goal needed)
  endif
endif
ifeq (app.exe, $(MAKECMDGOALS))
  COMPILATION_MODE := debug
endif
ifeq (unit_tests.exe, $(MAKECMDGOALS))
  COMPILATION_MODE := debug
endif
ifeq (all, $(MAKECMDGOALS))
  COMPILATION_MODE := debug
endif

CC := gcc
CC_SAN := clang

HEADERS_DIR := inc
SRC_DIR := src
SRC_UNIT_DIR := unit_tests
OUT_DIR := out

SRCS := $(wildcard $(SRC_DIR)/*.c)
UNIT_SRCS := $(wildcard $(SRC_UNIT_DIR)/*.c)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OUT_DIR)/%.o)
UNIT_OBJS := $(UNIT_SRCS:$(SRC_UNIT_DIR)/%.c=$(OUT_DIR)/%.o)
DEPS := $(OBJS:%.o=%.d)
UNIT_DEPS := $(UNIT_OBJS:%.o=%.d)
UNIT_OBJS += $(filter-out $(OUT_DIR)/main.o, $(OBJS))

CFLAGS := -std=c99 -Wall -Werror -Wextra -Wpedantic -Wfloat-equal -Wfloat-conversion -Wvla -g -I$(HEADERS_DIR)
LINK_FLAGS :=

DEBUG_FLAGS := -O0 -g3
RELEASE_FLAGS := -O2 -g0
MSAN_FLAGS := -fsanitize=memory -fPIE -fno-omit-frame-pointer -O0 -g
MSAN_LINK_FLAGS := -fsanitize=memory -pie
ASAN_FLAGS := -fsanitize=address -fno-omit-frame-pointer -O0 -g
ASAN_LINK_FLAGS := -fsanitize=address
UBSAN_FLAGS := -fsanitize=undefined -fno-omit-frame-pointer -O0 -g
UBSAN_LINK_FLAGS := -fsanitize=undefined
COV_FLAGS := --coverage -O0 -g -fprofile-abs-path
COV_LINK_FLAGS := --coverage

UNIT_LINK_FLAGS := -lcheck -lm
ifeq ($(shell uname -n), deb-laptop)
  UNIT_LINK_FLAGS += -lrt -lsubunit
  CFLAGS += -DDEBUG
endif

all : app.exe unit_tests.exe

debug : CFLAGS += $(DEBUG_FLAGS)
debug : app.exe

release : CFLAGS += $(RELEASE_FLAGS)
release : app.exe

msan : CFLAGS += $(MSAN_FLAGS)
msan : LINK_FLAGS += $(MSAN_LINK_FLAGS)
msan : CC := $(CC_SAN)
msan : app.exe

asan : CFLAGS += $(ASAN_FLAGS)
asan : LINK_FLAGS += $(ASAN_LINK_FLAGS)
asan : CC := $(CC_SAN)
asan : app.exe

ubsan : CFLAGS += $(UBSAN_FLAGS)
ubsan : LINK_FLAGS += $(UBSAN_LINK_FLAGS)
ubsan : CC := $(CC_SAN)
ubsan : app.exe

cov : CFLAGS += $(COV_FLAGS)
cov : LINK_FLAGS += $(COV_LINK_FLAGS)
cov : app.exe

app.exe : $(OBJS)
	$(CC) $^ $(LINK_FLAGS) -o ./app.exe

unit_tests.exe : $(UNIT_OBJS)
	$(CC) $^ $(UNIT_LINK_FLAGS) -o ./unit_tests.exe

$(OUT_DIR)/%.o : $(SRC_DIR)/%.c $(OUT_DIR)/$(COMPILATION_MODE)_flag.tmp
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT_DIR)/check_%.o : $(SRC_UNIT_DIR)/check_%.c $(OUT_DIR)/$(COMPILATION_MODE)_flag.tmp
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT_DIR)/$(COMPILATION_MODE)_flag.tmp : | $(OUT_DIR)
	$(RM) ./$(OUT_DIR)/*_flag.tmp
	touch $@

$(OUT_DIR)/%.d : $(SRC_DIR)/%.c | $(OUT_DIR)
	$(CC) -I$(HEADERS_DIR) -MM -MF $@ -MT $(OUT_DIR)/$*.o $<

$(OUT_DIR)/check_%.d : $(SRC_UNIT_DIR)/check_%.c | $(OUT_DIR)
	$(CC) -I$(HEADERS_DIR) -MM -MF $@ -MT $(OUT_DIR)/$*.o $<

$(OUT_DIR) :
	mkdir -p $(OUT_DIR)

ifneq (clean, $(MAKECMDGOALS))
  include $(UNIT_DEPS)
  include $(DEPS)
endif

clean :
	$(RM) ./$(OUT_DIR)/* ./*.exe

.PHONY : clean debug release msan asan ubsan cov all
