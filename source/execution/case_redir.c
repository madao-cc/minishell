/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikelitoris <mikelitoris@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:42:54 by mikelitoris       #+#    #+#             */
/*   Updated: 2024/12/03 16:43:09 by mikelitoris      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	case_redir(t_cmd *tree, t_data *ms_data)
{
	int		fd;
	int		return_code;
	t_redir	*redir_cmd;

	redir_cmd = (t_redir *)tree;
	fd = open(redir_cmd->file, redir_cmd->mode, 0644);
	if (fd == -1)
	{
		handle_path_errors(redir_cmd->file, ms_data);
		return_code = ms_data->return_code;
		clean_shell(ms_data);
		exit(return_code);
	}
	if (dup2(fd, redir_cmd->fd) == -1)
	{
		print_exec_error(strerror(errno), "dup2");
		return_code = ms_data->return_code;
		clean_shell(ms_data);
		exit(return_code);
	}
	close(fd);
	exec_tree(redir_cmd->cmd, ms_data);
}
