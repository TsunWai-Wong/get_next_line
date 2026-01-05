/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tswong <tswong@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:18:46 by tswong            #+#    #+#             */
/*   Updated: 2025/12/15 17:57:20 by tswong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
// For development
#include <stdio.h>

char *read_buffer_line(int fd, char *buffer_line, char *chars_left)
{
	int			buffer_size = 4;

	while (1)
	{
		if (read(fd, buffer_line, buffer_size) == 0)
			return ("");
		buffer_line[4] = '\0';
		// printf("buffer_line: %s\n", buffer_line);
		if (!chars_left)
			chars_left = ft_strdup("");
		// printf("chars_left before: %s\n", chars_left);
		chars_left = ft_strjoin(chars_left, buffer_line);
		// printf("chars_left after: %s\n", chars_left);
		if (ft_strrchr(buffer_line, '\n'))
			break ;
	}
	return (chars_left);
}


char *prepare_next_line(char *line)
{
	int		i;
	char	*chars_remain;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	chars_remain = ft_substr(line, i + 1, ft_strlen(line) - i - 1);
	// printf("chars_left after substr: %s\n", chars_remain);
	line[i + 1] = '\0';
	// printf("line after preparing: %s\n", line);
	return (chars_remain);
}


char *get_next_line(int fd)
{
	static char	*chars_left;
	char		*buffer_line;
	char		*line;

	int			buffer_size = 4;
	if (fd < 0 || buffer_size <= 0 || read(fd, 0, 0) < 0)
	{
		free(chars_left); // Is this needed?
        free(buffer_line);
        chars_left = NULL;
        buffer_line = NULL;
        return (NULL);
	}
	buffer_line = malloc(buffer_size + 1);
	if (!buffer_line)
		return (NULL);
	line = read_buffer_line(fd, buffer_line, chars_left);
	free(buffer_line);
	buffer_line = NULL;
	// printf("local line: %s\n", line);
	chars_left = prepare_next_line(line);
	return (line);
	

}

int	main()
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
}



/* int open (const char* path, int flags [, int mode ]);
ssize_t read(int fildes, void *buf, size_t nbyte);


O_RDONLY: In read-only mode, open the file.
O_WRONLY: In a write-only mode, open the file
O_RDWR: Open the file in reading and write mode
O_CREAT: This flag is applied to create a file if it doesn’t exist in the specified path or directory
O_EXCL: Prevents the file creation if it already exists in the directory or location. 

Usage:
fd1 = open("tests/test.txt", O_RDONLY);
line = get_next_line(fd1);


chars_left stores the leftover characters that were read from the file but not yet returned as a line
buffer_line: temporary memory storage used to store data while it’s being transferred, processed, or waiting to be used.

### Illustration
Sample File:
line1\nline2\n\0

Variables:
[static variable] char *chars_left
[malloc in get_next_line] char *buffer_line (malloc(buffer_size + 1))
[local variable in get_next_line] char *local_line

Steps:
1. [in fill_buffer_line] Fill the buffer_line with the buffer_size (e.g. 5)
(chars_left may already contain data from a previous call.)
chars_left = ""
buffer_line = "line1"
local_line = ""

2. [in fill_buffer_line] If chars_left is empty, depulicate an empty string to it. Concantente buffer_line to chars_left to it.
chars_left = "line1"
buffer_line = "line1"
local_line = ""

3. [in fill_buffer_line] Repeat steps 1 and 2 until the line contains \n or \0
chars_left = "line1\nline"
buffer_line = "\nline"
local_line = ""

4. [in get_next_line] Return the chars_left, set it to local line, and free buffer_line memory
chars_left = "line1\nline"
buffer_line = ""
local_line = "line1\nline"

5. [in set_line] Set chars_left to a substring which starts from the end of the previous line
chars_left = "line"
buffer_line = ""
local_line = "line1\nline"

6. [in set_line] Get a line from chars_left ending with \n or \0 (by setting \0 at the end of string)
chars_left = "line"
buffer_line = ""
local_line = "line1\n\0"

Functions
1. get_next_line
Input: fd
Output: char *next_line

static int current_position = 0
buffer_line = malloc(BUFFER_SIZE + 1)
[string_left = ??]
local_line = fill_buffer_line(fd, chars_left, buffer_line)
free(buffer_line)
next_line = set_line(buffer_line)
free(buffer_line)
if !local_line return (NULL)
string_left = set_line(local_line)
return local_line


2. fill_buffer_line
(read fd of a certain buffer size, keep doing this and add to chars_left until find \n or \0 inside the new buffer)
Input: int fd, char *chars_left, char *buffer_line
Output:

if fd = -1, there is an error
while (i < buffer_size)
	if (c = \n or \0), break

3. set_line
(read the line which contain \n (but maybe not as the last symbol)))
Input: char *buffer_line
Output: substring of the line
\n: end of line
\0: end of file

*/