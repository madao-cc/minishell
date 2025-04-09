/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikelitoris <mikelitoris@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:49:25 by mikelitoris       #+#    #+#             */
/*   Updated: 2024/12/04 15:04:11 by mikelitoris      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static long long	ft_strtoll_helper(char *str, long long result, int sign)
{
	int	digit;

	while (*str >= '0' && *str <= '9')
	{
		digit = *str - '0';
		if (result > (LLONG_MAX - digit) / 10)
		{
			errno = ERANGE;
			if (sign == 1)
				return (LLONG_MAX);
			else
				return (LLONG_MIN);
		}
		result = result * 10 + digit;
		str++;
	}
	return (result);
}

static long long	ft_strtoll(const char *str, char **endptr)
{
	long long	result;
	int			sign;
	int			i;

	errno = 0;
	i = 0;
	result = 0;
	sign = 1;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	result = ft_strtoll_helper((char *)str + i, result, sign);
	if (endptr)
		*endptr = (char *)str;
	return (result * sign);
}

void	handle_exit(char **argv, t_data *ms_data, char *pwd)
{
	int			exit_code;
	char		*endptr;
	long long	num;

	check_print_exit();
	exit_code = ms_data->return_code;
	if (argv[1])
	{
		num = ft_strtoll(argv[1], &endptr);
		if (check_required_args(argv[1], ms_data, num) == 1)
		{
			prepare_exit_numeric("numeric argument required", argv, \
			ms_data, 2);
			prepare_to_exit(ms_data, pwd, 2);
		}
		if (check_arg2(argv, ms_data) == 1)
			return ;
		else
		{
			exit_code = num % 256;
			if (exit_code < 0)
				exit_code = exit_code + 256;
		}
	}
	prepare_to_exit(ms_data, pwd, exit_code);
}
