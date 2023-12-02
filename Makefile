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

SRC := src/ast/append_node_argv.c src/ast/constructor.c src/ast/destructor.c src/ast/getter.c src/ast/setter.c src/builtins/cd/canonicalize_absolute_path.c src/builtins/cd/cd.c src/builtins/cd/change_directory.c src/builtins/echo.c src/builtins/env.c src/builtins/exit.c src/builtins/export/export.c src/builtins/export/export_each_arg.c src/builtins/export/no_arg.c src/builtins/get_builtin_func.c src/builtins/get_next_option.c src/builtins/pwd.c src/builtins/unset.c src/builtins/utils_internal.c src/exec/configure_io.c src/exec/execute_ast.c src/exec/execvp.c src/exec/handle_and_or.c src/exec/handle_command.c src/exec/handle_pipeline.c src/exec/handle_semicolon.c src/exec/handle_subshell.c src/exec/pipeline_info.c src/exec/utils_internal.c src/exec/wait_children.c src/init/init_loop.c src/init/init_shell.c src/init/utils_internal.c src/lexer/constructor.c src/lexer/destructor.c src/lexer/error.c src/lexer/get_next_token.c src/lexer/getter/get_cur_char.c src/lexer/getter/get_cur_token_type.c src/lexer/getter/get_input.c src/lexer/getter/get_input_snapshot.c src/lexer/getter/get_quote_char.c src/lexer/getter/get_token_len.c src/lexer/getter/has_empty_input.c src/lexer/quote.c src/lexer/read.c src/lexer/setter.c src/lexer/tokenize.c src/main.c src/parser/and_or.c src/parser/command.c src/parser/complete_command.c src/parser/constructor.c src/parser/consume.c src/parser/destructor.c src/parser/error.c src/parser/getter.c src/parser/here_doc.c src/parser/is_eof.c src/parser/parse.c src/parser/pipeline.c src/parser/redirect.c src/parser/setter.c src/parser/simple_command.c src/parser/utils_internal.c src/parser/word_cmd_suffix.c src/parser/word_expansion/expand_filename.c src/parser/word_expansion/expand_filenames.c src/parser/word_expansion/expand_parameters.c src/parser/word_expansion/expand_parameters_utils.c src/parser/word_expansion/expand_word.c src/parser/word_expansion/expand_word_list.c src/parser/word_expansion/is_match.c src/parser/word_expansion/remove_quotes.c src/parser/word_expansion/split_word.c src/parser/word_expansion/utils.c src/signal/set_sig_handlers.c src/signal/sig_handler.c src/token/constructor.c src/token/destructor.c src/token/getter.c src/token/push.c src/utils/char.c src/utils/directory.c src/utils/error.c src/utils/fs.c src/utils/list.c src/utils/memory.c src/utils/message.c src/variables/constructor.c src/variables/exportvar.c src/variables/get_environ.c src/variables/getvar.c src/variables/parse.c src/variables/setvar.c src/variables/unsetvar.c src/variables/utils_internal.c src/variables/validate.c
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
