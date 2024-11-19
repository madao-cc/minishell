#include "../../includes/minishell.h"

void	print_exec_error(char *error_message, char *command)
{
	ft_putstr_fd("ERROR: ", 2);
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
	else if (errno == EISDIR)
	{
		print_exec_error("Is a directory", path);
		ms_data->return_code = 126;
	}
	else if (errno == ENOTDIR)
	{
		print_exec_error("Not a directory", path);
		ms_data->return_code = 126;
	}
	else if (errno == EACCES)
	{
		print_exec_error("Permission denied", path);
		ms_data->return_code = 126;
	}
	else
	{
		print_exec_error(strerror(errno), path);
		ms_data->return_code = 1;
	}
}

void	prepare_error(char *error_message, char *command, t_data *ms_data, int return_code)
{
	print_exec_error(error_message, command);
	ms_data->return_code = return_code;	
}


void	prepare_cd_error(char *error_message, char *command, t_data *ms_data, int return_code, int error_code)
{
	if (error_code == ENOENT)
		prepare_error("No such file or directory", command, ms_data, 1);
	else if (error_code == EACCES)
		prepare_error("Permission denied", command, ms_data, 1);
	else
		prepare_error(error_message, command, ms_data, return_code);
}

void	prepare_exit_error(char *error_message, char *command, char *arg, t_data *ms_data, int return_code)
{
	ft_putstr_fd("ERROR: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error_message, 2);
	ft_putstr_fd("\n", 2);
	ms_data->return_code = return_code;
}
