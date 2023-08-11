NAME:=libft.a

SRC_DIR=src
BUILD_DIR:=build

CFLAGS:=-Wall -Wextra -Werror -Iinclude

SRC:=ctype/ft_isalnum.c ctype/ft_isalpha.c ctype/ft_isascii.c ctype/ft_isdigit.c ctype/ft_isprint.c ctype/ft_isspace.c ctype/ft_tolower.c ctype/ft_toupper.c \
stdio/ft_dprintf/ft_dprintf.c stdio/ft_dprintf/ft_putnbr_base.c stdio/ft_dprintf/parse_placeholder.c stdio/ft_dprintf/to_enum.c stdio/ft_putchar_fd.c stdio/ft_putendl_fd.c stdio/ft_putnbr_fd.c stdio/ft_putstr_fd.c stdio/get_next_line/get_next_line.c stdio/get_next_line/get_next_line_utils.c \
stdlib/ft_atoi.c stdlib/ft_atol.c stdlib/ft_atoll.c stdlib/ft_calloc.c stdlib/ft_itoa.c \
string/ft_memchr.c string/ft_memcmp.c string/ft_memcpy.c string/ft_memmove.c string/ft_memset.c string/ft_split.c string/ft_strall.c string/ft_strany.c string/ft_strchr.c string/ft_strcmp.c string/ft_strdup.c string/ft_striteri.c string/ft_strjoin.c string/ft_strlcat.c string/ft_strlcpy.c string/ft_strlen.c string/ft_strmapi.c string/ft_strncmp.c string/ft_strnlen.c string/ft_strnstr.c string/ft_strrchr.c string/ft_strtrim.c string/ft_substr.c strings/ft_bzero.c
OBJ:=$(addprefix $(BUILD_DIR)/,$(SRC:.c=.o))

.PHONY: all
all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $@ $^

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	$(RM) $(OBJ)

.PHONY: fclean
fclean: clean
	$(RM) $(NAME)

.PHONY: re
re: fclean all
