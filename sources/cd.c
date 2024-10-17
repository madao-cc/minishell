#include "minishell.h"

void	handle_cd(char *line)  //TODO: Falta caso de environment variable
{
	char *path;
	char *trimmed_path;
	int	i;

	i = 2;
	path = ft_strdup(&line[i]);
	trimmed_path = ft_strtrim(path, " \n\t");
	i = 0;
	if (strlen(trimmed_path) == 0 || (strcmp(ft_strtrim(trimmed_path, " \t"), "\n") == 0))
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
		if (strcmp(path, "~") == 0)
		{
			handle_home();
		}
		else if (strcmp(path, ".") == 0)
		{
			chdir(".");
		}
		else if (strcmp(path, "..") == 0)
		{
			chdir("..");
		}
		else
			chdir(path);
		path = strsep(&line, "/");
	}
}
