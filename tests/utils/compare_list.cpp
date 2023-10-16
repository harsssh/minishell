/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_list.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 19:16:15 by smatsuo           #+#    #+#             */
/*   Updated: 2023/09/25 23:55:08 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <utility>
#include <cstring>

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
