/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 11:09:45 by kemizuki          #+#    #+#             */
/*   Updated: 2023/07/31 01:37:33 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERNAL_H
# define INTERNAL_H

# define DECIMAL_BASE "0123456789"
# define HEX_BASE "0123456789abcdef"
# define HEX_BASE_UP "0123456789ABCDEF"

# include <stdbool.h>
# include <stddef.h>

enum							e_flag
{
	UNKNOWN_FLAG = 0,
	HYPHEN = 1,
	ZERO = 1 << 1,
	PLUS = 1 << 2,
	SPACE = 1 << 3,
	HASH = 1 << 4,
};
typedef enum e_flag				t_flag;

enum							e_spec
{
	UNKNOWN_SPEC,
	CHAR,
	STRING,
	DECIMAL,
	U_DECIMAL,
	HEX,
	HEX_UP,
	POINTER,
	PERCENT,
};
typedef enum e_spec				t_spec;

// conversion specification
// %[flags][width].[precision][length modifier][specifier]
// omit length modifier
struct							s_placeholder
{
	unsigned long long			flags;
	bool						exist_width;
	unsigned long long			width;
	bool						exist_precision;
	unsigned long long			precision;
	t_spec						specifier;
};
typedef struct s_placeholder	t_placeholder;

t_flag	to_flag(char c);
t_spec	to_specifier(char c);
char	*parse_placeholder(t_placeholder *p, const char *s);
size_t	ft_putnbr_base(int fd, long long nbr, char *base);
size_t	ft_putunbr_base(int fd, unsigned long long nbr, char *base);

#endif
