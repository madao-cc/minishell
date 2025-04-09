/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_heredoc_01.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antfonse <antfonse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 01:35:57 by antfonse          #+#    #+#             */
/*   Updated: 2024/12/03 01:37:27 by antfonse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// CASES WHERE VARIABLE NAME IS NULL - HEREDOC
static char	*null_var_heredoc(t_data *ms_data, char *start, char **str)
{
	if (ft_strchr(MS_DIGITS, *start) && *start != '\0' && \
	ms_data->text_quotes == false)
		return (start + 1);
	*str = check_str(ms_data, concat_str(*str, start - 1, start));
	return (start);
}

// EXPAND VARIABLE - HEREDOC
static char	*expand_var_heredoc(t_data *ms_data, char *start, char *end, \
char **str)
{
	char	*var_name;
	char	*var;

	start++;
	if (*start == '?')
		return (get_return_code(ms_data, start, str));
	var_name = NULL;
	if (ms_data-> text_quotes == false)
	{
		if (getvarname(ms_data, &start, end, &var_name) == EXIT_FAILURE)
		{
			*str = free_str(*str);
			return (start);
		}
	}
	if (!var_name)
		return (null_var_heredoc(ms_data, start, str));
	var = my_getenv_expans(var_name, ms_data->variables);
	free(var_name);
	if (var)
		*str = check_str(ms_data, concat_str(*str, var, var + ft_strlen(var)));
	return (start);
}

// ADD PLAIN TEXT - HEREDOC
static char	*text_heredoc(t_data *ms_data, char *start, char *end, char **str)
{
	char	*sub_start;
	char	*sub_end;

	sub_start = start;
	while (start < end && *start != '$')
		start++;
	sub_end = start;
	if (sub_start < sub_end)
		*str = check_str(ms_data, concat_str(*str, sub_start, sub_end));
	return (start);
}

// CREATE A SUBSTRING FROM POINTER START TO POINTER END EXPANDING VARIABLES
// HEREDOC
char	*substr_heredoc(t_data *ms_data, char *start, char *end)
{
	char	*str;

	str = check_str(ms_data, (char *)ft_calloc(sizeof(char), sizeof(char)));
	if (!str)
		return (NULL);
	while (start < end)
	{
		if (*start == '$')
			start = expand_var_heredoc(ms_data, start, end, &str);
		else
			start = text_heredoc(ms_data, start, end, &str);
		if (!str)
			return (NULL);
	}
	return (str);
}
