/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: praclet <praclet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 04:19:28 by praclet           #+#    #+#             */
/*   Updated: 2020/12/01 07:30:51 by praclet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "get_next_line.h"

int		ft_next_stop(t_file *file)
{
	size_t	i;
	char	*cur;
	size_t	n;

	cur = file->buffer + file->start;
	n = BUFFER_SIZE - file->start;
	i = 0;
	while (*cur && i < n)
	{
		if (*cur == '\n')
			return (i);
		cur++;
		i++;
	}
	return (-1);
}

int		ft_strlen(const char *str)
{
	int res;

	res = 0;
	if (str)
		while (*str++)
			res++;
	return (res);
}
