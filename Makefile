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
INC_DIR   = include

### variables containing lists of files ###
SRCS      := $(shell find $(SRC_DIR) -name *.c)
MAIN_SRCS := $(filter %.main.c,$(SRCS))
OBJS      := $(SRCS:%.c=$(BUILD_DIR)/%.o)
OBJS_DBG  := $(SRCS:%.c=$(BUILD_DIR)/%.odbg)
MAIN_OBJS := $(MAIN_SRCS:%.c=$(BUILD_DIR)/%.o)
MAIN_OBJS_DBG := $(MAIN_SRCS:%.c=$(BUILD_DIR)/%.odbg)
MAIN_EXES := $(MAIN_OBJS:.main.o=.out)
MAIN_EXES_DBG := $(MAIN_OBJS_DBG:.main.odbg=.outdbg)
DEPS      := $(OBJS:.o=.d)

### commandline flags/vairbales ###
MKDIR_P   ?= mkdir -p
CC        ?= clang
INC_FLAGS := -I$(INC_DIR)
WFLAGS    := -Wall -Wextra
CFLAGS    := $(INC_FLAGS) $(WFLAGS)
DBG_FLAGS := -Og -g
OPT_FLAGS := -Ofast -DNDEBUG

### compile executables ###
all: $(MAIN_EXES) $(MAIN_EXES_DBG)

distclean:
	$(RM) -r $(BUILD_DIR)
.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)
	# make dependent makefiles before continuing
	make depends
.PHONY: clean

$(BUILD_DIR)/%.out: $(BUILD_DIR)/%.main.o $(filter-out $(MAIN_OBJS),$(OBJS))
	$(CC) $^ -o $@ $(LDFLAGS)

# same executables, but linked with debug objects
$(BUILD_DIR)/%.outdbg: $(BUILD_DIR)/%.main.odbg $(filter-out $(MAIN_OBJS_DBG),$(OBJS_DBG))
	$(CC) $^ -o $@ $(LDFLAGS)

### compile object files ###
# $(OBJS)
$(BUILD_DIR)/%.o: %.c
	$(CC) $(CFLAGS) $(OPT_FLAGS) -c $< -o $@

# same objects, but compiled with debug flags
# $(OBJS_DBG)
$(BUILD_DIR)/%.odbg: %.c
	$(CC) $(CFLAGS) $(DBG_FLAGS) -c $< -o $@

### generates Makefile rules which add dependencies from #include's ##
# $(DEPS)
$(BUILD_DIR)/%.d: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(INC_FLAGS) -MM -MF $@ -MT $(BUILD_DIR)/$(<:.c=.o) $<
depends: $(DEPS)

-include $(DEPS)

### project specific targets ###

TEST_EXE := $(BUILD_DIR)/src/task_engine/test.outdbg
EXPERIMENT_EXE := $(BUILD_DIR)/src/task_engine/experiment.out

run: $(EXPERIMENT_EXE)
	./$(EXPERIMENT_EXE)

debug: $(TEST_EXE)
	MALLOC_CHECK_=1 gdb -q -ex run "$(TEST_EXE)" -ex backtrace
.PHONY: debug

test: $(TEST_EXE)
	valgrind $(TEST_EXE)
.PHONY: test

### references ###
# see https://spin.atomicobject.com/2016/08/26/makefile-c-projects/
# see "Recursive Make Considered Harmful" Peter Miller
