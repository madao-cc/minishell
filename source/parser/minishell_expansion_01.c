/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_expansion_01.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antfonse <antfonse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 14:17:01 by antfonse          #+#    #+#             */
/*   Updated: 2024/12/03 01:27:03 by antfonse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// GET VARIABLE NAME
int	getvarname(t_data *ms_data, char **start, char *end, char **var_name)
{
	char	*var_start;
	char	*var_end;

	var_start = *start;
	if (*start != end && ft_strchr(MS_DIGITS, **start))
		return (EXIT_SUCCESS);
	while (*start != end && ft_strchr(MS_VAR_CHAR, **start))
		(*start)++;
	var_end = *start;
	if (var_start < var_end)
	{
		*var_name = check_str(ms_data, substr(var_start, var_end));
		if (!*var_name)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

// GET RETURN CODE
char	*get_return_code(t_data *ms_data, char *start, char **str)
{
	char	*ret_str;

	ret_str = check_str(ms_data, ft_itoa(ms_data->return_code));
	if (ret_str)
		*str = check_str(ms_data, concat_str(*str, ret_str, ret_str + \
		ft_strlen(ret_str)));
	free(ret_str);
	start++;
	return (start);
}

// CASES WHERE VARIABLE NAME IS NULL
static char	*null_var(t_data *ms_data, char *start, char **str)
{
	if (ft_strchr(MS_QUOTES, *start) && *start != '\0')
		return (start);
	if (ft_strchr(MS_DIGITS, *start) && *start != '\0' && \
	ms_data->token != TOKEN_DELI)
		return (start + 1);
	*str = check_str(ms_data, concat_str(*str, start - 1, start));
	return (start);
}

// EXPAND VARIABLE
char	*expand_var(t_data *ms_data, char *start, char *end, char **str)
{
	char	*var_name;
	char	*var;

	start++;
	if (*start == '?')
		return (get_return_code(ms_data, start, str));
	var_name = NULL;
	if (ms_data-> token != TOKEN_DELI)
	{
		if (getvarname(ms_data, &start, end, &var_name) == EXIT_FAILURE)
		{
			*str = free_str(*str);
			return (start);
		}
	}
	if (!var_name)
		return (null_var(ms_data, start, str));
	var = my_getenv_expans(var_name, ms_data->variables);
	free(var_name);
	if (var)
		*str = check_str(ms_data, concat_str(*str, var, var + ft_strlen(var)));
	return (start);
}
