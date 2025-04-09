/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madao-da <madao-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:18:15 by mikelitoris       #+#    #+#             */
/*   Updated: 2024/12/08 17:08:02 by madao-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_tree(t_cmd *tree, t_data *ms_data)
{
	t_exec	*exec_cmd;
	t_pipe	*pipe_cmd;
	int		exit_code;

	if (!tree)
	{
		exit_code = 0;
		clean_shell(ms_data);
		exit(exit_code);
	}
	if (tree->type == EXEC)
	{
		exec_cmd = (t_exec *)tree;
		case_exec(exec_cmd, ms_data);
	}
	else if (tree->type == REDI)
	{
		case_redir(tree, ms_data);
	}
	else if (tree->type == PIPE)
	{
		pipe_cmd = (t_pipe *)tree;
		case_pipe(pipe_cmd, ms_data);
	}
}
