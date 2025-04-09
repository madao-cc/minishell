/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikelitoris <mikelitoris@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:03:58 by mikelitoris       #+#    #+#             */
/*   Updated: 2024/12/04 14:28:37 by mikelitoris      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_var	**ft_create_bulk_vars(t_data *ms_data)
{
	int		var_count;
	t_var	**vars;

	var_count = count_vars(ms_data->variables);
	vars = allocate_var_array(var_count, ms_data);
	if (!vars)
		return (NULL);
	if (!populate_vars(vars, ms_data, var_count))
	{
		free_vars(vars, var_count);
		return (NULL);
	}
	return (vars);
}

int	count_vars(char **variables)
{
	int	i;

	i = 0;
	while (variables[i])
		i++;
	return (i);
}

t_var	**allocate_var_array(int count, t_data *ms_data)
{
	t_var	**vars;

	vars = malloc(sizeof(t_var *) * (count + 1));
	if (!vars)
	{
		prepare_error("malloc failed (tmp_vars.c(l.93))", "UOPS!", ms_data, 1);
		return (NULL);
	}
	return (vars);
}

int	populate_vars(t_var **vars, t_data *ms_data, int count)
{
	int		i;
	char	*tmp;

	i = 0;
	while (i < count)
	{
		vars[i] = malloc(sizeof(t_var));
		if (!vars[i])
			return (0);
		tmp = ft_strchr(ms_data->variables[i], '=');
		if (!tmp)
		{
			vars[i]->name = ft_strdup(ms_data->variables[i]);
			vars[i]->value = NULL;
		}
		else
		{
			vars[i]->name = ft_strndup(ms_data->variables[i], \
			tmp - ms_data->variables[i]);
			vars[i]->value = ft_strdup(tmp + 1);
		}
		i++;
	}
	vars[i] = NULL;
	return (1);
}

void	free_vars(t_var **vars, int count)
{
	while (count >= 0)
	{
		free(vars[count]->name);
		free(vars[count]->value);
		free(vars[count]);
		count--;
	}
	free(vars);
}
