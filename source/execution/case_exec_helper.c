/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_exec_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikelitoris <mikelitoris@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:46:57 by mikelitoris       #+#    #+#             */
/*   Updated: 2024/12/05 17:33:43 by mikelitoris      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_null_exec(t_data *ms_data, int exit_code)
{
	prepare_error("command not found", "", ms_data, 127);
	exit_code = ms_data->return_code;
	clean_shell(ms_data);
	exit(exit_code);
}

char	*check_path_exec(t_exec *exec_cmd, t_data *ms_data, int exit_code)
{
	char	*executable;

	(void)exit_code;
	if (exec_cmd->argv[0][0] == '/' || (exec_cmd->argv[0][0] == '.' && \
	exec_cmd->argv[0][1] == '/'))
		executable = ft_strdup(exec_cmd->argv[0]);
	else
		executable = find_executable(exec_cmd->argv[0], ms_data);
	return (executable);
}
