/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: praclet <praclet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 04:19:28 by praclet           #+#    #+#             */
/*   Updated: 2020/12/07 15:45:49 by praclet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "get_next_line.h"

static t_file	*lst_add(t_list **list, int fd)
{
	t_list *res;
	t_file *data;

	res = (t_list *)malloc(sizeof(t_list));
	data = (t_file *)malloc(sizeof(t_file));
	if (!res || !data)
	{
		free(res);
		free(data);
		return (NULL);
	}
	data->fd = fd;
	data->state = 1;
	data->start = -1;
	data->end = -1;
	data->pos = -1;
	res->data = data;
	res->next = *list;
	*list = res;
	return ((t_file *)res->data);
}

t_file			*lst_get(t_list **list, int fd)
{
	t_list *lst;

	lst = *list;
	while (lst)
	{
		if (((t_file *)lst->data)->fd == fd)
			return ((t_file *)lst->data);
		lst = lst->next;
	}
	return (lst_add(list, fd));
}

void			ft_next_stop(t_file *file)
{
	size_t	i;
	char	*cur;
	size_t	n;

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

int				ft_strlen(const char *str)
{
	int res;

	res = 0;
	if (str)
		while (*str++)
			res++;
	return (res);
}

char			*gnl_new_line(t_file *file, char *s1)
{
	if (file->state == 0 && file->start == -1)
		return (gnl_concat(s1, file->buffer, 0));
	else
		return (gnl_concat(s1, file->buffer + file->start,
			file->pos < 0 ? file->end - file->start + 1 : file->pos));
}
