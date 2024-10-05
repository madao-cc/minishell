#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <linux/limits.h>
#include <stdbool.h>

#include <dirent.h>  // opendir, readdir, closedir

void	welcome_shell(void);
void	print_terminal_name(void);
void	ft_ls(void);
int	ft_is_blankspace(char c);
void	handle_cd(char *line);
void	handle_absolut_path(char *line);
void	handle_dot_cases(char *line);
void	handle_home(char *line);
void	handle_relative_path(char *line);
void	handle_special_case(char *line);
void	handle_env_var(char *line);
int	ft_is_char(char c);
char	*ft_strdup(char *s);
int	ft_is_path(char c);
char	*ft_strtrim(char const *s1, char const *set);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int	ft_is_in_set(char c, const char *set);
char	*ft_strtrim(const char *s1, const char *set);

int	main(int argc, char **argv)
{
	if (isatty(STDIN_FILENO))
	{
		welcome_shell();
		/*	Make sure the STDs are connected	*/
		printf("isatty(STDIN_FILENO) = %d\n", isatty(STDIN_FILENO));
		printf("isatty(STDOUT_FILENO) = %d\n", isatty(STDOUT_FILENO));
		printf("isatty(STDERR_FILENO) = %d\n", isatty(STDERR_FILENO));
		printf("\n\n");
		while (1)
		{
			print_terminal_name();
			char *line = NULL;
			char *input;
			size_t len = 0;
			getline(&line, &len, stdin);
			if (strcmp(line, "ls\n") == 0)
			{
				ft_ls();
			}
			else if (strcmp(line, "exit\n") == 0)  // Exit the shell
			{
				free(line);
				exit(0);
			}
			else if (strcmp(line, "clear\n") == 0)  // Clear the screen
			{
				printf("\033[2J");  // Clear the screen
				printf("\033[H");  // Move the cursor to the top left corner
			}
			else if (strncmp(line, "cd", 2) == 0)  // Change directory
			{
				handle_cd(line);
			}
			else
				printf("%s", line);
			free(line);
		}
	}
	else
	{
		printf("isatty(STDIN_FILENO) = %d\n", isatty(STDIN_FILENO));
		printf("isatty(STDOUT_FILENO) = %d\n", isatty(STDOUT_FILENO));
		printf("isatty(STDERR_FILENO) = %d\n", isatty(STDERR_FILENO));
	}
}

void	welcome_shell(void)
{
	printf("		\033[1;34m");  // Set color to bright blue
	printf("		\n\n");
	printf("		#########################################\n");
	printf("		#                                       #\n");
	printf("		#   \033[1;32mWelcome to Our Custom MiniShell!\033[1;34m    #\n");  // Bright green
	printf("		#                                       #\n");
	printf("		#   \033[1;31mFeel free to experiment, but...\033[1;34m     #\n");  // Bright red
	printf("		#      \033[1;5;31m**at your own risk!**\033[0m\033[1;34m            #\n");  // Bright red
	printf("		#                                       #\n");
	printf("		#########################################\n\n");
	printf("		\033[0m");  // Reset color to default
	printf("\n");
}

void	print_terminal_name(void)
{
	char cwd[PATH_MAX];

	getcwd(cwd, sizeof(cwd));
	printf("\033[1m\033[32mmy_shell\033[0m:\033[1m\033[33m%s\033[0m$ ", cwd);
}

void	ft_ls(void)
{
	DIR *dir;
	struct dirent *entry;
	bool nothing;

	dir = opendir(".");
	if (!dir)
	{
		perror("Erro ao abrir diretorio");
		exit(1);
	}
	nothing = true;
	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_name[0] != '.')
			printf("\033[34m%s\033[0m\t", entry->d_name);
		nothing = false;
	}
	if (nothing == false)
		printf("\n");
	closedir(dir);
}

