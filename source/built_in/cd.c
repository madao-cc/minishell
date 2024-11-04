#include "../../includes/minishell.h"

void	handle_cd(t_data *ms_data)  //TODO: Falta caso de environment variable
{
	char *path;
	char *trimmed_path;
	char *original_path;
	int	i;

	i = 2;
	original_path = ft_strdup((const char *)ms_data->input);
	path = original_path + 3; // Because i change the pointer to not point to the start of the allocated string, when i call free it wont clear the right way. So original_string :)
	trimmed_path = ft_strtrim(path, " \n\t");
	i = 0;
	/* printf("trimmed_path: %s\n", trimmed_path); */
	if (strlen(trimmed_path) == 0 || (strcmp(ft_strtrim(trimmed_path, " \t"), "\n") == 0))
	{
			handle_home(ms_data);
			free(original_path);
			return ;
	}
	while (trimmed_path[i])
	{
		if (trimmed_path[i] == '~')
		{
			if (strcmp(trimmed_path, "~") == 0)
			{
				handle_home(ms_data);
				free(original_path);
				return ;
			}
		}
		if (trimmed_path[i] == '/')
		{
			handle_absolut_path(trimmed_path, ms_data);
			free(original_path);
			return ;
		}
		if ((ft_is_char(trimmed_path[i]) == 1) || (trimmed_path[i] == '/' || trimmed_path[i] == '~'))
		{
			handle_relative_path(trimmed_path, ms_data);
			free(original_path);
			return ;
		}
		if (trimmed_path[i] == '.')
		{
			handle_relative_path(trimmed_path, ms_data);
			free(original_path);
			return ;
		}
		i++;
	}
}

void	handle_absolut_path(char *line, t_data *ms_data)
{
	/* printf("line: %s\n", line); */
	if (chdir(line) == -1)
	{
		print_exec_error("No such file or directory", line);
		ms_data->return_code = 1;  
	}
}

void	handle_home(t_data *ms_data)
{
	char *home = getenv("HOME");
	if (home != NULL)
	{
		chdir(home);
	}
	else
	{
		print_exec_error("HOME not set", "cd");
		ms_data->return_code = 1;
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

void	handle_dot_cases(char *line, t_data *ms_data)
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
				if (chdir("") == -1)
				{
					print_exec_error("No such file or directory", path);
					ms_data->return_code = 1;
					return ;
				}
				
			}
		}
		if (strcmp(path, "..") == 0)
		{
			if (chdir("..") == -1)
			{
				print_exec_error("No such file or directory", path);
				ms_data->return_code = 1;
				return ;
			}
		}
		if (strcmp(path, ".") == 0)
		{
			if (chdir(".") == -1)
			{
				print_exec_error("No such file or directory", path);
				ms_data->return_code = 1;
				return ;
			}
		}
	}
}

void	handle_relative_path(char *line, t_data *ms_data)
{
	char *path;

	path = strsep(&line, "/");
	while (path != NULL)
	{
		if (strcmp(path, "~") == 0)
		{
			handle_home(ms_data);
		}
		else if (strcmp(path, ".") == 0)
		{
			if (chdir(".") == -1)
			{
				print_exec_error("No such file or directory", path);
				ms_data->return_code = 1;
			}
		}
		else if (strcmp(path, "..") == 0)
		{
			if (chdir("..") == -1)
			{
				print_exec_error("No such file or directory", path);
				ms_data->return_code = 1;
			}
		}
		else
		{
			if (chdir(path) == -1)
			{
				print_exec_error("No such file or directory", path);
				ms_data->return_code = 1;
			}
		}
		path = strsep(&line, "/");
	}
}
