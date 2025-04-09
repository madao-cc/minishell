/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_extras_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikelitoris <mikelitoris@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:54:53 by mikelitoris       #+#    #+#             */
/*   Updated: 2024/12/04 15:01:56 by mikelitoris      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_print_exit(void)
{
	if (isatty(STDIN_FILENO))
		ft_putstr_fd("exit\n", STDOUT_FILENO);
}

int	check_arg2(char **argv, t_data *ms_data)
{
	int	arg_count;

	if (check_2_in_1(argv[1]) == 1)
	{
		if (ms_data->return_code == 0)
			prepare_error("too many arguments", "exit", ms_data, 1);
		else
			prepare_error("too many arguments", "exit", ms_data, \
			ms_data->return_code);
		return (1);
	}
	arg_count = ft_count_args(argv);
	if (arg_count > 2)
	{
		if (ms_data->return_code == 0)
			prepare_error("too many arguments", "exit", ms_data, 1);
		else
			prepare_error("too many arguments", "exit", ms_data, \
			ms_data->return_code);
		return (1);
	}
	return (0);
}

int	ft_is_char_opt(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}
