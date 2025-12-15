#include "get_next_line.h"

int	main()
{
	#include <stdio.h>
	int	fd = open("try.txt", O_RDONLY);
	printf("fd: %d\n", fd);
	char buffer[1024];
	int res = read(fd, buffer, 10);
	buffer[10] = '\0';
	printf("res: %d\n", res);
	printf("string: %s\n", buffer);
	return (0);
}