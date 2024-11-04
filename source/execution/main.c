/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikelitoris <mikelitoris@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 00:04:00 by antfonse          #+#    #+#             */
/*   Updated: 2024/11/04 15:51:20 by mikelitoris      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>

static void	print_exec(t_cmd *node)
{
	t_exec	*exec_node;
	char	**argv;
	int		i;

	exec_node = (t_exec *)node;
	if (exec_node->argv)
	{
		argv = exec_node->argv;
		i = 0;
		while (argv[i])
		{
			printf(" %s", argv[i]);
			i++;
		}
	}
}
void	print_tree(t_cmd *node);

static void	print_redir(t_cmd *node)
{
	t_redir	*redir_node;

	redir_node = (t_redir *)node;
	if (redir_node->fd == 0)
		printf(" < %s", redir_node->file);
	if (redir_node->fd == 1)
		printf(" > %s", redir_node->file);
	if (redir_node->cmd)
		print_tree(redir_node->cmd);
}

static void	print_pipe(t_cmd *node)
{
	t_pipe	*pipe_node;

	pipe_node = (t_pipe *)node;
	print_tree(pipe_node->left);
	printf(" |");
	print_tree(pipe_node->right);
}

void	print_tree(t_cmd *node)
{
	if (node->type == PIPE)
		print_pipe(node);
	else if (node->type == REDI)
		print_redir(node);
	else if (node->type == EXEC)
		print_exec(node);
}

/* int	main(int argc, char *argv[], char *envp[])
{
	t_data	*ms_data;

	(void)argc;
	(void)argv;
	(void)envp;
	ms_data = init_minishell();
	if (ms_data)
	{
		ms_data->input = check_readline(readline("minishell: "));
		if (!ms_data->input)
			return (EXIT_FAILURE);
		if (*(ms_data->input) == '\0')
		{
			final_clean(ms_data);
			return (EXIT_SUCCESS);
		}
		ms_data->tree = create_tree(ms_data);
		if (ms_data->tree)
		{
			print_tree(ms_data->tree);
			printf("\n");
		}
		final_clean(ms_data);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
} */

int	main(int argc, char **argv, char **envp)
{
	t_data	*ms_data;
	t_exec	*exec_cmd;
	bool		clear;
	int		status;

	(void)argc;
	(void)argv;
	(void)envp;
	clear = true;
	if (isatty(STDIN_FILENO))
	{
		ms_data = init_minishell(envp);
		handle_signals(ms_data);
		while (1)
		{
			ms_data->input = readline("minishell: "); //TODO funcao segurança
			if (ms_data->input == NULL)
			{
				write(1, "\033[1;31mExiting...\n\033[0m", 23);
				final_clean(ms_data);
				clear = false;
				break ;
			}
			else if (*(ms_data->input) == '\0')  // ou ft_strcmp(ms_data->input, "") == 0
			{
				ms_data->return_code = 0;
				//* free(ms_data->input);
				continue ;
			}
			//TODO verificar input == $?
			else
				ms_data->tree = create_tree(ms_data);
			if (ms_data->tree) // ou ms_data->tree == NULL
			{
				exec_cmd = (t_exec *)ms_data->tree;
				if (exec_cmd->type == EXEC && search_builtin(exec_cmd->argv[0]))
				{
					ft_exec_builtin(exec_cmd->argv, ms_data);
				}
				else
				{
					if (fork() == 0)  //TODO funcao seguranca
					{
						exec_tree(ms_data->tree, ms_data);
						exit(0); // TODO verificar se é necessário
					}
					else
					{
						waitpid(-1, &status, 0);
						if (WIFEXITED(status))
							ms_data->return_code = WEXITSTATUS(status);
					}
				}
			}
			if (ms_data->input)  // ou ms_data->input != NULL
				add_history(ms_data->input);
		}
		rl_clear_history();
	}
	if (clear)
		final_clean(ms_data);
	return (0);  // TODO verificar se é necessario
}