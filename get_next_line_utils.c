/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogoman <ogoman@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 07:31:16 by ogoman            #+#    #+#             */
/*   Updated: 2023/11/28 15:30:21 by ogoman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Looks for a newline character in buffer starting from start_index.
// Returns the index of the character folowing the newline.
// Returns 0 is no newline was found.
ssize_t	find_newline(char *buf, ssize_t start_index)
{
	while (buf[start_index])
	{
		if (buf[start_index] == '\n')
			return (start_index + 1);
		start_index++;
	}
	return (0);
}

// Returns the length of the string s
ssize_t	ft_strlen(const char *s)
{
	ssize_t	res;

	res = 0;
	while (s[res])
		res++;
	return (res);
}

// Initialises res as an empty string.
// In case of success returns 1.
// In case of error (malloc fail) returns 0.
int	init_res(char **res)
{
	*res = (char *)malloc(sizeof(char) * 1);
	if (!*res)
		return (0);
	(*res)[0] = '\0';
	return (1);
}

// size_t	ft_strlen(const char *str)
// {
// 	size_t	i;

// 	i = 0;
// 	while (str[i])
// 		i++;
// 	return (i);
// }

// char	*ft_strcpy(char *dest, char *src)
// {
// 	int	i;

// 	i = 0;
// 	while (src[i])
// 	{
// 		dest[i] = src[i];
// 		i++;
// 	}
// 	dest[i] = src[i];
// 	return (dest);
// }

// char	*ft_strcat(char *dest, char *src)
// {
// 	int	i;
// 	int	j;

// 	i = ft_strlen(dest);
// 	j = 0;
// 	while (src[j])
// 	{
// 		dest[i + j] = src[j];
// 		j++;
// 	}
// 	dest[i + j] = '\0';
// 	return (dest);
// }

// char	*ft_strjoin(char *s1, char *s2)
// {
// 	char	*res;

// 	if (!s1)
// 	{
// 		s1 = (char *)malloc(sizeof(char) * 1);
// 		s1[0] = '\0';
// 	}
// 	if (!s1 || !s2)
// 		return (NULL);
// 	res = (char *)malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 1);
// 	if (res == NULL)
// 		return (NULL);
// 	ft_strcpy(res, s1);
// 	ft_strcat(res, s2);
// 	free(s1);
// 	return (res);
// }

// char	*ft_strchr(const char *s, int c)
// {
// 	unsigned int	i;
// 	char			*str;

// 	i = 0;
// 	str = (char *)s;
// 	if (!s)
// 		return (0);
// 	while (str[i])
// 	{
// 		if (str[i] == (char)c)
// 			return (&str[i]);
// 		i++;
// 	}
// 	return (0);
// }

/////////////////////////////////////

// char	*join_str(void *dest, void const *source, size_t dest_l, size_t src_l)
// {
// 	char	*res_str;

// 	res_str = (char *)malloc((dest_l + src_l + 1) * sizeof(char));
// 	if (res_str != NULL)
// 	{
// 		custom_memcpy(res_str, dest, dest_l);
// 		custom_memcpy(res_str + dest_l, source, src_l);
// 		res_str[dest_l + src_l] = '\0';
// 	}
// 	free(dest);
// 	return (res_str);
// }

// void	*custom_memchr(const void *buffer, void *start, int targ, size_t size)
// {
// 	size_t	index;

// 	index = 0;
// 	while (index < size)
// 	{
// 		if (((unsigned char *)buffer)[index] == (unsigned char)targ)
// 			return ((void *)buffer + index);
// 		index++;
// 	}
// 	return (start);
// }

// void	*custom_memcpy(void *destination, const void *source, size_t num_bytes)
// {
// 	size_t	index;

// 	index = 0;
// 	if (destination == NULL && source == NULL)
// 		return (NULL);
// 	while (index < num_bytes)
// 	{
// 		((char *)destination)[index] = ((char *)source)[index];
// 		index++;
// 	}
// 	return (destination);
// }
/////////////////////////////////////////////////

// char	*ft_strjoin(char *s1, char *s2)
// {
// 	char	*new;
// 	size_t	i;

// 	if (!s1 || !s2)
// 		return (NULL);
// 	new = (char *)ft_calloc(sizeof(char), (ft_strlen(s1) + ft_strlen(s2) + 1));
// 	if (!new)
// 		return (NULL);
// 	i = 0;
// 	while (*s1)
// 	{
// 		new[i] = *s1;
// 		i++;
// 		s1++;
// 	}
// 	while (*s2)
// 	{
// 		new[i] = *s2;
// 		i++;
// 		s2++;
// 	}
// 	new[i] = '\0';
// 	return (new);
// }

// size_t	ft_strlen(const char *s)
// {
// 	size_t	length;

// 	length = 0;
// 	while (s[length] != '\0')
// 	{
// 		length++;
// 	}
// 	return (length);
// }

// void	*ft_calloc(size_t count, size_t size)
// {
// 	size_t			total_size;
// 	size_t			i;
// 	void			*ptr;
// 	unsigned char	*byte_ptr;

// 	total_size = count * size;
// 	ptr = malloc(total_size);
// 	if (!ptr)
// 		return (NULL);
// 	byte_ptr = (unsigned char *)ptr;
// 	i = 0;
// 	while (i < total_size)
// 	{
// 		byte_ptr[i] = 0;
// 		i++;
// 	}
// 	return (ptr);
// }

///////////

// size_t	ft_strlen(const char *s)
// {
// 	size_t	length;

// 	length = 0;
// 	while (*s)
// 	{
// 		s++;
// 		length++;
// 	}
// 	return (length);
// }

// void	*ft_memset(void *b, int c, size_t len)
// {
// 	unsigned char	*val;
// 	int				i;

// 	i = 0;
// 	val = (unsigned char *)b;
// 	while (len > 0)
// 	{
// 		val[i++] = (unsigned char)c;
// 		len--;
// 	}
// 	return (b);
// }

// void	*ft_calloc(size_t count, size_t size)
// {
// 	void	*mem;
// 	int		i;

// 	i = 0;
// 	mem = malloc(count * size);
// 	if (mem == NULL)
// 		return (NULL);
// 	ft_memset(mem, '\0', (count * size));
// 	return (mem);
// }

// char	*ft_strjoin(char *s1, char *s2)
// {
// 	char	*new;
// 	size_t	i;

// 	if (!s1 || !s2)
// 		return (NULL);
// 	new = (char *)ft_calloc(sizeof(char), (ft_strlen (s1) + ft_strlen(s2) + 1));
// 	if (!new)
// 		return (NULL);
// 	i = 0;
// 	while (*s1)
// 	{
// 		new[i] = *s1;
// 		i++;
// 		s1++;
// 	}
// 	while (*s2)
// 	{
// 		new[i] = *s2;
// 		i++;
// 		s2++;
// 	}
// 	new[i] = '\0';
// 	return (new);
// }
