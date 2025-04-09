/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikelitoris <mikelitoris@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:26:31 by mikelitoris       #+#    #+#             */
/*   Updated: 2024/12/02 12:20:28 by mikelitoris      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_heredoc(int sig, t_data *ms_data, char *delimiter, int fd)
{
	static t_data	*ms_data_tmp;
	static char		*delimiter_tmp;
	static int		fd_tmp;

	if (sig == -1)
	{
		ms_data_tmp = ms_data;
		delimiter_tmp = delimiter;
		fd_tmp = fd;
	}
	else if (sig == SIGINT)
	{
		g_sig_num = S_SIGINT;
		write(1, "\n", 1);
		exit_heredoc(ms_data_tmp, delimiter_tmp, fd_tmp, SIG_INT_TERM);
	}
}
