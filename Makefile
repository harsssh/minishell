SHELL := /bin/bash

NAME := minishell

SRC_DIR := src
BUILD_DIR := build

LIBFT := libft/libft.a
LIBREADLINE := readline/lib/libreadline.a

CFLAGS := -Wall -Wextra -Werror

# Flags for release build (optimizations enabled)
RELEASE_FLAGS := -O3
# Flags for debug build (no optimizations, with sanitizer)
DEBUG_FLAGS := -g -O0 -fsanitize=address

INCLUDES := -Iinclude -Isrc -Ilibft/include -Ireadline/include

LDFLAGS := -Llibft -Lreadline/lib
# Add linker flags for macOS to avoid 'could not create compact unwind' warnings
ifeq ($(shell uname -s),Darwin)
	LDFLAGS += -Wl,-no_compact_unwind
endif
LDLIBS := -lft -lreadline -lncurses

# Flags to generate dependency files
DEPFLAGS = -MT $@ -MMD -MP -MF $(BUILD_DIR)/$*.d

SRC := $(shell find $(SRC_DIR) -name '*.c')
OBJ := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC))
DEP := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.d,$(SRC))

.PHONY: all
all: CFLAGS+=$(RELEASE_FLAGS)
all: $(NAME)

.PHONY: debug
debug: CFLAGS+=$(DEBUG_FLAGS)
debug: $(NAME)

$(NAME): $(LIBFT) $(LIBREADLINE) $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) $(LDFLAGS) -o $@ $^ $(LDLIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) $(DEPFLAGS) -c -o $@ $<

$(LIBFT):
	make -C libft

$(LIBREADLINE):
	@git submodule update --init
	cd readline && \
	./configure -q --prefix=$(PWD)/readline --enable-shared=no && \
	make -s && \
	make -s install 2> /dev/null

# NOTE: Specifying SHELL to ensure compatibility across different environments.
.PHONY: clean
clean:
	-@make -C libft clean
	-@make -C readline clean SHELL=/bin/bash
	-$(RM) $(OBJ) $(DEP)

# NOTE: Specifying SHELL to ensure compatibility across different environments.
.PHONY: fclean
fclean: clean
	-@make -C libft fclean
	-@make -C readline uninstall SHELL=/bin/bash
	-$(RM) $(NAME)

.PHONY: re
re: fclean all

-include $(DEP)
