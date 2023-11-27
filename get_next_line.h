/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogoman <ogoman@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 07:31:34 by ogoman            #+#    #+#             */
/*   Updated: 2023/11/27 15:51:25 by ogoman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42

# endif //BUFFER_SIZE 

// # include <fcntl.h> // for open in main (del)
// # include <stdio.h> // for printf in main (del)
# include <stdlib.h>
# include <unistd.h>
// # include <stddef.h> // ?
// # include <stdio.h> // main (del)

char	*get_next_line(int fd);
void	*custom_memchr(const void *buffer, void *start, int tar, size_t size);
void	*custom_memcpy(void *destination, const void *source, size_t num_bytes);
char	*join_str(void *dest, void const *source, size_t dest_l, size_t src_l);
void	save_buffer(char *buf_save, ssize_t buf_l);
char	*read_line(int fd, char *line, void *buf, ssize_t *bytes_read);
size_t	ft_strlen(const char *str);

#endif // GET_NEXT_LINE_H;
