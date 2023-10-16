/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 14:59:34 by smatsuo           #+#    #+#             */
/*   Updated: 2023/10/16 20:57:13 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "parser_internal.h"
#include "token.h"

static void	destroy_redirect_helper(void *data)
{
	destroy_redirect(data);
}

// io_redirect+
t_list	*parse_redirects(t_parser *parser)
{
	t_list		*redirects;
	t_redirect	*redirect;

	redirects = ft_list_create();
	if (redirects == NULL)
		return (NULL);
	while (peek_redirect(parser))
	{
		redirect = parse_redirect(parser);
		if (redirect == NULL)
		{
			ft_list_destroy(redirects, destroy_redirect_helper);
			return (NULL);
		}
		ft_list_push_back(redirects, redirect);
	}
	return (redirects);
}

static t_redirect	*parse_redirect_helper(t_parser *parser)
{
	t_redirect_type	type;
	char			*filename;

	if (consume_token(parser, TK_REDIRECT_IN))
		type = REDIRECT_IN;
	else if (consume_token(parser, TK_REDIRECT_OUT))
		type = REDIRECT_OUT;
	else if (consume_token(parser, TK_REDIRECT_APPEND))
		type = REDIRECT_APPEND;
	else
		return (NULL);
	filename = parse_word(parser);
	if (filename == NULL)
		return (NULL);
	return (new_redirect(type, filename));
}

t_redirect	*parse_redirect(t_parser *parser)
{
	if (peek_token(parser, TK_REDIRECT_HERE_DOC))
		return (parse_here_doc(parser));
	else if (peek_redirect(parser))
		return (parse_redirect_helper(parser));
	else
		return (NULL);
}
