/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_list.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 19:16:15 by smatsuo           #+#    #+#             */
/*   Updated: 2023/10/31 11:33:50 by smatsuo          ###   ########.fr       */
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

::testing::AssertionResult compareStrList(t_list *got, vector<const char *> expects)
{
	if (got->size != expects.size())
		return ::testing::AssertionFailure() << "expected size: " << expects.size() << ", got: " << got->size;
	got = ft_list_copy(got, (void *(*)(void *))strdup, free);
	for (auto expect : expects)
	{
		auto filename = (char *)ft_list_pop_front(got);
		if (strcmp(filename, expect) != 0)
			return ::testing::AssertionFailure() << "expected: " << expect << ", got: " << filename;
	}
	return ::testing::AssertionSuccess();
}

::testing::AssertionResult compareStrList(t_list *got, vector<const char *> expects, bool strictOrder)
{
	if (strictOrder)
		return compareStrList(got, expects);
	if (got->size != expects.size())
		return ::testing::AssertionFailure() << "expected size: " << expects.size() << ", got: " << got->size;
	got = ft_list_copy(got, (void *(*)(void *))strdup, free);
	while (got->size > 0)
	{
		auto filename = (char *)ft_list_pop_front(got);
		bool found = false;
		for (auto expect : expects) {
			if (strcmp(filename, expect) == 0) {
				found = true;
				break;
			}
		}
		if (!found)
			return ::testing::AssertionFailure() << "not found: " << filename;
	}
	return ::testing::AssertionSuccess();
}
