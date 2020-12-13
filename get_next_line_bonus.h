/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: praclet <praclet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 22:21:11 by praclet           #+#    #+#             */
/*   Updated: 2020/12/13 10:01:25 by praclet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>

typedef struct		s_file
{
	int				fd;
	int				state;
	int				start;
	int				end;
	int				pos;
	char			buffer[BUFFER_SIZE];
}					t_file;

typedef struct		s_list
{
	void			*data;
	struct s_list	*next;
}					t_list;

int					get_next_line(int fd, char **line);
int					ft_strlen(const char *str);
t_file				*lst_get(t_list **list, int fd);
char				*gnl_concat(char *s1, char *s2, size_t len2);
void				lst_remove(t_list **list, t_file **file);

#endif
