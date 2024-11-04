/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser_functions_02.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antfonse <antfonse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 01:21:06 by antfonse          #+#    #+#             */
/*   Updated: 2024/11/03 12:20:28 by antfonse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// CHECK IF NEXT CHARACTER IS ONE OF THE TOKEN SYMBOLS
int	look_token(char **input, char *tokens)
{
	char	*str;

	str = *input;
	while (*str != '\0' && ft_strchr(MS_SPACE, *str))
		str++;
	*input = str;
	return (*str && ft_strchr(tokens, *str));
}

// SET TOKEN
static char	*set_token(char *str, int *token, int token_symbol)
{
	*token = token_symbol;
	str++;
	return (str);
}

// GET TOKEN
static char	*get_token(char *str, int *token)
{
	if (*str == '\0')
		*token = TOKEN_EOF;
	else if (*str == '|')
		str = set_token(str, token, TOKEN_PIPE);
	else if (*str == '<')
	{
		str = set_token(str, token, TOKEN_INPU);
		if (*str == '<')
			str = set_token(str, token, TOKEN_DELI);
	}
	else if (*str == '>')
	{
		str = set_token(str, token, TOKEN_OUTP);
		if (*str == '>')
			str = set_token(str, token, TOKEN_APPE);
	}
	else
		str = parse_text(str, token);
	return (str);
}

// PARSE NEXT TOKEN IN INPUT LINE
int	parse_token(char **input, char **stoken, char **etoken)
{
	char	*str;
	int		token;

	str = *input;
	while (*str != '\0' && ft_strchr(MS_SPACE, *str))
		str++;
	if (stoken)
		*stoken = str;
	str = get_token(str, &token);
	if (token == TOKEN_ERROR)
		return (token);
	if (etoken)
		*etoken = str;
	while (*str != '\0' && ft_strchr(MS_SPACE, *str))
		str++;
	*input = str;
	return (token);
}