int	ft_is_blankspace(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

void	handle_cd(char *line)
{
	int	i;

	i = 2;
	while (line[i])
	{
		if (ft_is_blankspace(line[i]) == 0)
		{
			if (ft_is_char(line[i] == 1))
			{
				handle_relative_path(line + i - 1);
				return ;
			}
			else if (line[i] == '/')
			{
				printf("no4\n");
				handle_absolut_path(line);
			}
			else if (line[i] == '.')
			{
				printf("no2\n");
				handle_dot_cases(line);
			}
			else if (line[i] == '\n' || line[i] == '~')
			{
				handle_home(line);
				return ;
			}
			else if (line[i] == '-')
			{
				printf("no\n");
				handle_special_case(line);
			}
			else if (line[i] == '$')
			{
				printf("no1\n");
				handle_env_var(line);
			}
		}
		i++;
	}
}

void	handle_absolut_path(char *line)
{
	int	i;
	char	*path;

	i = 2;
	while (line[i])
	{
		if (ft_is_blankspace(line[i]) == 0)
		{
			path = ft_strdup(&line[i]);
			break ;
		}
		i++;
	}
	chdir(path);
}

void	handle_dot_cases(char *line)
{
	int	i;

	i = 2;
	while (line[i])
	{
		if (ft_is_blankspace(line[i]) == 0)
		{
			if (line[i] == '.')
			{
				if (line[i + 1] == '/')
				{
					chdir(".");
				}
				else if (line[i + 1] == '.' && line[i + 2] == '/')
				{
					chdir("..");
				}
			}
		}
		i++;
	}
}

void	handle_home(char *line)
{
	char *home = getenv("HOME");
	if (home != NULL)
	{
		chdir(home);
	}
	else
	{
		fprintf(stderr, "Error: HOME environment variable not set.\n");
	}
}
void	handle_relative_path(char *line)
{
	int		i;
	char		*path;
	char		*trimmed_path;

	i = 0;
	printf("line[i] = %c\n", line[i]);
	printf("line = %s\n", line);
	while (line[i] && ft_is_blankspace(line[i]))
		i++;
	printf("line[i] = %c\n", line[i]);
	path = ft_strdup(&line[i]);
	printf("path = %s\n", path);
	trimmed_path = ft_strtrim(path, " \t\n");
	printf("trimmed_path = %s\n", trimmed_path);
	free(path);
	if (trimmed_path)
	{
		if (chdir(trimmed_path) == -1)
			perror("chdir error");
		free(trimmed_path);
	}
	else
	{
		printf("Error: Invalid path.\n");
	}
}

void	handle_special_case(char *line)
{
	int	i;

	i = 2;
	while (line[i])
	{
		if (ft_is_blankspace(line[i]) == 0)
		{
			if (line[i] == '-')
			{
				chdir("-");
			}
		}
		i++;
	}
}

void	handle_env_var(char *line)
{
	int	i;
	char	*path;

	i = 2;
	while (line[i])
	{
		if (ft_is_blankspace(line[i]) == 0)
		{
			path = ft_strdup(&line[i]);
			break ;
		}
		i++;
	}
	chdir(path);
}

int	ft_is_char(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

char	*ft_strdup(char *s)
{
	char	*str;
	int	i;

	i = 0;
	while (s[i])
		i++;
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	ft_is_path(char c)
{
	if (ft_is_char(c) == 1)
		return (1);
	if (c == '/' || c == '.' || c == '~' || c == '-')
		return (1);
	return (0);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	substr = (char *)malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

int	ft_is_in_set(char c, const char *set)
{
	int i = 0;

	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	int		start;
	int		end;
	char	*trimmed_str;
	int		i;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && ft_is_in_set(s1[start], set))
		start++;
	end = strlen(s1) - 1;
	while (end >= start && ft_is_in_set(s1[end], set))
		end--;
	trimmed_str = (char *)malloc(sizeof(char) * (end - start + 2));
	if (!trimmed_str)
		return (NULL);
	i = 0;
	while (start <= end)
		trimmed_str[i++] = s1[start++];
	trimmed_str[i] = '\0';

	return (trimmed_str);
}