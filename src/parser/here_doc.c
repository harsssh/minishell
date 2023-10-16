/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 18:19:43 by smatsuo           #+#    #+#             */
/*   Updated: 2023/10/10 17:22:28 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "parser_internal.h"
#include "fcntl.h"
#include <stdio.h>
#include <readline/readline.h>
#include <unistd.h>
#include "libft.h"

static int	open_here_doc(t_redirect *redirect)
{
	int	fd;

	if (redirect == NULL)
		return (-1);
	set_redirect_filename(redirect, "/tmp/here-doc.minishell");
	fd = open("/tmp/here-doc.minishell",
			O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
		set_redirect_filename(redirect, "/var/tmp/here-doc.minishell");
		fd = open("/var/tmp/here-doc.minishell",
				O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
	}
	if (fd == -1)
	{
		set_redirect_filename(redirect, "./here-doc.minishell");
		fd = open("./here-doc.minishell",
				O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
	}
	return (fd);
}

static t_redirect	*new_here_doc(char *delimiter)
{
	t_redirect	*redirect;
	int			fd;
	char		*line;

	redirect = new_redirect(REDIRECT_HERE_DOC, NULL);
	fd = open_here_doc(redirect);
	if (redirect == NULL || fd == -1)
	{
		destroy_redirect(redirect);
		return (NULL);
	}
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			close(fd);
			destroy_redirect(redirect);
			return (NULL);
		}
		if (ft_strcmp(delimiter, line) == 0)
			break ;
		ft_putendl_fd(line, fd);
	}
	return (redirect);
}

// When parsing here document, a tmporary file will be created and
// the file name will be stored in the filename field of the redirect
// structure. The following token will be used as the delimiter
// if the token type is TK_WORD.
t_redirect	*parse_here_doc(t_parser *parser)
{
	char	*delimiter;

	if (consume_token(parser, TK_REDIRECT_HERE_DOC))
	{
		delimiter = parse_word(parser);
		if (delimiter == NULL)
			return (NULL);
		return (new_here_doc(delimiter));
	}
	else
		return (NULL);
}
