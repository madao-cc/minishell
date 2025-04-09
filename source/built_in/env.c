/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikelitoris <mikelitoris@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:49:22 by mikelitoris       #+#    #+#             */
/*   Updated: 2024/12/04 20:18:42 by mikelitoris      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_env(char **argv, t_data *ms_data)
{
	int			i;

	ms_data->return_code = 0;
	i = 0;
	if (argv[1])
	{
		prepare_error("too many arguments", "env", ms_data, 2);
		return ;
	}
	while (ms_data->variables[i])
	{
		ft_putstr_fd(ms_data->variables[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
}
