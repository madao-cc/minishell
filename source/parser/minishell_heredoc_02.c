/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_heredoc_02.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikelitoris <mikelitoris@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 04:47:19 by antfonse          #+#    #+#             */
/*   Updated: 2024/12/03 15:35:50 by mikelitoris      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// CLEAN MEMORY IN HEREDOC CHILD PROCESS AND EXIT WITH GIVEN RETURN CODE
int	exit_heredoc(t_data *ms_data, char *delimiter, int fd, int r_code)
{
	free(delimiter);
	close(fd);
	free(ms_data->filename);
	free(ms_data->prompt);
	free(ms_data->input);
	ft_lstclear(&(ms_data->lst_nodes), &ft_del);
	delete_variables(ms_data->variables);
	free(ms_data);
	exit(r_code);
}

// WRITE EACH LINE TO HEREDOC FILE UNTIL EOF
static void	write_heredoc_lines(t_data *ms_data, char *delimiter, int fd)
{
	size_t	len;
	char	*line;

	handle_heredoc(-1, ms_data, delimiter, fd);
	signal(SIGINT, (void *)handle_heredoc);
	line = NULL;
	len = ft_strlen(delimiter);
	while (1)
	{
		line = check_readline(ms_data, readline("> "), delimiter);
		if (!line)
			exit_heredoc(ms_data, delimiter, fd, EXIT_SUCCESS);
		if (ft_strncmp(delimiter, line, len) != 0 || ft_strlen(line) != len)
		{
			line = substr_heredoc(ms_data, line, line + ft_strlen(line));
			if (!line)
				exit_heredoc(ms_data, delimiter, fd, EXIT_FAILURE);
			ft_putendl_fd(line, fd);
			line = free_str(line);
		}
		else
			break ;
	}
	line = free_str(line);
	exit_heredoc(ms_data, delimiter, fd, EXIT_SUCCESS);
}

// WRITE SHELL LINES TO HEREDOC FILE
int	write_heredoc(t_data *ms_data, char *delimiter, int fd)
{
	int		wstatus;
	int		ret_code;
	pid_t	pid;

	ret_code = 0;
	signal(SIGINT, SIG_IGN);
	pid = check_fork(ms_data, fork());
	if (pid == -1)
	{
		handle_signals();
		return (EXIT_FAILURE);
	}
	if (pid == 0)
		write_heredoc_lines(ms_data, delimiter, fd);
	waitpid(0, &wstatus, WUNTRACED);
	if (WIFEXITED(wstatus))
		ret_code = WEXITSTATUS(wstatus);
	handle_signals();
	if (ret_code != EXIT_SUCCESS)
	{
		ms_data->return_code = ret_code;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
