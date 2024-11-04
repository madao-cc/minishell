/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_ast_03.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antfonse <antfonse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:01:52 by antfonse          #+#    #+#             */
/*   Updated: 2024/11/03 21:21:19 by antfonse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	arraylen(char **str)
{
	char	**str2;

	if (!str)
		return (0);
	str2 = str;
	while (*str2)
		str2++;
	return (str2 - str);
}

static char	**create_new_argv(char **argv, char *stoken)
{
	char	**new_argv;
	int		argc;
	int		i;

	argc = arraylen(argv);
	new_argv = check_str_2d((char **)malloc((argc + 2) * sizeof(*new_argv)));
	if (!new_argv)
		free(stoken);
	else
	{
		ft_memset(new_argv, 0, (argc + 2) * sizeof(*new_argv));
		i = 0;
		while (i < argc)
		{
			new_argv[i] = argv[i];
			i++;
		}
		new_argv[i] = stoken;
	}
	return (new_argv);
}

int	fill_argv(char *stoken, t_exec *exec)
{
	char	**new_argv;

	if (*stoken == '\0')
		return (EXIT_SUCCESS);
	new_argv = create_new_argv(exec->argv, stoken);
	if (!new_argv)
		return (EXIT_FAILURE);
	free(exec->argv);
	exec->argv = new_argv;
	if (check_argv(exec->argv, arraylen(exec->argv)) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
