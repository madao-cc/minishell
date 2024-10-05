#include "sh.h"

int	main(void)
{
	if (isatty(STDIN_FILENO))
	{
		welcome_shell();
		setup_signals();
		/*	Make sure the STDs are connected	*/
		printf("isatty(STDIN_FILENO) = %d\n", isatty(STDIN_FILENO));
		printf("isatty(STDOUT_FILENO) = %d\n", isatty(STDOUT_FILENO));
		printf("isatty(STDERR_FILENO) = %d\n", isatty(STDERR_FILENO));
		printf("\n\n");
		while (1)
		{
			print_terminal_name();
			size_t len = 0;
			char *line = NULL;  // readline("");
 			getline(&line, &len, stdin);
			/* if (line == NULL)
			{
        			break; // EOF (Ctrl+D)
        		} */
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
			else if (strcmp(line, "pwd\n") == 0)
			{
				handle_pwd();
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

void	handle_home(void)
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

int	ft_is_blankspace(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
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
};

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

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return *(unsigned char *)s1 - *(unsigned char *)s2;
}

int	ft_is_char(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	handle_dot_cases(char *line)
{
	int	i;
	char *path;

	i = 0;
	path = ft_strtrim(line, " /t/n");
	printf("%s", path);
	while (path[i])
	{
		while (path[i] == '.' || path[i] == '/')
		{
			if (path[i] == '.' && path[i] == 1)
			{
				chdir("");
			}
		}
		if (strcmp(path, "..") == 0)
		{
			chdir("..");
		}
		if (strcmp(path, ".") == 0)
		{
			chdir(".");
		}
	}
}

/*while (path[i])
{
	if (path[i] == '.' && path[i + 1] == '.')
	{
		if (path[i + 1] == '.' && path[i + 2] == '/')
		{
			chdir ("..");
			while (path[i] == '/')
				i++;
		}
		else if (path[i + 1] == '.' && path[i + 2] == '\0')
		{
			chdir("..");
			break ;
		}
	}
	else f (path[i] == '.' && path[i + 1] == '/')
	{

	}
	
}*/

void	handle_cd(char *line)
{
	char *path;
	char *trimmed_path;
	int	i;

	i = 2;
	path = ft_strdup(&line[i]);
	trimmed_path = ft_strtrim(path, " \n\t");
	i = 0;
	if (strlen(trimmed_path) == 0 || ft_strcmp(ft_strtrim(trimmed_path, " \t"), "\n") == 0)
	{
			handle_home();
			free(path);
			return ;
	}
	while (trimmed_path[i])
	{
		
		if (trimmed_path[i] == '/')
		{
			handle_absolut_path(trimmed_path);
			free(path);
			return ;
		}
		if ((ft_is_char(trimmed_path[i]) == 1) || (trimmed_path[i] == '/' || trimmed_path[i] == '~'))
		{
			handle_relative_path(trimmed_path);
			free(path);
			return ;
		}
		if (trimmed_path[i] == '.')
		{
			handle_relative_path(trimmed_path);
			free(path);
			return ;
		}
		i++;
	}
}

void	handle_relative_path(char *line)
{
	char *path;

	path = strsep(&line, "/");
	while (path != NULL)
	{
		if (ft_strcmp(path, "~") == 0)
		{
			handle_home();
		}
		else if (ft_strcmp(path, ".") == 0)
		{
			chdir(".");
		}
		else if (ft_strcmp(path, "..") == 0)
		{
			chdir("..");
		}
		else
			chdir(path);
		path = strsep(&line, "/");
	}
}

void	handle_absolut_path(char *line)
{
	if (chdir(line) == -1)
	{
		perror("chdir error");
	}
}

void handle_pwd(void)
{
    char cwd[PATH_MAX];

    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    } else {
        perror("pwd");
    }
}
