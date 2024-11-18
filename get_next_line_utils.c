/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-you <mait-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 08:12:56 by mait-you          #+#    #+#             */
/*   Updated: 2024/11/18 15:33:13 by mait-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	l;

	if (!s)
		return (0);
	l = 0;
	while (*(s++))
		l++;
	return (l);
}

void *ft_calloc(size_t count, size_t size)
{
	unsigned char	*byte_ptr;
	void			*ptr;

	if (size != 0 && count > SIZE_MAX / size)
		return (NULL);
	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	byte_ptr = (unsigned char *)ptr;
	while (count > 0)
	{
		*(byte_ptr++) = 0;
		count--;
	}
	return (ptr);
}

char	*ft_strdup(const char *s1)
{
	char	*str;
	size_t	s1_len;
	char	*ptr;

	if (!s1)
		return (NULL);
	s1_len = ft_strlen(s1);
	str = (char *)ft_calloc(s1_len + 1, sizeof(char));
	if (!str)
		return (NULL);
	ptr = str;
	while (*s1)
	{
		*ptr = *s1;
		ptr++;
		s1++;
	}
	*ptr = 0;
	return (str);
}

// KO = calloc
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	s_len;
	size_t	substr_len;
	size_t	i;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start > s_len)
		return (ft_strdup(""));
	if (len > (s_len - start))
		substr_len = (s_len - start) + 1;
	else
		substr_len = len + 1;
	substr = (char *)ft_calloc(substr_len, sizeof(char));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len && s[start + i] != '\0')
	{
		substr[i] = s[start + i];
		i++;
	}
	// substr[i] = '\0';
	return (substr);
}

char	*ft_strchr(const char *s, int c)
{
	char	cc;

	cc = (char)c;
	while (s && *s)
	{
		if (*s == cc)
			return ((char *)(s));
		s++;
	}
	return (NULL);
}
// Timeout = ft_calloc & malloc
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	ptr = (char *)calloc((ft_strlen(s1) + ft_strlen(s2) + 1), sizeof(char));
	if (!ptr)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		ptr[j++] = s1[i++];
	i = 0;
	while (s2[i])
		ptr[j++] = s2[i++];
	// ptr[j] = '\0';
	return (ptr);
}
