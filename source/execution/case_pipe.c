/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikelitoris <mikelitoris@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:02:22 by mikelitoris       #+#    #+#             */
/*   Updated: 2024/12/08 14:35:02 by madao-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	case_pipe(t_pipe *pipe_cmd, t_data *ms_data)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		status;

	status = 0;
	if (pipe(pipe_fd) == -1)
		prepare_pipe_error(strerror(errno), ms_data, 0);
	pid = fork();
	if (pid == -1)
		prepare_pipe_error(strerror(errno), ms_data, 1);
	if (pid == 0)
		setup_pipe_exec_left(pipe_cmd, ms_data, pipe_fd, pid);
	pid = fork();
	if (pid == -1)
		prepare_pipe_error(strerror(errno), ms_data, 1);
	if (pid == 0)
		setup_pipe_exec_right(pipe_cmd, ms_data, pipe_fd, pid);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	handle_pipe_status(status, ms_data);
}

void	handle_pipe_status(int status, t_data *ms_data)
{
	int	exit_code;

	clean_shell(ms_data);
	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status))
		{
			exit_code = WEXITSTATUS(status);
		}
	}
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			write(2, "\n", 1);
			exit_code = 130;
		}
		else if (WCOREDUMP(status))
		{
			write(2, "Quit (core dumped)\n", 19);
			exit_code = 131;
		}
	}
	exit(exit_code);
}

void	setup_pipe_exec_left(t_pipe *pipe_cmd, t_data *ms_data, \
int *pipe_fd, pid_t pid)
{
	(void)pid;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	close(pipe_fd[0]);
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
	{
		print_exec_error(strerror(errno), "dup2");
		clean_shell(ms_data);
		exit(1);
	}
	close(pipe_fd[1]);
	exec_tree(pipe_cmd->left, ms_data);
}

void	setup_pipe_exec_right(t_pipe *pipe_cmd, t_data *ms_data, \
int *pipe_fd, pid_t pid)
{
	(void)pid;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
	{
		print_exec_error(strerror(errno), "dup2");
		clean_shell(ms_data);
		exit(1);
	}
	close(pipe_fd[0]);
	exec_tree(pipe_cmd->right, ms_data);
}

void	prepare_pipe_error(char *error, t_data *ms_data, int error_code)
{
	if (error_code == 0)
		print_exec_error(error, "pipe");
	else
		print_exec_error(error, "fork");
	clean_shell(ms_data);
	exit(1);
}
