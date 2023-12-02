/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 18:19:43 by smatsuo           #+#    #+#             */
/*   Updated: 2023/12/02 23:40:08 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "context.h"
#include "ft_list.h"
#include "parser/word_expansion/word_expansion_internal.h"
#include "parser_internal.h"
#include "fcntl.h"
#include <errno.h>
#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "characters.h"
#include "sig.h"

static int	heredoc_readline_hook(void)
{
	if (g_sig == SIGINT)
	{
		rl_done = 1;
	}
	return (EXIT_SUCCESS);
}

static int	open_here_doc(t_redirect *redirect)
{
	char	*filename;
	int		fd;

	if (redirect == NULL)
		return (-1);
	filename = ft_strdup("/tmp/here-doc.minishell");
	if (filename == NULL)
		return (-1);
	set_redirect_filename(redirect, filename);
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

static char	*expand_parameters_in_heredoc(char *line, t_context *ctx,
										char *delimiter)
{
	t_list	*res;

	if (ft_strchr(delimiter, SINGLE_QUOTE)
		|| ft_strchr(delimiter, DOUBLE_QUOTE))
		return (line);
	res = expand_parameters(line, ctx);
	free(line);
	if (res == NULL)
		return (NULL);
	return (res->head->data);
}

static t_redirect	*new_here_doc(char *delimiter, t_context *ctx)
{
	t_redirect	*redirect;
	int			fd;
	char		*line;

	redirect = new_redirect(REDIRECT_HERE_DOC, NULL);
	fd = open_here_doc(redirect);
	if (redirect == NULL || fd == -1)
		return (destroy_and_return_null(redirect));
	while (1)
	{
		line = readline("> ");
		if (line == NULL || g_sig == SIGINT)
		{
			close(fd);
			if (errno != 0)
				return (destroy_and_return_null(redirect));
			return (redirect);
		}
		if (ft_strcmp(delimiter, line) == 0)
			return (redirect);
		line = expand_parameters_in_heredoc(line, ctx, delimiter);
		if (line == NULL)
			return (destroy_and_return_null(redirect));
		ft_putendl_fd(line, fd);
	}
}

// When parsing here document, a tmporary file will be created and
// the file name will be stored in the filename field of the redirect
// structure. The following token will be used as the delimiter
// if the token type is TK_WORD.
t_redirect	*parse_here_doc(t_parser *parser)
{
	char			*delimiter;
	rl_hook_func_t	*tmp;
	t_redirect		*ret;

	if (consume_token(parser, TK_REDIRECT_HERE_DOC))
	{
		delimiter = parse_word(parser);
		if (delimiter == NULL)
			return (NULL);
		tmp = rl_event_hook;
		rl_event_hook = heredoc_readline_hook;
		ret = new_here_doc(delimiter);
		rl_event_hook = tmp;
		return (ret);
	}
	else
		return (NULL);
}
