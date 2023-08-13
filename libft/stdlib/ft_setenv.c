/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 21:46:43 by kemizuki          #+#    #+#             */
/*   Updated: 2023/08/14 02:33:48 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdlib.h"
#include "ft_string.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

static char	**find_env(const char *name, size_t name_len)
{
	extern char	**environ;
	char		**envp;

	if (environ == NULL)
		return (NULL);
	envp = environ;
	while (*envp != NULL)
	{
		if (!ft_strncmp(*envp, name, name_len) && (*envp)[name_len] == '=')
			return (envp);
		++envp;
	}
	return (envp);
}

static void	*reallocate_environ(void *ptr, size_t new_size, size_t old_size)
{
	void	*new;

	new = malloc(new_size);
	if (ptr == NULL)
		return (new);
	if (new != NULL)
	{
		ft_memcpy(new, ptr, old_size);
		free(ptr);
	}
	return (new);
}

static int	ensure_sufficient_environ_allocated(char ***envpp)
{
	static char	**last_environ;
	extern char	**environ;
	char		**new_environ;
	size_t		env_len;

	if (*envpp == NULL || **envpp == NULL)
	{
		env_len = *envpp - environ;
		printf("%zu\n", env_len);
		new_environ = reallocate_environ(last_environ, (env_len + 2)
				* sizeof(char *), (env_len + 1) * sizeof(char *));
		if (new_environ == NULL)
			return (-1);
		if (environ != last_environ)
			ft_memcpy(new_environ, environ, env_len * sizeof(char *));
		new_environ[env_len] = NULL;
		new_environ[env_len + 1] = NULL;
		environ = new_environ;
		*envpp = new_environ + env_len;
		last_environ = environ;
	}
	return (0);
}

static int	add_to_environ(const char *name, const char *value,
		const char *combined, int overwrite)
{
	const size_t	name_len = ft_strlen(name);
	char			**envp;
	size_t			value_len;

	envp = find_env(name, name_len);
	if (ensure_sufficient_environ_allocated(&envp) != 0)
		return (-1);
	if (*envp == NULL || overwrite)
	{
		if (combined != NULL)
			*envp = (char *)combined;
		else
		{
			value_len = ft_strlen(value);
			*envp = malloc(name_len + value_len + 2);
			if (*envp == NULL)
				return (-1);
			ft_memcpy(*envp, name, name_len);
			(*envp)[name_len] = '=';
			ft_memcpy(*envp + name_len + 1, value, value_len + 1);
		}
	}
	return (0);
}

int	ft_setenv(const char *name, const char *value, int overwrite)
{
	if (name == NULL || *name == '\0' || ft_strchr(name, '=') != NULL)
	{
		errno = EINVAL;
		return (-1);
	}
	return (add_to_environ(name, value, NULL, overwrite));
}
