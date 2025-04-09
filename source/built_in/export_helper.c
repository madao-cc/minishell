/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madao-da <madao-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:05:31 by mikelitoris       #+#    #+#             */
/*   Updated: 2024/12/08 15:53:01 by madao-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	case_equal_plus(char **argv, t_data *ms_data, t_var **vars, int i)
{
	char	*name;

	name = extract_variable_name(argv[i]);
	if (!name)
		return ;
	if (!validate_variable_name(name, ms_data, argv[i]))
	{
		free(name);
		return ;
	}
	if (process_existing_variables(name, argv[i], ms_data, vars) == 1)
	{
		return ;
	}
	add_new_variable(name, argv[i], ms_data);
	free(name);
}

char	*extract_variable_name(char *arg)
{
	char	*name;

	name = ft_strndup(arg, ft_strchr(arg, '+') - arg);
	return (name);
}

int	process_existing_variables(char *name, char *arg, t_data *ms_data, \
t_var **vars)
{
	int		i;
	char	*old_value;
	char	*new_value;

	i = 0;
	while (ms_data->variables[i])
	{
		if (ft_strcmp(name, vars[i]->name) == 0)
		{
			old_value = ft_strdup(ft_strchr(ms_data->variables[i], '='));
			ms_data->variables = \
			reduce_environment(ms_data->variables, name, ms_data);
			new_value = ft_strjoin(old_value, ft_strchr(arg, '=') + 1);
			free(old_value);
			old_value = ft_strjoin(name, new_value);
			free(new_value);
			free(name);
			ms_data->variables = expand_environment(ms_data->variables, \
			old_value, ms_data);
			free(old_value);
			return (1);
		}
		i++;
	}
	return (0);
}

int	validate_variable_name(char *name, t_data *ms_data, char *arg)
{
	if (is_variable_name_ok(name) == 0)
	{
		prepare_error("not a valid identifier", arg, ms_data, 1);
		return (0);
	}
	return (1);
}

void	add_new_variable(char *name, char *arg, t_data *ms_data)
{
	char	*var;

	var = ft_strjoin(name, ft_strchr(arg, '='));
	ms_data->variables = expand_environment(ms_data->variables, var, ms_data);
	free(var);
}
