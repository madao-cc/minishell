/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikelitoris <mikelitoris@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:49:40 by mikelitoris       #+#    #+#             */
/*   Updated: 2024/11/19 12:13:58 by mikelitoris      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_unset(char **argv, t_data *ms_data)
{
	int	i;
	int	index;

	i = 1;
	if (argv[i] == NULL)
	{
		ms_data->return_code = 0;
		return ;
	}
	while (argv[i])
	{
		if ((index = find_variable(ms_data->variables, argv[i])) != -1)
			ms_data->variables = reduce_environment(ms_data->variables, argv[i], ms_data);
		i++;
	}
}
