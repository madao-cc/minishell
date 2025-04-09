/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_option.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikelitoris <mikelitoris@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:25:04 by mikelitoris       #+#    #+#             */
/*   Updated: 2024/12/04 18:48:41 by mikelitoris      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_options_built_ins(char **argv, t_data *ms_data)
{
	int	checker;

	checker = 0;
	if (ft_strcmp(argv[0], "export") == 0)
		checker = check_options(argv, ms_data);
	else if (ft_strcmp(argv[0], "cd") == 0)
		checker = check_options_cd(argv, ms_data);
	else if (ft_strcmp(argv[0], "echo") == 0)
		checker = check_options_echo(argv, ms_data);
	else if (ft_strcmp(argv[0], "unset") == 0)
		checker = check_options(argv, ms_data);
	else if (ft_strcmp(argv[0], "exit") == 0)
		checker = check_options_exit(argv, ms_data);
	else if (ft_strcmp(argv[0], "pwd") == 0)
		checker = check_options(argv, ms_data);
	else if (ft_strcmp(argv[0], "env") == 0)
		checker = check_options(argv, ms_data);
	return (checker);
}

int	check_options_exit(char **argv, t_data *ms_data)
{
	if (!argv[1])
		return (0);
	if (ft_strcmp(argv[1], "--help") == 0)
		return (error_options("🤓 Minishell is not build for that my friend 🤓", \
		"--help", ms_data));
	return (0);
}

int	check_options(char **argv, t_data *ms_data)
{
	if (argv[1] == NULL)
		return (0);
	else if (ft_strncmp(argv[1], "-", 1) == 0 && ft_is_char(argv[1][1]) == 0)
		return (error_options("🤓 Minishell is not build for that my friend 🤓", \
		ft_strchr(argv[1], '-'), ms_data));
	else if (ft_strncmp(argv[1], "--", 2) == 0 && ft_is_char(argv[1][2]) == 0)
		return (error_options("🤓 Minishell is not build for that my friend 🤓", \
		ft_strchr(argv[1], '-'), ms_data));
	return (0);
}

int	check_options_echo(char **argv, t_data *ms_data)
{
	if (argv[1] == NULL)
		return (0);
	if (ft_strcmp(argv[1], "-E") == 0)
		return (error_options("🤓 Minishell is not build for that my friend 🤓", \
		"-E", ms_data));
	if (ft_strcmp(argv[1], "-e") == 0)
		return (error_options("🤓 Minishell is not build for that my friend 🤓", \
		"-e", ms_data));
	else if (ft_strcmp(argv[1], "--help") == 0)
		return (error_options("🤓 Minishell is not build for that my friend 🤓", \
		"--help", ms_data));
	else if (ft_strcmp(argv[1], "--version") == 0)
		return (error_options("🤓 Minishell is not build for that my friend 🤓", \
		"--version", ms_data));
	return (0);
}

int	check_options_cd(char **argc, t_data *ms_data)
{
	if (argc[1] == NULL)
		return (0);
	if (ft_strcmp(argc[1], "--help") == 0)
		return (error_options("🤓 Minishell is not build for that my friend 🤓", \
		"--help", ms_data));
	else if (ft_strcmp(argc[1], "-L") == 0)
		return (error_options("🤓 Minishell is not build for that my friend 🤓", \
		"--version", ms_data));
	else if (ft_strcmp(argc[1], "-P") == 0)
		return (error_options("🤓 Minishell is not build for that my friend 🤓", \
		"--version", ms_data));
	return (0);
}
