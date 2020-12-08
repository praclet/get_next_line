/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: praclet <praclet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 22:21:11 by praclet           #+#    #+#             */
/*   Updated: 2020/12/07 15:52:41 by praclet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

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
char				*gnl_new_line(t_file *file, char *s1);
int					ft_strlen(const char *str);
t_file				*lst_get(t_list **list, int fd);
char				*gnl_new_line(t_file *file, char *s1);

#endif
