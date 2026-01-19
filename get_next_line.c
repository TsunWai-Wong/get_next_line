/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tswong <tswong@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:18:46 by tswong            #+#    #+#             */
/*   Updated: 2026/01/19 18:26:39 by tswong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
// For development
#include <stdio.h>



// if there is problem in the file or there is nothing left to read
static void	read_buffer_line(int fd, char *buffer_line, char **chars_left)
{
	int		byte_read;
	char	*current_chars_left;

	byte_read = 1;
	while (byte_read > 0 && *chars_left && !ft_strchr(*chars_left, '\n'))
	{
		byte_read = read(fd, buffer_line, BUFFER_SIZE);
		if (byte_read < 0)
		{
			free(*chars_left);
			*chars_left = NULL;
			return ;
		}
		if (byte_read == 0)
			return ;
		buffer_line[byte_read] = '\0';
		current_chars_left = *chars_left;
		*chars_left = ft_strjoin(current_chars_left, buffer_line);
		free(current_chars_left);
		current_chars_left = NULL;
		if (!*chars_left)
			return ;
	}
}

// Handle the remaining text without \n at the end
static char	*extract_next_line(char **text)
{
	int		i;
	char	*line;
	char	*chars_remain;

	if (!ft_strchr(*text, '\n'))
	{
		line = ft_strdup(*text);
		free(*text);
		*text = NULL;
		return (line);
	}
	i = 0;
	while ((*text)[i] && (*text)[i] != '\n')
		i++;
	line = ft_substr(*text, 0, i + 1);
	if (!line)
	{
		free(*text);
		*text = NULL;
		return (NULL);
	}
	chars_remain = ft_strdup(*text + i + 1);
	free(*text);
	*text = chars_remain;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*chars_left;
	char		*buffer_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!chars_left)
		chars_left = ft_strdup("");
	buffer_line = malloc(BUFFER_SIZE + 1);
	if (!buffer_line)
	{
		free(chars_left);
		chars_left = NULL; 
		return (NULL);
	}
	read_buffer_line(fd, buffer_line, &chars_left);
	free(buffer_line);
	if (!chars_left || chars_left[0] == '\0')
	{
		free(chars_left);
		chars_left = NULL;
		return (NULL);
	}
	return (extract_next_line(&chars_left));
}

/* int	main()
{
	int	fd = open("text.txt", O_RDONLY);
	printf("Line 1: %s", get_next_line(fd));
	printf("Line 2: %s", get_next_line(fd));
	printf("Line 3: %s", get_next_line(fd));
	printf("Line 4: %s", get_next_line(fd));
	printf("Line 5: %s", get_next_line(fd));
	printf("Line 6: %s", get_next_line(fd));
	printf("Line 7: %s", get_next_line(fd));
	printf("Line 8: %s", get_next_line(fd));
	printf("Line 9: %s", get_next_line(fd));
	printf("Line 10: %s", get_next_line(fd));
	printf("Line 11: %s", get_next_line(fd));
	printf("Line 12: %s", get_next_line(fd));
	printf("Line 13: %s", get_next_line(fd));
	printf("Line 14: %s", get_next_line(fd));
	printf("Line 15: %s", get_next_line(fd));
	return (0);
} */