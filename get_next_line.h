/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogoman <ogoman@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 07:31:34 by ogoman            #+#    #+#             */
/*   Updated: 2023/11/29 15:16:49 by ogoman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 255
# endif

char	*get_next_line(int fd);
ssize_t	find_new_string(char *buffer, ssize_t start_index);
ssize_t	ft_strlen(const char *s);

#endif // GET_NEXT_LINE_H;