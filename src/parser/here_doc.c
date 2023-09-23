/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 18:19:43 by smatsuo           #+#    #+#             */
/*   Updated: 2023/09/24 07:55:28 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "parser_internal.h"
#include "fcntl.h"
#include <sys/_types/_s_ifmt.h>
#include <sys/fcntl.h>
#include <readline/readline.h>
#include <unistd.h>

static t_redirect	*new_here_doc(char *delimiter)
{
//	int		fd;
//	char	*line;
//
//	fd = open("/tmp/here-doc.minishell",
//			O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
//	if (fd == -1)
//	{
//		fd = open("/var/tmp/here-doc.minishell",
//				O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
//		if (fd == -1)
//		{
//			fd = open("./here-doc.minishell",
//					O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
//			if (fd == -1)
//
//		}
//		return (NULL);
//	}
//	while (1)
//	{
//		line = readline("> ");
//		if (line == NULL)
//		{
//			close(fd);
//			return (NULL);
//		}
//		if (ft_strcmp(delimiter, line) == 0)
//			break ;
//		write(fd, line, ft_strlen(line));
//	}
	(void)delimiter;
	return (new_redirect(REDIRECT_HERE_DOC, "/tmp/here-doc.minishell"));
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
