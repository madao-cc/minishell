/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reducer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikelitoris <mikelitoris@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:47:23 by mikelitoris       #+#    #+#             */
/*   Updated: 2024/11/19 17:32:22 by mikelitoris      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**reduce_environment(char **envp, char *var, t_data *ms_data)
{
	int	index;
	char	**new_envp;
	int	len;

	index = find_variable(envp, var);
	if (index == -1)
	{
		prepare_error("Variable not found", var, ms_data, 1);
		return (envp);
	}
	len = 0;
	while (envp[len])
		len++;
	new_envp = malloc((len) * sizeof(char *));
	if (!new_envp)
	{
		prepare_error("Malloc failed", var, ms_data, 1);
		return (NULL);
	}
	if (reducer_helper(envp, new_envp, var, ms_data, 0, len, index) == 1)
		return (NULL);
	delete_variables(envp);
	return (new_envp);
}

int	reducer_helper(char **envp, char **new_envp, char *var, t_data *ms_data, int i, int len, int index)
{
	int		j;
	
	(void)ms_data;
	(void)var;
	j = 0;	
	while (i < (len))
	{
		if (i != index)
		{
			new_envp[j] = ft_strdup(envp[i]);
			if (!new_envp[j])
			{
				delete_remain_reducer(new_envp, j);
				ms_data->return_code = 1;
				return (1);
			}
			j++;
		}
		i++;
	}
	new_envp[j] = NULL;
	return (0);
}

void	delete_remain_reducer(char **variables, int len)
{
	perror("strdup");
	while (len > 0 && variables[len])
	{
		free(variables[len]);
		len--;
	}
	free(variables);
}
