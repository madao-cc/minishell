/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madao-da <madao-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 14:25:44 by mikelitoris       #+#    #+#             */
/*   Updated: 2024/12/08 14:36:49 by madao-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_tree(t_data *ms_data, t_exec *exec_cmd, int *status)
{
	int		local_status;
	int		pid;

	(void)status;
	local_status = 0;
	if (exec_cmd == NULL)
		return ;
	if (exec_cmd->type == EXEC && search_builtin(exec_cmd->argv[0]))
		ft_exec_builtin(exec_cmd->argv, ms_data);
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		pid = fork();
		if (pid == 0)
		{
			exec_tree(ms_data->tree, ms_data);
		}
		waitpid(pid, &local_status, 0);
		from_parent(local_status, ms_data);
	}
}

void	from_parent(int local_status, t_data *ms_data)
{
	if (WIFSIGNALED(local_status))
	{
		if (WCOREDUMP(local_status))
		{
			write(2, "Quit (core dumped)\n", 19);
			ms_data->return_code = 131;
		}
		else if (WTERMSIG(local_status) == SIGINT)
		{
			write(2, "\n", 1);
			ms_data->return_code = 130;
		}
	}
	else
		ms_data->return_code = local_status / 256;
}
