/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: praclet <praclet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 04:19:28 by praclet           #+#    #+#             */
/*   Updated: 2020/12/07 15:54:53 by praclet          ###   ########lyon.fr   */
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

int				ft_strlen(const char *str)
{
	int res;

	res = 0;
	if (str)
		while (*str++)
			res++;
	return (res);
}

static char		*gnl_concat(char *s1, char *s2, size_t len2)
{
	char	*res;
	char	*tmp;
	char	*tmp_s1;

	if (!s1 && !s2)
		return (NULL);
	if (!s2)
		return (s1);
	if (!(res = (char *)malloc((ft_strlen(s1) + len2 + 1) * sizeof(char))))
	{
		free(s1);
		return (NULL);
	}
	tmp = res;
	tmp_s1 = s1;
	if (s1)
		while (*s1)
			*tmp++ = *s1++;
	if (s1)
		free(tmp_s1);
	if (s2)
		while (len2--)
			*tmp++ = *s2++;
	*tmp = 0;
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
