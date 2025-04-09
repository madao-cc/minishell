/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikelitoris <mikelitoris@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:24:40 by mikelitoris       #+#    #+#             */
/*   Updated: 2024/12/04 20:09:43 by mikelitoris      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_input(t_data *ms_data, char ***my_envs, int *return_code)
{
	t_exec	*exec_cmd;
	int		status;

	ms_data->input = readline("minishell$ ");
	if (g_sig_num == S_SIGINT)
		update_codes_130(ms_data, return_code);
	if (!ms_data->input)
		exit_minishell(ms_data, *my_envs);
	if (*(ms_data->input) == '\0')
	{
		free_and_copy_environment(my_envs, ms_data->variables);
		clean_shell(ms_data);
		return ;
	}
	ms_data->tree = create_tree(ms_data);
	if (ms_data->tree)
	{
		exec_cmd = (t_exec *)ms_data->tree;
		execute_tree(ms_data, exec_cmd, &status);
	}
	*return_code = ms_data->return_code;
	if (ms_data->input)
		add_history(ms_data->input);
	free_and_copy_environment(my_envs, ms_data->variables);
	clean_shell(ms_data);
}
