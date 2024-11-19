/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikelitoris <mikelitoris@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:49:12 by mikelitoris       #+#    #+#             */
/*   Updated: 2024/11/19 13:41:05 by mikelitoris      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	search_builtin(char *command)
{
	if (!strcmp(command, "echo"))
		return (true);
	if (!strcmp(command, "pwd"))
		return (true);
	if (!strcmp(command, "export"))
		return (true);
	if (!strcmp(command, "unset"))
		return (true);
	if (!strcmp(command, "env"))
		return (true);
	if (!strcmp(command, "exit"))
		return (true);
	if (!strcmp(command, "cd"))
		return (true);
	return (false);
}

 //TODO: SEE WHAT TO DO IF SOME COMMANDS HAVE OPTIONS - GIVE ERROR MESSAGE? UPDATE RETURN_CODE?
 
void	ft_exec_builtin(char **argv, t_data *ms_data)
{
	char 	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		prepare_error("getcwd failed", "in ft_exec_builtin", ms_data, 1);
		return ;
	}
	if (strcmp(argv[0], "export") == 0)
	{
		if (argv[1] == NULL)
		{
			export_env(ms_data);
			free(pwd);
			return ;
		}
		handle_export(argv, ms_data);
	}
	else	
		ft_exec_builtin_2(argv, ms_data, pwd);
	free(pwd);
}

void	ft_exec_builtin_2(char **argv, t_data *ms_data, char *pwd)
{
	
	if (strcmp(argv[0], "unset") == 0)
	{
		handle_unset(argv, ms_data);
		return ;
	}
	else if (strcmp(argv[0], "env") == 0)
	{
		handle_env(argv, ms_data);
	}
	else if (strcmp(argv[0], "exit") == 0)
	{
		handle_exit(argv, ms_data);
	}
	else if (strcmp(argv[0], "pwd") == 0)
	{
		handle_pwd(argv, ms_data);
	}
	else if (strcmp(argv[0], "echo") == 0)
	{
		handle_echo(argv);
	}
	else if (strcmp(argv[0], "cd") == 0)
	{
		handle_cd(ms_data, argv, pwd);
		//update_pwd(pwd, ms_data);
	}
}