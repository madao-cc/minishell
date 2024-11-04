/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_str_functions_02.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antfonse <antfonse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 14:17:01 by antfonse          #+#    #+#             */
/*   Updated: 2024/11/03 20:52:56 by antfonse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//  ADD PLAIN TEXT INSIDE DOUBLE QUOTES
static char	*add_text_double_quotes(char *start, char *end, char **str)
{
	char	*sub_start;
	char	*sub_end;

	sub_start = start;
	while (start != end && *start != '$' && *start != '"')
		start++;
	sub_end = start;
	if (sub_start && sub_end)
		*str = check_str(concat_str(*str, sub_start, sub_end));
	return (start);
}

// ADD TEXT IN DOUBLE QUOTES
static char	*double_quotes(t_data *ms_data, char *start, char *end, char **str)
{
	start++;
	while (start != end && *start != '"')
	{
		if (*start == '$')
			start = expand_var(ms_data, start, end, str);
		else
			start = add_text_double_quotes(start, end, str);
	}
	start++;
	return (start);
}

// ADD TEXT IN SINGLE QUOTES
static char	*single_quotes(char *start, char *end, char **str)
{
	char	*sub_start;
	char	*sub_end;

	start++;
	sub_start = start;
	while (start != end && *start != '\'')
		start++;
	sub_end = start;
	start++;
	if (sub_start && sub_end)
		*str = check_str(concat_str(*str, sub_start, sub_end));
	return (start);
}

//  ADD PLAIN TEXT
static char	*add_text(char *start, char *end, char **str)
{
	char	*sub_start;
	char	*sub_end;

	sub_start = start;
	while (start != end && *start != '$' && !ft_strchr(MS_QUOTES, *start))
		start++;
	sub_end = start;
	if (sub_start && sub_end)
		*str = check_str(concat_str(*str, sub_start, sub_end));
	return (start);
}

// CREATE A SUBSTRING FROM POINTER START TO POINTER END, REMOVING " AND '
// AND EXPANDING VARIABLES
char	*substr_expans(t_data *ms_data, char *start, char *end)
{
	char	*str;

	str = check_str((char *)ft_calloc(sizeof(char), sizeof(char)));
	if (!str)
		return (NULL);
	while (start < end)
	{
		if (*start == '$')
			start = expand_var(ms_data, start, end, &str);
		else if (*start == '"')
			start = double_quotes(ms_data, start, end, &str);
		else if (*start == '\'')
			start = single_quotes(start, end, &str);
		else
			start = add_text(start, end, &str);
		if (!str)
			return (NULL);
	}
	return (str);
}
