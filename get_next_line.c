/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: praclet <praclet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 09:14:07 by praclet           #+#    #+#             */
/*   Updated: 2020/12/04 11:13:14 by praclet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

static char	*gnl_concat(char *s1, char *s2, size_t len2)
{
	int		len1;
	char	*res;
	char	*tmp;
	char	*tmp_s1;

	if (!s1 && !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	res = (char *)malloc((len1 + len2 + 1) * sizeof(char));
	if (!res)
	{
		free(s1);
		return (NULL);
	}
	tmp = res;
	if (s1)
	{
		tmp_s1 = s1;
		while (*s1)
			*tmp++ = *s1++;
		free(tmp_s1);
	}
	if (s2)
		while (len2--)
			*tmp++ = *s2++;
	*tmp = 0;
	return (res);
}

static int	gnl_fill_buffer(t_file *file)
{
	if (file->state < 0)
		return (-1);
	if (file->state == 0
		|| (file->start >= 0 && file->start <= file->end))
	{
		ft_next_stop(file);
		return (file->state);
	}
	file->state = read(file->fd, file->buffer, BUFFER_SIZE);
	if (file->state < 0)
	{
		file->start = -1;
		file->end = -1;
		file->pos = -1;
		return (file->state);
	}
	file->start = file->state ? 0 : file->start;
	file->end = file->state ? file->state : file->end;
	file->state = file->state ? 1 : 0;
	ft_next_stop(file);
	return (file->state);
}

static int	gnl_update_file(t_file *file, int rc)
{
	if (file->state < 0)
	{
		file->start = -1;
		file->end = -1;
	}
	else
	{
		if (file->pos < 0)
		{
			file->start = -1;
			file->end = -1;
		}
		else
			file->start += file->pos + 1;
	}
	return (rc);
}

int			get_next_line(int fd, char **line)
{
	static t_list	*dir;
	t_file			*file;

	file = lst_get(&dir, fd);
	if (!file)
		return (-1);
	if (gnl_fill_buffer(file) < 0)
		return (gnl_update_file(file, -1));
	*line = gnl_concat(NULL, file->buffer + file->start,
		(file->pos < 0 ? file->end - file->start + 1 : file->pos));
	if (!*line)
		return (gnl_update_file(file, -1));
	(void)gnl_update_file(file, 1);
	while (file->pos < 0 && file->state > 0)
	{
		if (gnl_fill_buffer(file) < 0)
			return (gnl_update_file(file, -1));
		*line = gnl_concat(*line, file->buffer + file->start,
			(file->pos < 0 ? file->end - file->start + 1 : file->pos));
		if (!*line)
			return (gnl_update_file(file, -1));
		(void)gnl_update_file(file, 1);
	}
	return (file->pos < 0 && file->state == 0 ? 0 : 1);
}
