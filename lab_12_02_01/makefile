COMPILATION_MODE := $(MAKECMDGOALS)
ifneq (1, $(words $(MAKECMDGOALS)))
  ifeq (0, $(words $(MAKECMDGOALS)))
    COMPILATION_MODE := stat
  else
    $(error Only one goal needed)
  endif
endif
ifeq (stat, $(MAKECMDGOALS))
  COMPILATION_MODE := stat
endif
ifeq (dyn_link, $(MAKECMDGOALS))
  COMPILATION_MODE := dyn_link
endif
ifeq (dyn_load, $(MAKECMDGOALS))
  COMPILATION_MODE := dyn_load
endif
ifeq (all, $(MAKECMDGOALS))
  COMPILATION_MODE := stat
endif

CC := gcc

HEADERS_DIR := inc
SRC_DIR := src
SRC_LIB_DIR := lib
SRC_UNIT_DIR := unit_tests
OUT_DIR := out

SRCS := $(wildcard $(SRC_DIR)/*.c)
UNIT_SRCS := $(wildcard $(SRC_UNIT_DIR)/*.c)
LIB_SRCS := $(wildcard $(SRC_LIB_DIR)/*.c)

OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OUT_DIR)/%.o)
UNIT_OBJS := $(UNIT_SRCS:$(SRC_UNIT_DIR)/%.c=$(OUT_DIR)/%.o)
LIB_OBJS := $(LIB_SRCS:$(SRC_LIB_DIR)/%.c=$(OUT_DIR)/%.o)
DEPS := $(OBJS:%.o=%.d)
UNIT_DEPS := $(UNIT_OBJS:%.o=%.d)
UNIT_OBJS += $(filter-out $(OUT_DIR)/main.o, $(OBJS))
LIB_DEPS := $(LIB_OBJS:%.o=%.d)

STAT_LIB = $(OUT_DIR)/libarr.a
DYN_LIB = $(OUT_DIR)/libarr.so

CFLAGS := -std=c99 -Wall -Werror -Wextra -Wfloat-equal -Wfloat-conversion -Wvla -g -O0 -I$(HEADERS_DIR)
ifneq (dyn_load, $(COMPILATION_MODE)) 
  CFLAGS += -Wpedantic
else
  CFLAGS += -DDYNLOAD
endif

UNIT_LINK_FLAGS := -lcheck -lm
ifeq ($(shell uname -n), deb-laptop)
  UNIT_LINK_FLAGS += -lrt -lsubunit
endif

all : app.exe unit_tests.exe

stat : all 

dyn_link : all

dyn_load : all

ifeq (stat, $(COMPILATION_MODE)) 
app.exe : $(OBJS) $(STAT_LIB)
	$(CC) $(OBJS) -L$(OUT_DIR) -larr -o $@
unit_tests.exe : $(UNIT_OBJS) $(STAT_LIB)
	$(CC) $(UNIT_OBJS) -L$(OUT_DIR) -larr $(UNIT_LINK_FLAGS) -o $@
endif
ifeq (dyn_link, $(COMPILATION_MODE)) 
app.exe : $(OBJS) $(DYN_LIB)
	$(CC) $(OBJS) -L$(OUT_DIR) -larr -Wl,-rpath,./$(OUT_DIR) -o $@
unit_tests.exe : $(UNIT_OBJS) $(DYN_LIB)
	$(CC) $(UNIT_OBJS) -L$(OUT_DIR) -larr $(UNIT_LINK_FLAGS) -Wl,-rpath,./$(OUT_DIR) -o $@
endif
ifeq (dyn_load, $(COMPILATION_MODE)) 
app.exe : $(OBJS) $(DYN_LIB)
	$(CC) $(OBJS) -ldl -Wl,-rpath,./$(OUT_DIR) -o $@
unit_tests.exe : $(UNIT_OBJS) $(DYN_LIB)
	$(CC) $(UNIT_OBJS) -ldl $(UNIT_LINK_FLAGS) -Wl,-rpath,./$(OUT_DIR) -o $@
endif

$(STAT_LIB) : $(LIB_OBJS)
	ar cr $@ $^
	ranlib $@

$(DYN_LIB) : CFLAGS += -fPIC
$(DYN_LIB) : $(LIB_OBJS)
	$(CC) -shared $^ -o $@

$(OUT_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT_DIR)/$(SRC_LIB_DIR)_%.o : $(SRC_LIB_DIR)/$(SRC_LIB_DIR)_%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT_DIR)/check_%.o : $(SRC_UNIT_DIR)/check_%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT_DIR)/%.d : $(SRC_DIR)/%.c | $(OUT_DIR)
	$(CC) -I$(HEADERS_DIR) -MM -MF $@ -MT $(OUT_DIR)/$*.o $<

$(OUT_DIR)/check_%.d : $(SRC_UNIT_DIR)/check_%.c | $(OUT_DIR)
	$(CC) -I$(HEADERS_DIR) -MM -MF $@ -MT $(OUT_DIR)/check_$*.o $<

$(OUT_DIR)/$(SRC_LIB_DIR)_%.d : $(SRC_LIB_DIR)/$(SRC_LIB_DIR)_%.c | $(OUT_DIR)
	$(CC) -I$(HEADERS_DIR) -MM -MF $@ -MT $(OUT_DIR)/$(SRC_LIB_DIR)_$*.o $<

$(OUT_DIR) :
	mkdir -p $(OUT_DIR)

ifneq (clean, $(MAKECMDGOALS))
  include $(DEPS)
  include $(UNIT_DEPS)
  include $(LIB_DEPS)
endif

clean :
	$(RM) ./$(OUT_DIR)/* ./*.exe

.PHONY : clean stat dyn_link dyn_load all
