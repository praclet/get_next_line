/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: praclet <praclet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 09:14:07 by praclet           #+#    #+#             */
/*   Updated: 2020/12/02 10:42:27 by praclet          ###   ########lyon.fr   */
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

	if (!s1 && !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	res = (char *)malloc((len1 + len2 + 1) * sizeof(char));
	if (!res)
		return (NULL);
	tmp = res;
	if (s1)
		while (*s1)
			*tmp++ = *s1++;
	free(s1);
	if (s2)
		while (len2--)
			*tmp++ = *s2++;
	*tmp = 0;
	return (res);
}

static int	gnl_fill_buffer(t_file *file)
{
	int tmp;

	if (file->state < 0)
		return (-1);
	if (file->start >= 0)
	{
		file->pos = ft_next_stop(file);
		return (file->state);
	}
	tmp = read(file->fd, file->buffer, BUFFER_SIZE);
	if (tmp <= 0)
	{
		file->start = -1;
		file->end = -1;
		file->pos = -1;
		file->state = tmp;
		return (tmp);
	}
	file->start = 0;
	file->end = tmp - 1;
	file->pos = ft_next_stop(file);
	file->state = 1;
	return (tmp ? 1 : 0);
}

static int	gnl_get_file_index(t_directory *dir, int fd)
{
	int	i;

	i = 0;
	while (i < dir->nb_file && dir->tab[i].fd != fd)
		i++;
	if (i >= dir->nb_file)
	{
		if (i > MAX_FILE)
			return (-1);
		dir->tab[i].fd = fd;
		dir->tab[i].start = -1;
		dir->tab[i].end = -1;
		dir->tab[i].state = 1;
		dir->nb_file++;
	}
	return (i);
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
		if (file->pos <= 0)
		{
			file->start = -1;
			file->end = -1;
		}
		else
			file->start += file->pos;
	}
	return (rc);
}

int			get_next_line(int fd, char **line)
{
	t_directory	dir;
	t_file		*file;
	int			tmp;

	tmp = gnl_get_file_index(&dir, fd);
	if (tmp < 0)
		return (-1);
	file = &dir.tab[tmp];
	if (gnl_fill_buffer(file) < 0)
		return (gnl_update_file(file, -1));
	*line = gnl_concat(NULL, file->buffer + file->start,
		(file->pos < 0 ? file->end - file->start : file->pos) + 1);
	if (!*line)
		return (gnl_update_file(file, -1));
	while (file->pos < 0 && file->state > 0)
	{
		if (gnl_fill_buffer(file) < 0)
			return (gnl_update_file(file, -1));
		*line = gnl_concat(*line, file->buffer + file->start,
			(file->pos < 0 ? file->end - file->start : file->pos) + 1);
		if (!*line)
			return (gnl_update_file(file, -1));
	}
	return (gnl_update_file(file, file->pos < 0 && file->state == 0 ? 0 : 1));
}
