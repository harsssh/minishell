/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:54:55 by kemizuki          #+#    #+#             */
/*   Updated: 2023/06/02 20:11:05 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "ft_string.h"
#include <unistd.h>
#include <stdlib.h>

static ssize_t	read_file(t_buffer *buf)
{
	ssize_t	len;

	if (BUFFER_SIZE == 0)
		return (0);
	len = read(buf->fd, buf->buf, BUFFER_SIZE);
	if (len > 0)
		buf->len = len;
	else if (len < 0)
		buf->read_failed = true;
	return (len);
}

static char	*copy_prefix_and_shift(t_buffer *buf, size_t len)
{
	char	*prefix;
	size_t	n;

	if (buf == NULL)
		return (NULL);
	n = 0;
	while (n < len && buf->buf[n])
		n++;
	prefix = malloc((n + 1) * sizeof(char));
	if (prefix == NULL)
		return (NULL);
	ft_memmove(prefix, buf->buf, n);
	prefix[n] = '\0';
	buf->len -= n;
	ft_memmove(buf->buf, buf->buf + n, buf->len);
	return (prefix);
}

static char	*extend_line(char *line, t_buffer *buf, size_t len)
{
	char	*prefix;
	char	*tmp;

	prefix = copy_prefix_and_shift(buf, len);
	if (prefix == NULL)
	{
		free(line);
		return (NULL);
	}
	tmp = line;
	line = ft_strjoin(line, prefix);
	free(tmp);
	free(prefix);
	return (line);
}

static char	*get_line(t_buffer *buf)
{
	char	*line;
	char	*newline_addr;
	size_t	copy_len;

	line = NULL;
	while (buf->len > 0 || read_file(buf) > 0)
	{
		newline_addr = ft_memchr(buf->buf, '\n', buf->len);
		if (newline_addr == NULL)
			copy_len = buf->len;
		else
			copy_len = newline_addr - buf->buf + 1;
		line = extend_line(line, buf, copy_len);
		if (line == NULL || newline_addr != NULL)
			break ;
	}
	if (buf->read_failed)
	{
		free(line);
		line = NULL;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static t_buffer_list	*list;
	t_buffer_list			*node;
	char					*line;
	size_t					i;

	node = list;
	while (node != NULL && node->buf->fd != fd)
		node = node->next;
	if (node == NULL)
	{
		node = push_front_new_node(&list, fd);
		if (node == NULL)
			return (NULL);
	}
	line = get_line(node->buf);
	i = 0;
	while (line && line[i] && line[i] != '\n')
		i++;
	if (line == NULL || line[i] == '\0')
		remove_node(&list, fd);
	return (line);
}
