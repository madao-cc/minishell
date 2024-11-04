#include "../../includes/minishell.h"

void	handle_env(char **argv, t_data *ms_data)
{
	int			i;

	i = 0;
	if (argv[1])
	{
		print_exec_error("too many arguments", "env");
		ms_data->return_code = 2;  //! HANDLE ERROR - 2 for too many arguments or 127 for command not found
		return ; //! Dont know if im suppose to exit or return
	}
	while (ms_data->variables[i])
	{
		ft_putstr_fd(ms_data->variables[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
}
