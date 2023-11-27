/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogoman <ogoman@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 09:16:52 by ogoman            #+#    #+#             */
/*   Updated: 2023/11/27 15:36:20 by ogoman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	count;

	count = 0;
	while (str[count])
		count++;
	return (count);
}

char	*read_line(int fd, char *line, void *buf, ssize_t *bytes_read)
{
	void	*next_l_s;
	size_t	l_length;

	next_l_s = NULL;
	l_length = 0;
	while (*bytes_read != -1)
	{
		next_l_s = custom_memchr(buf, next_l_s, '\n', *bytes_read);
		if (next_l_s != NULL && next_l_s != buf + *bytes_read)
			line = join_str(line, buf, l_length, (next_l_s - buf) + 1);
		else if (*bytes_read > 0)
			line = join_str(line, buf, l_length, *bytes_read);
		l_length += *bytes_read;
		if ((!line && l_length != 0) || next_l_s)
			break ;
		*bytes_read = read(fd, buf, BUFFER_SIZE);
		if (*bytes_read < BUFFER_SIZE)
			next_l_s = buf + *bytes_read;
	}
	return (line);
}

void	save_buffer(char *buf_save, ssize_t buf_l)
{
	char	*end;

	if (buf_l > 0)
		end = (char *)custom_memchr(buf_save, NULL, '\n', buf_l);
	else
		end = NULL;
	if (end && end + 1 < (buf_save + buf_l))
	{
		custom_memcpy(buf_save, end + 1, (buf_l - ((end + 1) - buf_save)));
		buf_save[(buf_l - ((end + 1) - buf_save))] = 0;
	}
	else
		buf_save[0] = 0;
}

char	*get_next_line(int fd)
{
	char		*line_was_read;
	ssize_t		byte_was_read;
	static char	buffer_save[BUFFER_SIZE + 1] = {'\0'};

	byte_was_read = (ssize_t) ft_strlen(buffer_save);
	line_was_read = NULL;
	line_was_read = read_line(fd, line_was_read, buffer_save, &byte_was_read);
	if (line_was_read && byte_was_read == -1)
	{
		free(line_was_read);
		line_was_read = NULL;
	}
	save_buffer(buffer_save, byte_was_read);
	return (line_was_read);
}

// int main(void)
// {
// 	int fd;
// 	fd = open("file.txt", O_RDONLY);
// 	printf("%s\n", get_next_line(fd));
// 	// close(fd);
// 	return (0);
// }

// void	copy_s2_in_s1(char *s1, char *s2)
// {
// 	while (*s2)
// 	{
// 		*s1 = *s2;
// 		s1++;
// 		s2++;
// 	}
// 	*s1 = '\0';
// }

// int	ft_find_line(char *buf, char **remainder)
// {
// 	int		i;
// 	int		j;
// 	int		flag_line;
// 	char	*find_line;

// 	i = 0;
// 	while (buf[i] && buf[i] != '\n')
// 		i++;
// 	flag_line = 0;
// 	if (buf[i] == '\n')
// 		flag_line = 1;
// 	find_line = ft_calloc(i + flag_line + 1, 1);
// 	if (find_line == NULL)
// 		return (-1);
// 	j = 0;
// 	while (j < i + flag_line)
// 	{
// 		find_line[j] = buf[j];
// 		j++;
// 	}
// 	*remainder = ft_strjoin(*remainder, find_line);
// 	if (remainder == NULL)
// 		return (-1);
// 	copy_s2_in_s1(buf, &buf[i + flag_line]);
// 	return (flag_line);
// }

// char	*free_line(char **remainder)
// {
// 	if (*remainder != NULL)
// 		free(*remainder);
// 	return (NULL);
// }

// char	*get_next_line(int fd)
// {
// 	static char	buf[BUFFER_SIZE + 1];
// 	char		*remainder;
// 	int			byte_was_read;
// 	int			flag_line;

// 	remainder = NULL;
// 	flag_line = 0;
// 	if (read(fd, NULL, 0) < 0)
// 		return (NULL);
// 	while (flag_line == 0)
// 	{
// 		flag_line = ft_find_line(buf, &remainder);
// 		if (flag_line == -1)
// 			return (free_line(&remainder));
// 		if (flag_line == 0)
// 		{
// 			byte_was_read = read(fd, buf, BUFFER_SIZE);
// 			if (byte_was_read == 0 && *remainder)
// 				flag_line = 1;
// 			else if (byte_was_read <= 0)
// 				return (free_line(&remainder));
// 			buf[byte_was_read] = '\0';
// 		}
// 	}
// 	return (remainder);
// }

// int main(void)
// {
// 	int fd;
// 	fd = open("file.txt", O_RDONLY);
// 	printf("%s\n", get_next_line(fd));
// 	// close(fd);
// 	return (0);
// }