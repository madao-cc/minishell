/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikelitoris <mikelitoris@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:03:32 by mikelitoris       #+#    #+#             */
/*   Updated: 2024/12/05 17:59:56 by mikelitoris      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	write_var(t_var *var)
{
	write(1, "declare -x ", 11);
	write(1, var->name, ft_strlen(var->name));
	write(1, "=\"", 2);
	write(1, var->value, ft_strlen(var->value));
	write(1, "\"\n", 2);
}

void	export_env(t_data *ms_data)
{
	t_var	**vars;
	int		i;

	vars = ft_create_bulk_vars(ms_data);
	sort_vars(vars);
	i = 0;
	while (vars[i])
	{
		if (vars[i]->value)
		{
			write_var(vars[i]);
		}
		else
		{
			write(1, "declare -x ", 11);
			write(1, vars[i]->name, ft_strlen(vars[i]->name));
			write(1, "\n", 1);
		}
		free(vars[i]->name);
		free(vars[i]->value);
		free(vars[i]);
		i++;
	}
	free(vars);
	ms_data->return_code = 0;
}

int	sort_vars(t_var **vars)
{
	int		i;
	int		j;
	t_var	*temp;

	i = 0;
	while (vars[i])
	{
		j = 0;
		while (vars[j])
		{
			if (vars[i]->name && vars[j]->name && \
			ft_strcmp(vars[i]->name, vars[j]->name) < 0)
			{
				temp = vars[i];
				vars[i] = vars[j];
				vars[j] = temp;
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	delete_bulk_vars(t_var **vars)
{
	int	i;

	if (!vars)
		return ;
	i = 0;
	while (vars[i])
	{
		free(vars[i]->name);
		free(vars[i]->value);
		free(vars[i]);
		i++;
	}
	free(vars);
}
