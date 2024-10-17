#include "minishell.h"
#include "readline/readline.h"
#include "readline/history.h"

/*
	IMPORTANT STUFF TO NOTE OUT:
	
	- clear: DONT KNOW IF IT SHOULD BE IMPLEMENTED IN THE MAIN FUNCTION OR LATER ON
	
	
	
	
*/

int	main(void)
{
	char	cwd[PATH_MAX];
	char	*prompt;
	char	*input;
	t_cmd	*tree;

	if (isatty(STDIN_FILENO))
	{
		handle_signals();
		while (1)
		{
			if (g_signal_received)
			{
				g_signal_received = 0;
				continue;
			}
			if (getcwd(cwd, sizeof(cwd)) == NULL)
			{
				perror("getcwd");
				exit(EXIT_FAILURE);
			}
			prompt = ft_prepare_prompt();
			input = readline(prompt);
			tree = NULL;
			if (input == NULL)  // CTRL+D
			{
				write(1, "\033[1;31mExiting...\n\033[0m", 23);
				free(prompt);
				free(input);
				if (tree)
					free_tree(tree); //TODO: implement free_tree
				break ;
			}
			input = ft_trim(input);
			if (strncmp(input, "cd ", 2) == 0)
			{
				handle_cd(input);
			}
			else if (strncmp(input, "exit", 4) == 0)
			{
				free(prompt);
				free(input);
				if (tree)
					free_tree(tree); //TODO: implement free_tree
				break ;
			}
			else if (strncmp(input, "clear", 5) == 0)
			{
				write(1, "\033[H\033[J", 7);  // clear screen ->//! Nao sei se é a forma correta
			}
			// JUST FOR TESTING
			else if (strcmp(input, "history") == 0)
			{
				HIST_ENTRY **list;
				int			i;

				list = history_list();
				i = 0;
				while (list[i])
				{
					printf("%d: %s\n", i, list[i]->line);
					i++;
				}
			}
			// END OF TESTING
			else
			{
				tree = parse_tree(input);
			}
			if (tree != NULL)  //TODO: see if this is the correct way
			{
				if (fork() == 0)
				{
					exec_tree(tree);
					exit(EXIT_SUCCESS);
				}
				else
				{
					wait(NULL);
				}
			}
			if (input[0] != '\0')
				add_history(input);
			free(input);
			free(prompt);
			if (tree)
				free_tree(tree);  //TODO: implement free_tree
		}
		rl_clear_history();
	}

}