/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikelitoris <mikelitoris@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:56:47 by mikelitoris       #+#    #+#             */
/*   Updated: 2024/12/04 14:07:32 by mikelitoris      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_codes_130(t_data *ms_data, int *return_code)
{
	ms_data->return_code = 130;
	*return_code = 130;
	g_sig_num = NO_SIG;
}

void	handle_signals(void)
{
	signal(SIGINT, handle_sigint_parent);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_sigint_parent(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_sig_num = S_SIGINT;
	}
}
