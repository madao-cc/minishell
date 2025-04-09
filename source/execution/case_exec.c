/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikelitoris <mikelitoris@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:49:12 by mikelitoris       #+#    #+#             */
/*   Updated: 2024/12/05 19:37:28 by mikelitoris      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	case_exec(t_exec *exec_cmd, t_data *ms_data)
{
	char	*executable;
	int		exit_code;

	exit_code = 0;
	if (exec_cmd->argv[0][0] == '\0')
		handle_null_exec(ms_data, exit_code);
	if (search_builtin(exec_cmd->argv[0]))
	{
		ft_exec_builtin(exec_cmd->argv, ms_data);
		exit_code = ms_data->return_code;
		clean_shell(ms_data);
		exit(exit_code);
	}
	executable = check_path_exec(exec_cmd, ms_data, exit_code);
	if (executable)
		handle_executable(executable, exec_cmd, ms_data);
	else
		command_not_found(exec_cmd->argv[0], ms_data, exit_code);
}

void	handle_executable(char *executable, t_exec *exec_cmd, t_data *ms_data)
{
	struct stat	file_stat;
	int			exit_code;

	if (stat(executable, &file_stat) == 0 && S_ISDIR(file_stat.st_mode))
	{
		handle_executable_helper(executable, exec_cmd, \
		ms_data, 0);
	}
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	execve(executable, exec_cmd->argv, ms_data->variables);
	handle_exec_errors(executable, ms_data);
	exit_code = ms_data->return_code;
	free(executable);
	clean_shell(ms_data);
	exit(exit_code);
}

void	command_not_found(char *command, t_data *ms_data, int exit_code)
{
	prepare_error("command not found", command, ms_data, 127);
	exit_code = ms_data->return_code;
	clean_shell(ms_data);
	exit(exit_code);
}

void	handle_executable_helper(char *executable, t_exec *exec_cmd, \
t_data *ms_data, int exit_code)
{
	exit_code = 0;
	if (ft_strcmp(exec_cmd->argv[0], ".") == 0)
	{
		write(2, "ERROR: .: filename argument required\n", 37);
		write(2, ".: usage: . filename [arguments]\n", 33);
		exit_code = 2;
	}
	else if (ft_strcmp(exec_cmd->argv[0], "..") == 0)
	{
		write(2, "ERROR: ..: command not found\n", 29);
		exit_code = 127;
	}
	else
	{
		print_exec_error("Is a directory", executable);
		exit_code = 126;
	}
	free(executable);
	clean_shell(ms_data);
	exit(exit_code);
}
