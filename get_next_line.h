/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogoman <ogoman@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 07:31:34 by ogoman            #+#    #+#             */
/*   Updated: 2023/11/24 15:13:12 by ogoman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42

# endif //BUFFER_SIZE 

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

static void	copy_s2_in_s1(char *s1, char *s2);
char		*get_next_line(int fd);
static int	ft_find_line(char *buf, char **line);
static char	*free_line(char **line);
char		*ft_strjoin(char *s1, char *s2);
size_t		ft_strlen(const char *s);
void		*ft_calloc(size_t count, size_t size);

#endif // GET_NEXT_LINE-_H
