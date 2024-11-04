/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_error_handling_01.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antfonse <antfonse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 20:25:19 by antfonse          #+#    #+#             */
/*   Updated: 2024/11/03 17:54:48 by antfonse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// PRINT ERROR MESSAGE WITH SPECIFIC INFORMATION
static void	print_error_msg(char *msg, char *info)
{
	ft_putstr_fd(MSG_MINISHELL, STDERR_FILENO);
	if (*info == '\0')
		ft_putendl_fd(msg, STDERR_FILENO);
	else
	{
		ft_putstr_fd(msg, STDERR_FILENO);
		ft_putendl_fd(info, STDERR_FILENO);
	}
}

// PRINT ERROR MESSAGE WITH SPECIFIC INFORMATION (BACKWARDS)
static void	print_error_msg_reverse(char *msg, char *info)
{
	ft_putstr_fd(MSG_MINISHELL, STDERR_FILENO);
	if (*info == '\0')
		ft_putendl_fd(msg, STDERR_FILENO);
	else
	{
		ft_putstr_fd(info, STDERR_FILENO);
		ft_putendl_fd(msg, STDERR_FILENO);
	}
}

// PRINT ERROR MESSAGE ACCORDING TO ERROR CODE
void	print_error(int error_code, char *error_info)
{
	if (error_code == MALLOC)
		print_error_msg(MSG_MALLOC, "");
	if (error_code == SYNTAX)
		print_error_msg(MSG_SYNTAX, error_info);
	if (error_code == QUOTE)
		print_error_msg(MSG_QUOTE, error_info);
	if (error_code == ARG_LIMIT)
		print_error_msg_reverse(MSG_ARG_LIMIT, error_info);
	if (error_code == HEREDOC)
		print_error_msg(MSG_HEREDOC, "");
	if (error_code == INPUT)
		print_error_msg(MSG_INPUT, "");
}

void	print_syntax_error(int token)
{
	if (token == TOKEN_PIPE)
		print_error(SYNTAX, "`|\'");
	if (token == TOKEN_INPU)
		print_error(SYNTAX, "`<\'");
	if (token == TOKEN_OUTP)
		print_error(SYNTAX, "`>\'");
	if (token == TOKEN_DELI)
		print_error(SYNTAX, "`<<\'");
	if (token == TOKEN_APPE)
		print_error(SYNTAX, "`>>\'");
	if (token == TOKEN_EOF)
		print_error(SYNTAX, "`new line\'");
}
