### common goals ###
#     make test  # runs unittests and memory checks
#     make debug # runs GDB on unittest
#     make run   # actually runs experiment
#     make all   # makes all executables
#                # (based on source files like %.main.c containing int main())
# The object files depend only on those headers which their source include

### directory layout ###
BUILD_DIR = build
SRC_DIR   = src
INC_DIR   = ./include

### variables containing lists of files ###
# reactants
C_SRCS    := $(shell find $(SRC_DIR) -name *.c -printf '%P\n')
CC_SRCS  := $(shell find $(SRC_DIR) -name *.cc -printf '%P\n')
MAIN_C_SRCS := $(filter %.main.c,$(C_SRCS))
MAIN_CC_SRCS := $(filter %.main.cc,$(CC_SRCS))

# products
OBJS      := $(C_SRCS:%.c=$(BUILD_DIR)/%.o)      $(CC_SRCS:%.cc=$(BUILD_DIR)/%.o)
DEPS      := $(OBJS:.o=.d)
MAIN_OBJS := $(MAIN_C_SRCS:%.c=$(BUILD_DIR)/%.o) $(MAIN_CC_SRCS:%.cc=$(BUILD_DIR)/%.o)
OTHER_OBJS := $(filter-out $(MAIN_OBJS),$(OBJS))
MAIN_EXES := $(MAIN_OBJS:.main.o=.out)

### commandline flags/vairbales ###
MKDIR_P   ?= mkdir -p
CC        := clang
CPP       := clang++
INC_FLAGS := -I$(INC_DIR)
WFLAGS    := -Wall -Wextra -Wno-unused-parameter
CFLAGS    := $(INC_FLAGS) $(WFLAGS)
CPPFLAGS  := $(INC_FLAGS) $(WFLAGS) -std=c++11
DBG_FLAGS := -Og -g
OPT_FLAGS := -O2 -DNDEBUG

### compile executables ###
all: $(MAIN_EXES) $(addsuffix dbg,$(MAIN_EXES))

distclean:
	$(RM) -r $(BUILD_DIR)
.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)
	# make dependent makefiles before continuing
	make depends
.PHONY: clean

$(BUILD_DIR)/%.out: $(BUILD_DIR)/%.main.o $(OTHER_OBJS)
	$(CPP) $^ -o $@ $(CPPFLAGS)

# same executables, but linked with debug objects
$(BUILD_DIR)/%.outdbg: $(BUILD_DIR)/%.main.odbg $(addsuffix dbg,$(OTHER_OBJS))
	$(CPP) $^ -o $@ $(CPPFLAGS)

### compile object files ###
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(OPT_FLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cc
	$(CPP) $(CPPFLAGS) $(OPT_FLAGS) -c $< -o $@

# same objects, but compiled with debug flags
$(BUILD_DIR)/%.odbg: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(DBG_FLAGS) -c $< -o $@

$(BUILD_DIR)/%.odbg: $(SRC_DIR)/%.cc
	$(CPP) $(CPPFLAGS) $(DBG_FLAGS) -c $< -o $@

### generates Makefile rules which add dependencies from #include's ##
# $(DEPS)
$(BUILD_DIR)/%.d: $(SRC_DIR)/%.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CFLAGS) -MM -MF $@ -MT $(BUILD_DIR)/$(<:.c=.o) $<
$(BUILD_DIR)/%.d: $(SRC_DIR)/%.cc
	$(MKDIR_P) $(dir $@)
	$(CPP) $(CPPFLAGS) -MM -MF $@ -MT $(BUILD_DIR)/$(<:.c=.o) $<

depends: $(DEPS)

-include $(DEPS)

### project specific targets ###

# TEST_EXE := $(BUILD_DIR)/src/task_engine/test.outdbg
# EXPERIMENT_EXE := $(BUILD_DIR)/src/task_engine/experiment.out

# run: $(EXPERIMENT_EXE)
# 	./$(EXPERIMENT_EXE)

# debug: $(TEST_EXE)
# 	gdb "$(TEST_EXE)" -q -ex run -ex backtrace
# .PHONY: debug

# test: $(TEST_EXE)
# 	valgrind -q $(TEST_EXE)
# #  --track-origins=yes --leak-check=full
# .PHONY: test

### references ###
# see https://spin.atomicobject.com/2016/08/26/makefile-c-projects/
# see "Recursive Make Considered Harmful" Peter Miller
