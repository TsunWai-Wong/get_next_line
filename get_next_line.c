/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tswong <tswong@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:18:46 by tswong            #+#    #+#             */
/*   Updated: 2026/01/15 14:51:16 by tswong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
// For development
#include <stdio.h>

char	*read_buffer_line(int fd, char *buffer_line, char *chars_left)
{
	int	byte_read;

	while (1)
	{
		byte_read = read(fd, buffer_line, BUFFER_SIZE);
		printf("byte_read: %d\n", byte_read);
		printf("chars_left: %s\n", chars_left);
		if (byte_read <= 0)
			return (chars_left);
		buffer_line[byte_read] = '\0';
		if (!chars_left)
			chars_left = ft_strdup("");
		chars_left = ft_strjoin(chars_left, buffer_line);
		if (ft_strrchr(buffer_line, '\n'))
			break ;
	}
	return (chars_left);
}

char	*prepare_next_line(char *line)
{
	int		i;
	char	*chars_remain;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	chars_remain = ft_substr(line, i + 1, ft_strlen(line) - i - 1);
	line[i + 1] = '\0';
	return (chars_remain);
}

char	*get_next_line(int fd)
{
	static char	*chars_left;
	char		*buffer_line;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer_line = malloc(BUFFER_SIZE + 1);
	if (!buffer_line)
		return (NULL);
	line = read_buffer_line(fd, buffer_line, chars_left);
	free(buffer_line);
	buffer_line = NULL;
	chars_left = prepare_next_line(line);
	return (line);
}

/* int	main()
{
	int	fd = open("README.md", O_RDONLY);
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