/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madao-da <madao-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:49:29 by mikelitoris       #+#    #+#             */
/*   Updated: 2024/12/08 15:54:09 by madao-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_export(char **argv, t_data *ms_data)
{
	int		i;
	char	*tmp;
	t_var	**vars;

	i = 0;
	vars = ft_create_bulk_vars(ms_data);
	while (argv[++i])
	{
		if (ft_strchr(argv[i], '='))
		{
			tmp = ft_substr(argv[i], 0, ft_strchr(argv[i], '=') - argv[i]);
			if (argv[i][0] == '+' || argv[i][0] == '=')
				ft_xpo(tmp, argv, ms_data, i);
			else if (tmp && tmp[ft_strlen(tmp) - 1] == '+')
				case_equal_plus(argv, ms_data, vars, i);
			else
				handle_variable(argv, ms_data, i);
			free(tmp);
		}
		else
			case_no_equal(argv, ms_data, i);
	}
	delete_bulk_vars(vars);
}

void	ft_xpo(char *tmp, char **argv, t_data *ms_data, int i)
{
	(void)tmp;
	prepare_error("not a valid identifier", argv[i], ms_data, 1);
}

void	handle_variable(char **argv, t_data *ms_data, int i)
{
	char	*name;

	name = ft_strndup(argv[i], ft_strchr(argv[i], '=') - argv[i]);
	if (is_variable_name_ok(name) == 0 || argv[i][0] == '=')
	{
		prepare_error("not a valid identifier", argv[i], ms_data, 1);
		free(name);
		i++;
		return ;
	}
	if (find_variable(ms_data->variables, name) != -1)
		ms_data->variables = \
		reduce_environment(ms_data->variables, name, ms_data);
	ms_data->variables = \
	expand_environment(ms_data->variables, argv[i], ms_data);
	free(name);
	name = NULL;
}
