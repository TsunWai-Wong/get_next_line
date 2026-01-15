/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tswong <tswong@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:50:20 by tswong            #+#    #+#             */
/*   Updated: 2026/01/15 14:50:23 by tswong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strdup(const char *s)
{
	int		i;
	int		str_len;
	char	*dest;

	i = 0;
	str_len = ft_strlen(s);
	dest = malloc((str_len + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	while (i < str_len)
	{
		dest[i] = s[i];
		i++;
	}
	dest[str_len] = '\0';
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	char	*result;

	result = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (*s1)
	{
		result[i] = *s1;
		s1++;
		i++; 
	}
	while (*s2)
	{
		result[i] = *s2;
		s2++;
		i++; 
	}
	result[i] = '\0';
	return (result);
}

char	*ft_strrchr(const char *s, int c)
{
	size_t			i;
	unsigned char	uc;

	uc = (unsigned char) c;
	i = ft_strlen(s);
	while (i > 0)
	{
		if (s[i] == uc)
			return ((char *) &s[i]);
		i--;
	}
	if (s[i] == uc)
		return ((char *) &s[i]);
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*result;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if ((start + len) > ft_strlen(s))
		len = ft_strlen(s) - start;
	result = malloc(sizeof(char) * (len + 1));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		result[i] = s[start + i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
