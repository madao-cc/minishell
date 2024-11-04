/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_check_error_01.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antfonse <antfonse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 22:36:14 by antfonse          #+#    #+#             */
/*   Updated: 2024/11/03 17:18:20 by antfonse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// PRINT ERROR IF NODE WAS NOT CREATED
t_cmd	*check_node(t_cmd *node)
{
	if (!node)
		print_error(MALLOC, "");
	return (node);
}

// PRINT ERROR IF STRING WAS NOT ALLOCATED
char	*check_str(char *str)
{
	if (!str)
		print_error(MALLOC, "");
	return (str);
}

// PRINT ERROR IF STRING 2D WAS NOT ALLOCATED
char	**check_str_2d(char **str)
{
	if (!str)
		print_error(MALLOC, "");
	return (str);
}

// PRINT ERROR IF FILE WAS NOT CREATED
int	check_fd(int fd)
{
	if (fd == -1)
		print_error(HEREDOC, "");
	return (fd);
}

// PRINT ERROR IF READLINE RETURNED NULL
char	*check_readline(char *str)
{
	if (!str)
		print_error(INPUT, "");
	return (str);
}
