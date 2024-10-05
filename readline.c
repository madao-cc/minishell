#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <linux/limits.h>
#include <stdbool.h>
#include <signal.h>  // sigaction
#include <sys/types.h>  // pid_t
#include <sys/wait.h>  // waitpid
#include <sys/stat.h>  // stat
#include <readline/readline.h>  // readline and add_history
#include <readline/history.h>  // add_history
#include <dirent.h>  // opendir, readdir, closedir
#include <fcntl.h>

char	*ft_trim(char *str);
char	*ft_prepare_prompt(void);
void	handle_cd(char *line);
void	handle_absolut_path(char *line);
void	handle_home(void);
int	ft_is_char(char c);
int	ft_is_in_set(char c, const char *set);
char	*ft_strtrim(const char *s1, const char *set);
int	ft_strcmp(const char *s1, const char *s2);
void	handle_dot_cases(char *line);
void	handle_relative_path(char *line);
char	*ft_strdup(char *s);
void	setup_signals(void);
void	handle_sigint(int sig);

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

char	*ft_trim(char *str)
{
	char	*start;
	char	*end;
	char	*trimmed;
	size_t	len;

	start = str;
	while (*start == ' ' || *start == '\t')
		start++;
	end = start;
	while (*end)
		end++;
	while (end > start && (*(end - 1) == ' ' || *(end - 1) == '\t'))
		end--;
	len = end - start;
	trimmed = malloc(len + 1);
	if (trimmed == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	memcpy(trimmed, start, len);
	trimmed[len] = '\0';
	free(str);
	return (trimmed);
}

char	*ft_prepare_prompt(void)
{
	char	cwd[PATH_MAX];
	char	*prompt;
	char	*color_prefix = "\033[1;35m";
	char	*color_cwd = "\033[1;36m";
	char	*color_reset = "\033[0m";
	size_t	len;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd");
		exit(EXIT_FAILURE);
	}
	len = strlen(color_prefix) + strlen(cwd) + strlen(color_cwd) + strlen("minishel-") + strlen(color_reset) + strlen("> ") + 1;
	prompt = malloc(len);
	if (prompt == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	strcpy(prompt, color_prefix);
	strcat(prompt, "minishel\033[0m-");
	strcat(prompt, color_cwd);
	strcat(prompt, cwd);
	strcat(prompt, color_reset);
	strcat(prompt, "> ");
	return (prompt);
}

void	handle_cd(char *line)  //TODO: Falta caso de environment variable
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
		if (trimmed_path[i] == '~')
		{
			if (strcmp(trimmed_path, "~") == 0)
			{
				handle_home();
				free(path);
				return ;
			}
		}
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

void	handle_absolut_path(char *line)
{
	if (chdir(line) == -1)
	{
		perror("chdir error");
	}
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

int	ft_is_char(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
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

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return *(unsigned char *)s1 - *(unsigned char *)s2;
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

void	setup_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	//signal(EOF, handle_sigkill);
}

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/* void	handle_echo(char *line)
{
	int	i = 0;
	char *trimmed_line;
	char *phrase;

	trimmed_line = ft_strtrim(line, " ");
	if (strncmp(trimmed_line, "echo -n", 7) == 0)
	{
		handle_echo_n(line + 7);
		return;
	}
	else
	{
		phrase = line + 4;

	}
} */

int	main(void)
{
	char cwd[PATH_MAX];
	char *prompt;
	char *input;
	char *prefix = "minishel-";
	char *suffix = "> ";
	size_t	len;

	if (isatty(STDIN_FILENO))
	{
		setup_signals();
		while (1)
		{
			if (getcwd(cwd, sizeof(cwd)) == NULL)
			{
				perror("getcwd");
				exit(EXIT_FAILURE);
			}
			len = strlen(cwd) + strlen(prefix) + strlen(suffix) + 1;
			prompt = ft_prepare_prompt();
			input = readline(prompt);
			if (input == NULL)
			{
				write(1, "\033[1;31mExiting...\n\033[0m", 23);
				free(prompt);
				free(input);
				break ;
			}
			input = ft_trim(input);
			if (strncmp(input, "cd ", 2) == 0)
			{
				handle_cd(input);
			}
			/* if (strncmp(input, "echo", 4) == 0)
			{
				handle_echo(input);
			} */
			if (strcmp(input, "exit") == 0)
			{
				free(input);
				free(prompt);
				break ;
			}
			if (strcmp(input, "pwd") == 0)
			{
				if (getcwd(cwd, sizeof(cwd)) != NULL)
				{
					printf("%s\n", cwd);
				}
				else
				{
					perror("getcwd");
				}
			}
			if (strcmp(input, "clear") == 0)
			{
				printf("\033[2J");  // Clear the screen
				printf("\033[H");  // Move the cursor to the top left corner
			}
			if (strcmp(input, "ls") == 0)
			{
				DIR *dir;
				struct dirent *entry;
				bool nothing;

				dir = opendir(".");
				if (!dir)
				{
					perror("opendir");
					exit(EXIT_FAILURE);
				}
				nothing = true;
				while ((entry = readdir(dir)) != NULL)
				{
					if (entry->d_name[0] != '.')
						printf("%s\t", entry->d_name);
					nothing = false;
				}
				if (nothing == false)
					printf("\n");
				closedir(dir);
			}
			if (strcmp(input, "history") == 0)
			{
				HIST_ENTRY **history;
				int i;

				history = history_list();
				i = 0;
				while (history[i])
				{
					printf("%d: %s\n", i, history[i]->line);
					i++;
				}
			}
			if (input[0] != '\0')
				add_history(input);
		}
		rl_clear_history();
	}
	return (0);
}
