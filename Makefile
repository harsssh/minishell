NAME:=minishell

SRC_DIR:=src
BUILD_DIR:=build

LIBFT:=libft/libft.a

CFLAGS:=-Wall -Wextra -Werror -Ilibft/include -Iinclude -Isrc
RELEASE_FLAGS:=-O3
DEBUG_FLAGS:=-g -O0 -fsanitize=address
LDFLAGS:=-lreadline
DEPFLAGS=-MT $@ -MMD -MP -MF $(BUILD_DIR)/$*.d

SRC:=$(shell find $(SRC_DIR) -name '*.c')
OBJ:=$(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC))
DEP:=$(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.d,$(SRC))

.PHONY: all
all: CFLAGS+=$(RELEASE_FLAGS)
all: $(NAME)

.PHONY: debug
debug: CFLAGS+=$(DEBUG_FLAGS)
debug: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(DEPFLAGS) -c -o $@ $<

$(LIBFT):
	make -C libft

.PHONY: clean
clean:
	make -C libft clean
	$(RM) $(OBJ) $(DEP)

.PHONY: fclean
fclean: clean
	make -C libft fclean
	$(RM) $(NAME)

.PHONY: re
re: fclean all

-include $(DEP)
