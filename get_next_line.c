/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: praclet <praclet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 09:14:07 by praclet           #+#    #+#             */
/*   Updated: 2020/12/08 07:37:38 by praclet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

static void	ft_next_stop(t_file *file)
{
	size_t	i;
	char	*cur;
	size_t	n;

	if (file->start < 0 || file->end < 0 || file->start >= BUFFER_SIZE)
	{
		file->pos = -1;
		return ;
	}
	cur = file->buffer + file->start;
	n = BUFFER_SIZE - file->start;
	i = 0;
	while (i < n)
	{
		if (*cur == '\n')
		{
			file->pos = i;
			return ;
		}
		cur++;
		i++;
	}
	file->pos = -1;
}

static void	gnl_update_data_file(t_file *file, int start, int end, int pos)
{
	file->start = start;
	file->end = end;
	file->pos = pos;
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
		gnl_update_data_file(file, -1, -1, -1);
		return (file->state);
	}
	if (file->state)
		gnl_update_data_file(file, 0, file->state - 1, file->pos);
	file->state = !!file->state;
	ft_next_stop(file);
	return (file->state);
}

static int	gnl_update_file(t_file *file, int rc)
{
	if (file->state < 0)
		gnl_update_data_file(file, -1, -1, -1);
	else
	{
		if (file->pos < 0)
			gnl_update_data_file(file, -1, -1, -1);
		else
			file->start += file->pos + 1;
		if (file->start > -1 && file->start < BUFFER_SIZE
			&& file->start > file->end)
			file->state = 0;
	}
	return (rc);
}

int			get_next_line(int fd, char **line)
{
	static t_list	*dir;
	t_file			*file;
	int				tmp;

	file = lst_get(&dir, fd);
	if (!file)
		return (-1);
	if ((tmp = gnl_fill_buffer(file)) < 0)
		return (gnl_update_file(file, tmp));
	*line = gnl_new_line(file, NULL);
	if (!*line)
		return (gnl_update_file(file, -1));
	(void)gnl_update_file(file, 1);
	while (file->pos < 0 && file->state > 0)
	{
		if ((tmp = gnl_fill_buffer(file)) < 0)
			return (gnl_update_file(file, -1));
		if (tmp)
			*line = gnl_new_line(file, *line);
		if (!*line)
			return (gnl_update_file(file, -1));
		(void)gnl_update_file(file, 1);
	}
	return (file->state);
}
