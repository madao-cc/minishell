/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikelitoris <mikelitoris@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:49:29 by mikelitoris       #+#    #+#             */
/*   Updated: 2024/11/19 15:31:38 by mikelitoris      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_export(char **argv, t_data *ms_data)
{
	int	i;
	char *name;

	i = 1;
	name = NULL;
	while (argv[i])
	{
		if (ft_strchr(argv[i], '='))
		{
			name = ft_strndup(argv[i], ft_strchr(argv[i], '=') - argv[i]);
			if (is_variable_name_ok(name) == 0 || argv[i][0] == '=')
			{
				export_helper(name, ms_data, i);
				break ;
			}
			if (find_variable(ms_data->variables, name) != -1)
				ms_data->variables = reduce_environment(ms_data->variables, name, ms_data);
			ms_data->variables = expand_environment(ms_data->variables, argv[i], ms_data);
			free(name);
			name = NULL;
		}
		i++;
	}
}

void	export_helper(char *name, t_data *ms_data, int i)
{
	prepare_error("Invalid variable name", name, ms_data, 1);
	free(name);
	i++;
}

void	export_env(t_data *ms_data)
{
	char	*name;
	char	*value;
	char	**variables;
	int		i;
	
	i = 0;
	variables = ms_data->variables;
	while (variables[i] != NULL)
	{
		name = ft_strndup(variables[i], ft_strchr(variables[i], '=') - variables[i]);
		value = ft_strchr(variables[i], '=') + 1;
		printf("declare -x %s=\"%s\"\n", name, value);
		free(name);
		i++;
	}
	ms_data->return_code = 0;
}
