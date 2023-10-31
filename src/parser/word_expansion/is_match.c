/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_match.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 17:22:22 by smatsuo           #+#    #+#             */
/*   Updated: 2023/10/31 17:16:28 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include <stdlib.h>
#include "word_expansion_internal.h"

static void	destroy_dp(bool **dp, size_t height)
{
	size_t	i;

	i = 0;
	while (i < height)
		free(dp[i++]);
	free(dp);
}

static bool	**calloc_2d_vector(size_t height, size_t width)
{
	bool	**vec;
	size_t	i;

	vec = ft_calloc(height, sizeof(bool *));
	if (vec == NULL)
		return (NULL);
	i = 0;
	while (i < height)
	{
		vec[i] = ft_calloc(width, sizeof(bool));
		if (vec[i] == NULL)
		{
			destroy_dp(vec, height);
			return (NULL);
		}
		i++;
	}
	return (vec);
}

static bool	new_dp_value(t_match_table *table, char pat_char, char text_char,
						char *quote)
{
	size_t	i;
	size_t	j;
	bool	**dp;

	dp = table->dp;
	i = table->i;
	j = table->j;
	if ((pat_char == '"' || pat_char == '\'')
		&& (*quote == '\0' || *quote == pat_char))
	{
		if (*quote == '\0')
			*quote = pat_char;
		else if (*quote == pat_char)
			*quote = '\0';
		return (j == 1 || dp[i][j - 1]);
	}
	if (text_char == pat_char)
		return (dp[i - 1][j - 1]);
	else if (*quote == '\0' && pat_char == '*')
		return (dp[i][j - 1] || dp[i - 1][j]);
	return (false);
}

static bool	update_dp(t_match_table *table, char *text, char *pat)
{
	char	quote;

	table->i = 1;
	while (table->i <= table->text_len)
	{
		table->j = 1;
		quote = '\0';
		while (table->j <= table->pat_len)
		{
			table->dp[table->i][table->j] = new_dp_value(table,
					pat[table->j - 1], text[table->i - 1], &quote);
			table->j++;
		}
		table->i++;
	}
	return (table->dp[table->text_len][table->pat_len]);
}

bool	reg_is_match(char *text, char *pat, bool *is_failed)
{
	t_match_table	table;
	size_t			j;
	bool			res;

	if (text[0] == '.' && pat[0] != '.')
		return (false);
	table.text_len = ft_strlen(text);
	table.pat_len = ft_strlen(pat);
	table.dp = calloc_2d_vector(table.text_len + 1, table.pat_len + 1);
	if (table.dp == NULL)
	{
		*is_failed = true;
		return (false);
	}
	table.dp[0][0] = true;
	j = 1;
	while (j <= table.pat_len)
	{
		table.dp[0][j] = (pat[j - 1] == '*' && table.dp[0][j - 1]);
		j++;
	}
	res = update_dp(&table, text, pat);
	destroy_dp(table.dp, table.text_len + 1);
	return (res);
}
