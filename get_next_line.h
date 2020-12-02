/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: praclet <praclet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 22:21:11 by praclet           #+#    #+#             */
/*   Updated: 2020/12/02 10:39:10 by praclet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define MAX_FILE 50

typedef struct	s_file
{
	int			fd;
	int			state;
	int			start;
	int			end;
	int			pos;
	char		buffer[BUFFER_SIZE];
}				t_file;

typedef struct	s_directory
{
	int			nb_file;
	t_file		tab[MAX_FILE];
}				t_directory;

int				get_next_line(int fd, char **line);
int				ft_next_stop(t_file *file);
int				ft_strlen(const char *str);

#endif
