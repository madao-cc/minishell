#include "../../includes/minishell.h"

void	print_exec_error(char *error_message, char *command)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error_message, 2);
	ft_putstr_fd("\n", 2);
}

void	handle_path_errors(char *path, t_data *ms_data)
{
	if (errno == ENOENT)
	{
		print_exec_error("No such file or directory", path);
		ms_data->return_code = 127;
	}
	else if (errno == EACCES)
	{
		print_exec_error("Permission denied", path);
		ms_data->return_code = 126;
	}
	else if (errno == ENOTDIR)
	{
		print_exec_error("Not a directory", path);
		ms_data->return_code = 126;
	}
	else if (errno == EISDIR)
	{
		print_exec_error("Is a directory", path);
		ms_data->return_code = 126;
	}
	else
	{
		print_exec_error(strerror(errno), path);
		ms_data->return_code = 1;
	}
}