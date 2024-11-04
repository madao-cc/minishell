/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_ast_04.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antfonse <antfonse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 01:39:43 by antfonse          #+#    #+#             */
/*   Updated: 2024/11/03 21:20:36 by antfonse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// FILL DATA IN EXECUTION NODE + LOOK FOR REDIRECTIONS AFTER COMMAND
static int	fill_exec(t_data *ms_data, char **input, t_exec *exec, t_cmd **node)
{
	int		token;
	char	*stoken;
	char	*etoken;

	while (!look_token(input, "|"))
	{
		token = parse_token(input, &stoken, &etoken);
		if (token == TOKEN_ERROR)
			return (EXIT_FAILURE);
		if (token == TOKEN_EOF && !exec->argv)
			return (EXIT_FAILURE);
		else if (token == TOKEN_EOF)
			return (EXIT_SUCCESS);
		stoken = substr_expans(ms_data, stoken, etoken);
		if (!stoken)
			return (EXIT_FAILURE);
		if (fill_argv(stoken, exec) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		*node = parse_redir(ms_data, *node, input);
	}
	return (EXIT_SUCCESS);
}

// PARSE EXECUTION
static t_cmd	*parse_exec(t_data *ms_data, char **input)
{
	t_cmd	*node;
	t_exec	*exec;

	node = check_node(exec_node());
	if (!node)
		return (NULL);
	exec = (t_exec *)node;
	node = parse_redir(ms_data, node, input);
	if (!node)
		return (NULL);
	if (fill_exec(ms_data, input, exec, &node) == EXIT_FAILURE)
		node = free_tree(node);
	return (node);
}

// PARSE PIPE
t_cmd	*parse_pipe(t_data *ms_data, char **input)
{
	t_cmd	*pnode;
	t_cmd	*lnode;
	t_cmd	*rnode;

	lnode = parse_exec(ms_data, input);
	if (!lnode)
		return (NULL);
	if (look_token(input, "|"))
	{
		parse_token(input, 0, 0);
		rnode = parse_pipe(ms_data, input);
		if (!rnode)
		{
			free(lnode);
			return (NULL);
		}
		pnode = check_node(pipe_node(lnode, rnode));
		if (!pnode)
			return (NULL);
		return (pnode);
	}
	return (lnode);
}
