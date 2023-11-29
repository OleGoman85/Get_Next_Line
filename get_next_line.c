/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogoman <ogoman@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 09:16:52 by ogoman            #+#    #+#             */
/*   Updated: 2023/11/29 15:20:03 by ogoman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// This function puts together a new string by adding a specific part of
//				the data we read (from the buffer) to the existing string.
//It takes care of managing memory to ensure everything fits.
static char	*append_string(char *old_res, char *buf, ssize_t start, ssize_t len)
{
	ssize_t	i;
	char	*result;

	result = (char *)malloc(sizeof(char) * (ft_strlen(old_res) + len + 1));
	if (!result)
	{
		free(old_res);
		return (NULL);
	}
	i = 0;
	while (old_res[i])
	{
		result[i] = old_res[i];
		i++;
	}
	free(old_res);
	result[i + len] = '\0';
	while (len)
	{
		len--;
		result[i + len] = buf[start + len];
	}
	return (result);
}

// Reads data from a file descriptor (fd) into a buffer (buffer)
//					with a specified size (BUFFER_SIZE).
// It updates the result string (result) dynamically
static int	read_to_buf(int fd, char **result, char *buffer)
{
	ssize_t	read_result;

	read_result = read(fd, buffer, BUFFER_SIZE);
	if (read_result == 0 && (**result))
		return (0);
	if (read_result <= 0)
	{
		free(*result);
		*result = NULL;
		return (0);
	}
	buffer[read_result] = '\0';
	return (1);
}

// This function is used when find a complete line in data.
// It adds the remaining part of the line to result string and
//						prepares for the next round of reading.
static char	*finish_line(char *res, char *buf, ssize_t *line_start,
		ssize_t *line_len)
{
	res = append_string(res, buf, *line_start, *line_len);
	*line_start += *line_len;
	*line_len = 0;
	return (res);
}

// This function is called when no newline was found in buffer
// 		and therefore all we need to do is append buffer to result.
// It returns 0 in case or error (malloc fail), returns 1 if success.
// line_start and line_len values are also reset
//								in preparation for next buffer read.
static int	add_buf_to_res(char **res, char *buf, ssize_t *line_start,
		ssize_t *line_len)
{
	*res = append_string(*res, buf, *line_start, BUFFER_SIZE - *line_start);
	if (!*res)
		return (0);
	*line_start = 0;
	*line_len = 0;
	return (1);
}

// line_len indicates index in the buffer
//							after the end of the current line.
// line_start indicates index in the buffer from which 
//						the next line should be started to be read.
//0 value indicates that new info needs to be read to buffer.
// First obvious errors are handled
// 						and res is initialised as an empty string.
// New data is being read to buffer and added to res until either
//			newline is found or EOF is reached (or error happened)
// If newline was found, it and everything before it is added to res
//												and res is returned.
// If EOF reached and there was something in res, res is returned,
//										otherwise NULL is returned.
// The STATIC keyword means that these variables will retain their
//				values between calls to the function get_next_line.
// So, after the first call, the values of LINE_START and LINE_LEN
// 					BUFFER will be preserved, and the function will
//									resume from where it left off. 
char	*get_next_line(int fd)
{
	char			*result;
	static char		buffer[BUFFER_SIZE + 1];
	static ssize_t	string_start = 0;
	static ssize_t	string_len = 0;

	result = (char *)malloc(sizeof(char) * 1);
	if (!result)
		return (NULL);
	result[0] = '\0';
	while (!string_len)
	{
		if (!string_start && !read_to_buf(fd, &result, buffer))
			return (result);
		string_len = find_new_string(buffer, string_start) - string_start;
		if (string_len > 0)
			return (finish_line(result, buffer, &string_start, &string_len));
		else if (!add_buf_to_res(&result, buffer, &string_start, &string_len))
			return (NULL);
	}
	return (NULL);
}

// char	*reader(char *line, int fd)
// {
// 	char	*buff;
// 	int		was_read;

// 	was_read = 1;
// 	buff = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
// 	if (!buff)
// 		return (0);
// 	while (!ft_strchr(line, '\n') && was_read != 0)
// 	{
// 		was_read = read(fd, buff, BUFFER_SIZE);
// 		if (was_read == -1)
// 		{
// 			free(buff);
// 			return (0);
// 		}
// 		buff[was_read] = '\0';
// 		line = ft_strjoin(line, buff);
// 	}
// 	free(buff);
// 	return (line);
// }

// char	*get_one_line(char *st_line)
// {
// 	char	*line;
// 	int		i;

// 	i = 0;
// 	if (st_line[i] == '\0')
// 		return (0);
// 	while (st_line[i] && st_line[i] != '\n')
// 		i++;
// 	line = (char *)malloc(sizeof(char) * (i + 2));
// 	if (!line)
// 		return (0);
// 	i = 0;
// 	while (st_line[i] && st_line[i] != '\n')
// 	{
// 		line[i] = st_line[i];
// 		i++;
// 	}
// 	if (st_line[i] == '\n')
// 	{
// 		line[i] = st_line[i];
// 		i++;
// 	}
// 	line[i] = '\0';
// 	return (line);
// }

// char	*trim(char *st_line)
// {
// 	char	*line;
// 	int		before_n;
// 	int		after_n;

// 	before_n = 0;
// 	while (st_line[before_n] && st_line[before_n] != '\n')
// 		before_n++;
// 	if (!st_line[before_n])
// 	{
// 		free(st_line);
// 		return (NULL);
// 	}
// 	line = (char *)malloc(sizeof(char) * (ft_strlen(st_line) - before_n + 1));
// 	if (!line)
// 	{
// 		free(st_line);
// 		return (NULL);
// 	}
// 	before_n++;
// 	after_n = 0;
// 	while (st_line[before_n])
// 		line[after_n++] = st_line[before_n++];
// 	line[after_n] = '\0';
// 	free(st_line);
// 	return (line);
// }

// char	*get_next_line(int fd)
// {
// 	char		*line;
// 	static char	*remainder = NULL;

// 	if (fd < 0 || BUFFER_SIZE <= 0)
// 		return (NULL);
// 	remainder = reader(remainder, fd);
// 	if (!remainder)
// 		return (NULL);
// 	line = get_one_line(remainder);
// 	remainder = trim(remainder);
// 	if (!remainder)
// 		free(remainder);
// 	return (line);
// }

// int	main(int n, char *args[])
// {
// 	char	*line;
// 	int		fd;

// 	if (n < 2)
// 		return (-1);
// 	fd = open(args[1], O_RDONLY);
// 	if (fd == -1)
// 		return (-1);
// 	line = NULL;
// 	do {
// 		if (line)
// 			free(line);
// 		line = get_next_line(fd);
// 		printf("%s", line);
// 	} while (line);
// 	close(fd);
// }

//////////////////////////////////////////////////

// size_t	ft_strlen(const char *str)
// {
// 	size_t	count;

// 	count = 0;
// 	while (str[count])
// 		count++;
// 	return (count);
// }

// char	*read_line(int fd, char *line, void *buf, ssize_t *bytes_read)
// {
// 	void	*next_l_s;
// 	size_t	l_length;

// 	next_l_s = NULL;
// 	l_length = 0;
// 	while (*bytes_read != -1)
// 	{
// 		next_l_s = custom_memchr(buf, next_l_s, '\n', *bytes_read);
// 		if (next_l_s != NULL && next_l_s != buf + *bytes_read)
// 			line = join_str(line, buf, l_length, (next_l_s - buf) + 1);
// 		else if (*bytes_read > 0)
// 			line = join_str(line, buf, l_length, *bytes_read);
// 		l_length += *bytes_read;
// 		if ((!line && l_length != 0) || next_l_s)
// 			break ;
// 		*bytes_read = read(fd, buf, BUFFER_SIZE);
// 		if (*bytes_read < BUFFER_SIZE)
// 			next_l_s = buf + *bytes_read;
// 	}
// 	return (line);
// }

// void	save_buffer(char *buf_save, ssize_t buf_l)
// {
// 	char	*end;

// 	if (buf_l > 0)
// 		end = (char *)custom_memchr(buf_save, NULL, '\n', buf_l);
// 	else
// 		end = NULL;
// 	if (end && end + 1 < (buf_save + buf_l))
// 	{
// 		custom_memcpy(buf_save, end + 1, (buf_l - ((end + 1) - buf_save)));
// 		buf_save[(buf_l - ((end + 1) - buf_save))] = 0;
// 	}
// 	else
// 		buf_save[0] = 0;
// }

// char	*get_next_line(int fd)
// {
// 	char		*line_was_read;
// 	ssize_t		byte_was_read;
// 	static char	buffer_save[BUFFER_SIZE + 1] = {'\0'};

// 	byte_was_read = (ssize_t) ft_strlen(buffer_save);
// 	line_was_read = NULL;
// 	line_was_read = read_line(fd, line_was_read, buffer_save, &byte_was_read);
// 	if (line_was_read && byte_was_read == -1)
// 	{
// 		free(line_was_read);
// 		line_was_read = NULL;
// 	}
// 	save_buffer(buffer_save, byte_was_read);
// 	return (line_was_read);
// }

//////////////////////////////////////////

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