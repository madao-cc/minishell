#include "../../includes/minishell.h"

void handle_signals(t_data *ms_data);
void handle_sigint(int sig);
void handle_eof(int sig);

void handle_signals(t_data *ms_data)
{
	struct sigaction sa_int;
	struct sigaction sa_quit;
	struct sigaction sa_eof;

	(void)ms_data;
	sa_int.sa_handler = handle_sigint;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;  // Restart functions if interrupted by handler
	sigaction(SIGINT, &sa_int, NULL);

	sa_quit.sa_handler = SIG_IGN;  // Ignore the signal to prevent the shell from printing ^\(:D)
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa_quit, NULL);

	sa_eof.sa_handler = handle_eof;
	sigemptyset(&sa_eof.sa_mask);
	sa_eof.sa_flags = SA_RESTART;
	sigaction(SIGTERM, &sa_eof, NULL);
}

void handle_sigint(int sig)
{
    	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void handle_eof(int sig)
{
	(void)sig;
	write(1, "exit\n", 5);
}
