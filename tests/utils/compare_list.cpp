/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_list.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 19:16:15 by smatsuo           #+#    #+#             */
/*   Updated: 2023/10/31 10:45:35 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <utility>
#include <cstring>
#include <cstdlib>
#include <gtest/gtest.h>

using namespace std;

extern "C" {
#include "libft.h"
#include "token.h"
}

bool compareTokenStream(t_list *got, vector<pair<t_token_type, const char *>> expect)
{
	if (got->size != expect.size())
		return false;
	for (auto [expect_type, expect_literal] : expect)
	{
		auto top = (t_token *)ft_list_pop_front(got);
		if (top->type != expect_type)
			return false;
		if (strcmp(top->literal, expect_literal) != 0)
			return false;
	}
	return true;
}

bool compareStrList(t_list *got, vector<const char *> expect)
{
	if (got->size != expect.size())
		return false;
	got = ft_list_copy(got, (void *(*)(void *))strdup, free);
	for (auto expect_literal : expect)
	{
		auto top = (char *)ft_list_pop_front(got);
		if (strcmp(top, expect_literal) != 0)
			return false;
	}
	return true;
}

void assertStrList(t_list *got, vector<const char *> expect)
{
	ASSERT_EQ(got->size, expect.size());
	got = ft_list_copy(got, (void *(*)(void *))strdup, free);
	for (auto expect_literal : expect)
	{
		auto top = (char *)ft_list_pop_front(got);
		ASSERT_STREQ(top, expect_literal);
	}
}
