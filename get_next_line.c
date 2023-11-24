/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogoman <ogoman@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 09:16:52 by ogoman            #+#    #+#             */
/*   Updated: 2023/11/24 15:28:38 by ogoman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <unistd.h>
// #include <stdlib.h>
// #include <fcntl.h>
// #include <stdio.h>
// #include <stdio.h>
// #include "get_next_line.h"

// char *ft_strchr(char *s, int c);
// char *ft_strjoin(char *left_str, char *buff);
// char *ft_get_line(char *left_str);
// char *ft_new_left_str(char *left_str);

// char	*ft_read_to_left_str(int fd, char *left_str)
// {
// 	char	*buff;
// 	int		rd_bytes;

// 	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
// 	if (!buff)
// 		return (NULL);
// 	rd_bytes = 1;
// 	while (!ft_strchr(left_str, '\n') && rd_bytes != 0)
// 	{
// 		rd_bytes = read(fd, buff, BUFFER_SIZE);
// 		if (rd_bytes == -1)
// 		{
// 			free(buff);
// 			return (NULL);
// 		}
// 		buff[rd_bytes] = '\0';
// 		left_str = ft_strjoin(left_str, buff);
// 	}
// 	free(buff);
// 	return (left_str);
// }

// char	*get_next_line(int fd)
// {
// 	char		*line;
// 	static char	*left_str;

// 	if (fd < 0 || BUFFER_SIZE <= 0)
// 		return (0);
// 	left_str = ft_read_to_left_str(fd, left_str);
// 	if (!left_str)
// 		return (NULL);
// 	line = ft_get_line(left_str);
// 	left_str = ft_new_left_str(left_str);
// 	return (line);
// }

// size_t	ft_strlen(char *s)
// {
// 	size_t	i;

// 	i = 0;
// 	if (!s)
// 		return (0);
// 	while (s[i] != '\0')
// 		i++;
// 	return (i);
// }

// char	*ft_strchr(char *s, int c)
// {
// 	int	i;

// 	i = 0;
// 	if (!s)
// 		return (0);
// 	if (c == '\0')
// 		return ((char *)&s[ft_strlen(s)]);
// 	while (s[i] != '\0')
// 	{
// 		if (s[i] == (char) c)
// 			return ((char *)&s[i]);
// 		i++;
// 	}
// 	return (0);
// }

// char	*ft_strjoin(char *left_str, char *buff)
// {
// 	size_t	i;
// 	size_t	j;
// 	char	*str;

// 	if (!left_str)
// 	{
// 		left_str = (char *)malloc(1 * sizeof(char));
// 		left_str[0] = '\0';
// 	}
// 	if (!left_str || !buff)
// 		return (NULL);
// 	str = malloc(sizeof(char) * ((ft_strlen(left_str) + ft_strlen(buff)) + 1));
// 	if (str == NULL)
// 		return (NULL);
// 	i = -1;
// 	j = 0;
// 	if (left_str)
// 		while (left_str[++i] != '\0')
// 			str[i] = left_str[i];
// 	while (buff[j] != '\0')
// 		str[i++] = buff[j++];
// 	str[ft_strlen(left_str) + ft_strlen(buff)] = '\0';
// 	free(left_str);
// 	return (str);
// }

// char	*ft_get_line(char *left_str)
// {
// 	int		i;
// 	char	*str;

// 	i = 0;
// 	if (!left_str[i])
// 		return (NULL);
// 	while (left_str[i] && left_str[i] != '\n')
// 		i++;
// 	str = (char *)malloc(sizeof(char) * (i + 2));
// 	if (!str)
// 		return (NULL);
// 	i = 0;
// 	while (left_str[i] && left_str[i] != '\n')
// 	{
// 		str[i] = left_str[i];
// 		i++;
// 	}
// 	if (left_str[i] == '\n')
// 	{
// 		str[i] = left_str[i];
// 		i++;
// 	}
// 	str[i] = '\0';
// 	return (str);
// }

// char	*ft_new_left_str(char *left_str)
// {
// 	int		i;
// 	int		j;
// 	char	*str;

// 	i = 0;
// 	while (left_str[i] && left_str[i] != '\n')
// 		i++;
// 	if (!left_str[i]) // No more newline characters
// 	{
// 		free(left_str);
// 		return (NULL);
// 	}
// 	str = (char *)malloc(sizeof(char) * (ft_strlen(left_str) - i));
// 	if (!str)
// 		return (NULL);
// 	i++;
// 	j = 0;
// 	while (left_str[i])
// 		str[j++] = left_str[i++];
// 	str[j] = '\0';
// 	free(left_str);
// 	return (str);
// }

// int	main(void)
// {
// 	char	*line;
// 	int		i;
// 	int		fd1;
// 	int		fd2;
// 	int		fd3;
// 	fd1 = open("file.txt", O_RDONLY);
// 	fd2 = open("file.txt", O_RDONLY);
// 	fd3 = open("file.txt", O_RDONLY);
// 	i = 1;
// 	while (i < 7)
// 	{
// 		line = get_next_line(fd1);
// 		printf("line [%02d]: %s", i, line);
// 		free(line);
// 		line = get_next_line(fd2);
// 		printf("line [%02d]: %s", i, line);
// 		free(line);
// 		line = get_next_line(fd3);
// 		printf("line [%02d]: %s", i, line);
// 		free(line);
// 		i++;
// 	}
// 	close(fd1);
// 	close(fd2);
// 	close(fd3);
// 	return (0);
// }

#include "get_next_line.h"

static void	copy_s2_in_s1(char *s1, char *s2)
{
	while (*s2)
	{
		*s1 = *s2;
		s1++;
		s2++;
	}
	*s1 = '\0';
}

static int	ft_find_line(char *buf, char **line)
{
	int		i;
	int		j;
	int		flag_line;
	char	*find_line;

	i = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	flag_line = 0;
	if (buf[i] == '\n')
		flag_line = 1;
	find_line = ft_calloc(i + flag_line + 1, 1);
	if (find_line == NULL)
		return (-1);
	j = 0;
	while (j < i + flag_line)
	{
		find_line[j] = buf[j];
		j++;
	}
	*line = ft_strjoin(*line, find_line);
	free(find_line);
	if (*line == NULL)
		return (-1);
	return (0);
}


static char	*free_line(char **line)
{
	if (*line != NULL)
		free(*line);
	return (NULL);
}

char	*get_next_line( int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*line;
	int			count_byte;
	int			flag_line;

	line = NULL;
	flag_line = 0;
	if (read(fd, NULL, 0) < 0)
		return (NULL);
	while (flag_line == 0)
	{
		flag_line = ft_find_line(buf, &line);
		if (flag_line == -1)
			return (free_line(&line));
		if (flag_line == 0)
		{
			count_byte = read(fd, buf, BUFFER_SIZE);
			if (count_byte == 0 && *line)
				flag_line = 1;
			else if (count_byte <= 0)
				return (free_line(&line));
			buf[count_byte] = '\0';
		}
	}
	return (line);
}

int main(void)
{
	int fd;
	fd = open("file.txt", O_RDONLY);
	printf("%s", get_next_line(fd));
	close(fd);

	
	// int fd;
	// char *line;
	// int i;

	// fd = open("file.txt", O_RDONLY);
	// if (fd == -1)
	// {
	// 	perror("Error opening file");
	// 	return (1);
	// }
	// i = 1;
	// while (i < 7)
	// {
	// 	line = get_next_line(fd);
	// 	if (!line)
	// 	{
	// 		printf("Error reading line %d\n", i);
	// 		break ;
	// 	}
	// 	printf("line [%02d]: %s", i, line);
	// 	free(line);
	// 	i++;
	// }
	// close(fd);
	// return (0);
}
