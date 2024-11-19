/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikelitoris <mikelitoris@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:49:25 by mikelitoris       #+#    #+#             */
/*   Updated: 2024/11/19 15:31:06 by mikelitoris      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_exit(char **argv, t_data *ms_data)
{
	int		exit_code;
	int		i;

	exit_code = 0;
	i = 0;
	if (argv[1])
	{
		if (check_arg2(argv, ms_data) == 1)
			return;
		write (1, "exit\n", 5);
		while (argv[1][i])
		{
			if (!ft_isdigit(argv[1][i]) && (i != 0 || argv[1][i] != '-'))
			{
				prepare_exit_error("numeric argument required", "exit", argv[1], ms_data, 2);
				exit_code = 2;
				break;
			}
			i++;
		}
		if (exit_code == 0)
			exit_code = atoi(argv[1]) % 256;
	}
	ms_data->return_code = exit_code;
	exit(exit_code);
}

int	check_arg2(char **argv, t_data *ms_data)
{
	if (argv[2])
	{
		prepare_error("too many arguments", "exit", ms_data, 1);
		return (1);
	}
	return (0);
}
