/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser_functions_01.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antfonse <antfonse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 20:16:50 by antfonse          #+#    #+#             */
/*   Updated: 2024/11/02 20:25:49 by antfonse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// PARSE QUOTES
static char	*parse_quotes(char *str, int *token)
{
	char	quote;

	quote = *str;
	str++;
	while (*str != quote)
	{
		if (*str == '\0')
		{
			print_error(QUOTE, &quote);
			*token = TOKEN_ERROR;
			return (str);
		}
		str++;
	}
	return (str);
}

// PARSE TEXT
char	*parse_text(char *str, int *token)
{
	*token = TOKEN_TEXT;
	while (*str != '\0' && !ft_strchr(MS_SPACE, *str) && \
	!ft_strchr(MS_TOKENS, *str))
	{
		if (ft_strchr(MS_QUOTES, *str))
		{
			str = parse_quotes(str, token);
			if (*token == TOKEN_ERROR)
				return (str);
			if (*str != '\0')
				str++;
		}
		else
			str++;
	}
	return (str);
}
