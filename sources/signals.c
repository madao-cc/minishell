/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikelitoris <mikelitoris@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:01:22 by mikelitoris       #+#    #+#             */
/*   Updated: 2024/10/17 17:40:50 by mikelitoris      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

volatile sig_atomic_t g_signal_received = 0;

#ifndef NSIG
# define NSIG 65  // Number of signals. Tested with:  printf("NSIG: %d\n", NSIG);
#endif

void	handle_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_sigint(int sig)
{
	(void)sig;
	g_signal_received = 1;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}


