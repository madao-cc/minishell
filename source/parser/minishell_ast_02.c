/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_ast_02.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antfonse <antfonse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 00:18:58 by antfonse          #+#    #+#             */
/*   Updated: 2024/11/03 16:00:49 by antfonse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// CREATE NEW REDIRECTION NODE IN SEQUENTIAL ORDER
t_cmd	*seq_redir(t_cmd *node, char *file, int mode, int fd)
{
	t_redir	*node0;
	t_cmd	*node1;

	if (node->type == EXEC)
	{
		node1 = check_node(redir_node(node, file, mode, fd));
		if (!node1)
			node = free_tree(node);
		else
			node = node1;
	}
	else
	{
		node0 = (t_redir *)(node);
		while (node0->cmd->type != EXEC)
			node0 = (t_redir *)(node0->cmd);
		node1 = check_node(redir_node(node0->cmd, file, mode, fd));
		if (!node1)
			node = free_tree(node);
		else
			node0->cmd = node1;
	}
	return (node);
}

t_cmd	*redir_type(t_data *ms_data, int token, t_cmd *node, char *stoken)
{
	if (token == TOKEN_INPU)
		node = seq_redir(node, stoken, O_RDONLY, 0);
	else if (token == TOKEN_OUTP)
		node = seq_redir(node, stoken, O_WRONLY | O_TRUNC | O_CREAT, 1);
	else if (token == TOKEN_DELI)
		node = heredoc_node(ms_data, node, stoken);
	else if (token == TOKEN_APPE)
		node = seq_redir(node, stoken, O_WRONLY | O_CREAT, 1);
	return (node);
}

// PARSE REDIRECTION
t_cmd	*parse_redir(t_data *ms_data, t_cmd *node, char **input)
{
	int		token;
	int		next_token;
	char	*stoken;
	char	*etoken;

	while (look_token(input, "<>"))
	{
		token = parse_token(input, 0, 0);
		next_token = parse_token(input, &stoken, &etoken);
		if (next_token == TOKEN_ERROR || next_token != TOKEN_TEXT)
		{
			if (next_token != TOKEN_TEXT)
				print_syntax_error(next_token);
			return (free_tree(node));
		}
		stoken = substr_expans(ms_data, stoken, etoken);
		if (!stoken)
			return (free_tree(node));
		node = redir_type(ms_data, token, node, stoken);
		if (!node)
			break ;
	}
	return (node);
}
