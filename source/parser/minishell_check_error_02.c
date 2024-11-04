/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_check_error_02.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antfonse <antfonse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 17:16:45 by antfonse          #+#    #+#             */
/*   Updated: 2024/11/03 18:19:38 by antfonse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// PRINT ERROR IF ARGC IS TOO LONG
int	check_argv(char **argv, int argc)
{
	size_t	size;
	int		i;

	size = sizeof(argv);
	if (argc > 0)
	{
		size = size + (argc + 1) * sizeof(*argv);
		i = 0;
		while (argv[i])
		{
			size = size + (ft_strlen(argv[i]) + 1) * sizeof(*argv[i]);
			i++;
		}
		if (size > ARG_MAX)
		{
			print_error(ARG_LIMIT, argv[0]);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}
