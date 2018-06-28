# see https://spin.atomicobject.com/2016/08/26/makefile-c-projects/
# see "Recursive Make Considered Harmful" Peter Miller
CC ?= clang
MKDIR_P ?= mkdir -p

TARGET_EXEC = main
BUILD_DIR = build
SRC_DIR  = src
INC_DIR  = include

SRCS := $(shell find $(SRC_DIR) -name *.c)
OBJS := $(SRCS:%.c=$(BUILD_DIR)/%.o)
OBJS_DBG := $(SRCS:%.c=$(BUILD_DIR)/%.odbg)
DEPS := $(OBJS:.o=.d)

INC_FLAGS := -I$(INC_DIR)
WFLAGS = -Wall -Wextra -Werror
CFLAGS = $(INC_FLAGS) $(WFLAGS)
DBG_FLAGS = -Og -g
OPT_FLAGS = -Ofast

all: $(BUILD_DIR)/$(TARGET_EXEC) $(BUILD_DIR)/$(TARGET_EXEC)_dbg

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/$(TARGET_EXEC)_dbg: $(OBJS_DBG)
	$(CC) $(OBJS_DBG) -o $@ $(LDFLAGS)

# $(OBJS)
$(BUILD_DIR)/%.o: %.c
	$(CC) $(CFLAGS) $(OPT_FLAGS) -c $< -o $@

# $(OBJS_DBG)
$(BUILD_DIR)/%.odbg: %.c
	$(CC) $(CFLAGS) $(DBG_FLAGS) -c $< -o $@

clean:
	$(RM) -r $(BUILD_DIR)
.PHONY: clean

# generates Makefile rules which add dependencies from #include's
# $(DEPS)
$(BUILD_DIR)/%.d: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(INC_FLAGS) -MM -MF $@ -MT $(BUILD_DIR)/$(<:.c=.o) $<
depends: $(DEPS)

-include $(DEPS)
