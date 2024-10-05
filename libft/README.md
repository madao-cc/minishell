# Libft - @42Born2Code
My first project in the 42 main core.

### TOC
* [What is libft?](#what-is-libft)
* [What's in it?](#whats-in-it)
* [Functions - Explanations](#Libft-Functions)

### What is libft?
Libft is an individual project at 42 that requires us to re-create some standard C library functions that can be used later to build a library of useful functions for the rest of the program.

Disclaimer: *Reinventing the wheel is bad, 42 makes us do this just so we can have a deeper understanding of data structures and basic algorithms. At 42 we're not allowed to use some standard libraries on our projects, so we have to keep growing this library with our own functions as we go farther in the program.*

### What's in it?

As you can see from the [Project instructions][1], there are 4 sections:

1.  **Libc Functions:** Some of the standard C functions
2.  **Additional functions:** Functions 42 deems will be useful for later projects
3.  **Bonus Functions:** Functions 42 deems will be useful for linked list manipulation

Libc functions | Additional functions | Bonus Functions
:----------- | :-----------: | :-----------:
memset		| ft_memalloc	| ft_lstnew		
bzero		| ft_memdel		| ft_lstdelone	 
memcpy		| ft_strnew		| ft_lstdel		    
memccpy		| ft_strdel		| ft_lstadd		    
memmove		| ft_strclr		| ft_lstiter	    
memchr		| ft_striter	| ft_lstmap		
memcmp		| ft_striteri	|				
strlen		| ft_strmap		|				
strdup		| ft_strmapi	|				
strcpy		| ft_strequ		|				
strncpy		| ft_strnequ	|			
strcat		| ft_strsub		| 
strlcat		| ft_strjoin	| 
strchr		| ft_strtrim	| 
strrchr		| ft_strsplit	| 
strstr		| ft_itoa		| | 
strnstr		| ft_putchar	| 
strcmp		| ft_putstr		| 
strncmp		| ft_putendl	| 
atoi		| ft_putnbr		| | 
isalpha		| ft_putchar_fd	| |
isdigit		| ft_putstr_fd	| | 
isalnum		| ft_putendl_fd	| | 
isascii		| ft_putnbr_fd	| | 
isprint		|| 
tolower		| |

# Libft Functions

### Functions from `<ctype.h>`

- [`ft_isalpha`](ft_isalpha.c)	- checks  for  an  alphabetic  character.
- [`ft_isdigit`](ft_isdigit.c)	- checks for a digit (0 through 9).
- [`ft_isalnum`](ft_isalnum.c)	- checks for an alphanumeric character.
- [`ft_isascii`](ft_isascii.c)	- checks whether c fits into the ASCII character set.
- [`ft_isprint`](ft_isprint.c)	- checks for any printable character.
- [`ft_toupper`](ft_toupper.c)	- convert char to uppercase.
- [`ft_tolower`](ft_tolower.c)	- convert char to lowercase.

### Functions from `<string.h>`

- [`ft_memset`](ft_memset.c)	- fill memory with a constant byte.
- [`ft_strlen`](ft_strlen.c)	- calculate the length of a string.
- [`ft_bzero`](ft_bzero.c)	- zero a byte string.
- [`ft_memcpy`](ft_memcpy.c)	- copy memory area.
- [`ft_memmove`](ft_memmove.c)	- copy memory area.
- [`ft_strlcpy`](ft_strlcpy.c)	- copy string to an specific size.
- [`ft_strlcat`](ft_strlcat.c)	- concatenate string to an specific size.
- [`ft_strchr`](ft_strchr.c)	- locate character in string.
- [`ft_strrchr`](ft_strrchr.c)	- locate character in string.
- [`ft_strncmp`](ft_strncmp.c)	- compare two strings.
- [`ft_memchr`](ft_memchr.c)	- scan memory for a character.
- [`ft_memcmp`](ft_memcmp.c)	- compare memory areas.
- [`ft_strnstr`](ft_strnstr.c)	- locate a substring in a string.
- [`ft_strdup`](ft_strdup.c)	- creates a dupplicate for the string passed as parameter.

### Functions from `<stdlib.h>`
- [`ft_atoi`](ft_atoi.c)	- convert a string to an integer.
- [`ft_calloc`](ft_calloc.c)	- allocates memory and sets its bytes' values to 0.

### Non-standard functions
- [`ft_substr`](ft_substr.c)	- returns a substring from a string.
- [`ft_strjoin`](ft_strjoin.c)	- concatenates two strings.
- [`ft_strtrim`](ft_strtrim.c)	- trims the beginning and end of string with specific set of chars.
- [`ft_split`](ft_split.c)	- splits a string using a char as parameter.
- [`ft_itoa`](ft_itoa.c)	- converts a number into a string.
- [`ft_strmapi`](ft_strmapi.c)	- applies a function to each character of a string.
- [`ft_striteri`](ft_striteri.c)	- applies a function to each character of a string.
- [`ft_putchar_fd`](ft_putchar_fd.c)	- output a char to a file descriptor.
- [`ft_putstr_fd`](ft_putstr_fd.c)	- output a string to a file descriptor.
- [`ft_putendl_fd`](ft_putendl_fd.c)	- output a string to a file descriptor, followed by a new line.
- [`ft_putnbr_fd`](ft_putnbr_fd.c)	- output a number to a file descriptor.

### Linked list functions

- [`ft_lstnew`](ft_lstnew.c)	- creates a new list element.
- [`ft_lstadd_front`](ft_lstadd_front.c)	- adds an element at the beginning of a list.
- [`ft_lstsize`](ft_lstsize.c)	- counts the number of elements in a list.
- [`ft_lstlast`](ft_lstlast.c)	- returns the last element of the list.
- [`ft_lstadd_back`](ft_lstadd_back.c)	- adds an element at the end of a list.
- [`ft_lstclear`](ft_lstclear.c)	- deletes and free list.
- [`ft_lstiter`](ft_lstiter.c)	- applies a function to each element of a list.
- [`ft_lstmap`](ft_lstmap.c)	- applies a function to each element of a list.



