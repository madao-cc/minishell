#include "../../includes/minishell.h"

void	handle_exit(char **argv, t_data *ms_data)
{
	if (argv[1])
	{
		print_exec_error("too many arguments", "exit");
		ms_data->return_code = 2; //! HANDLE ERROR - 2 for too many arguments
		return ;
	}
	clean_minishell(ms_data);
	exit(EXIT_SUCCESS);
}