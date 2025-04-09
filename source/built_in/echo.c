/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikelitoris <mikelitoris@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:49:19 by mikelitoris       #+#    #+#             */
/*   Updated: 2024/12/05 16:23:48 by mikelitoris      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_specifics(char c)
{
	if (c == 0)
		return (0);
	if (c != '\0')
	{
		if (whitespace(c))
		{
			while (whitespace(c))
				c++;
			if (c == '\0')
				return (1);
		}
	}
	return (1);
}

void	handle_echo(char **argv, t_data *ms_data)
{
	int	i;
	int	new_line;
	int	j;

	i = 1;
	new_line = 1;
	while (argv[i] && argv[i][0] == '-')
	{
		if (argv[i][1] == '\0')
			break ;
		j = 1;
		while (argv[i][j] == 'n')
			j++;
		if (argv[i][j] == 'e' || argv[i][j] == 'E')
		{
			prepare_error("What a trickster 🤡... you almost got me! LOL", \
			"option: e", ms_data, 1);
			return ;
		}
		if (check_specifics(argv[i][j]) == 1)
			break ;
		new_line = 0;
		i++;
	}
	print_arguments(argv, i, ms_data, new_line);
}

void	print_arguments(char **argv, int i, t_data *ms_data, int new_line)
{
	(void)ms_data;
	while (argv[i])
	{
		ft_putstr_fd(argv[i], 1);
		if (argv[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (new_line == 1)
		write(1, "\n", 1);
}
