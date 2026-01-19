_This project has been created as part of the 42 curriculum by tswong_

### Description
The aim of this project is to make a function that returns a line by reading from a file descriptor.

The function uses functions including read, malloc, and free. It is able to handles files and standard input. It can manage newlines, errors, and end-of-file correctly and efficiently.

### Instructions

1. Include the header in your file
```
#include "get_next_line.h"
```

2. when compiling your code, add the source files and the required flag. There is only one optional flag called BUFFER_SIZE to control the buffer size to read each time.
```
cc main.c get_next_line.c get_next_line_utils.c -D BUFFER_SIZE=<size>
```

### Resources

A tutorial session: https://medium.com/@lannur-s/gnl-c3cff1ee552b
Reading file in C: https://www.educative.io/answers/read-data-from-a-file-using-read-in-c
Macros and its types in C: https://www.geeksforgeeks.org/c/macros-and-its-types-in-c-cpp/

AI was used for me to clarify some concepts including Macro in C, memory management, different flags for opening files, and etc.

### Detailed Explanation

##### Detailed explanation and justification of the algorithm

1. Keep reading the file with a certain buffer size. After each time of read, fill the text we just read to chars_left. The reading process stops when we encounter a '\n' character inside chars_left.

2. Extract the line (which ends with a '\n' character) from chars_left. Then we update chars_left as the remaining text. 

3. When the user wants to get the 2nd line and so on, if there is still '\n' character in the chars_left. Otherwise, we will repeat everthing from step 1.

##### Variables
- chars_left: stores the leftover characters that were read from the file but not yet returned as a line
- buffer_line: temporary memory storage used to store data while it’s being transferred, processed, or waiting to be used.

##### Sample Steps
sample_file.txt:
line1\nline2\n\0

Variables:
- char *chars_left: static variable across all functions
- char *buffer_line: local variable (malloc) in get_next_line
- char *line: local variable in extract_next_line

Steps:
1. [in fill_buffer_line] Fill the buffer_line with the buffer_size (e.g. 5)
(chars_left may already contain data from a previous call.)
chars_left = ""
buffer_line = "line1"
line = ""

2. [in fill_buffer_line] If chars_left is empty, depulicate an empty string to it. Concantente buffer_line to chars_left to it.
chars_left = "line1"
buffer_line = "line1"
line = ""

3. [in fill_buffer_line] Repeat steps 1 and 2 until the line contains \n or \0
chars_left = "line1\nline"
buffer_line = "\nline"
line = ""

4. [in get_next_line] Update the chars_left and free buffer_line memory
chars_left = "line1\nline"
buffer_line = ""
line = ""

5. [in extract_next_line] Return the extracted next line, and set chars_left to the remaining characters
chars_left = "line"
buffer_line = ""
line = "line1\n"

6. If chars_left still contains one or more '\n' character, repeat from step 5. Otherwise, repeat from step 1.

##### Other Concepts

Dangling pointer
A dangling pointer pointed to memory that does not exist. For example, after the pointer is freed.
To solve it, we have to set the variable to NULL after freeing it. For example:
```
free(*chars_left);
*chars_left = NULL;
```

Flags for opening files
O_RDONLY: In read-only mode, open the file.
O_WRONLY: In a write-only mode, open the file
O_RDWR: Open the file in reading and write mode
O_CREAT: This flag is applied to create a file if it doesn’t exist in the specified path or directory
O_EXCL: Prevents the file creation if it already exists in the directory or location. 
