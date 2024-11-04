#include "../../includes/minishell.h"

void	handle_unset(char **argv, t_data *ms_data)
{
	int	i;

	i = 1;
	if (argv[i] == NULL)
	{
		ms_data->return_code = 0;
		return ;
	}
	if (is_variable_name_ok(argv[i]) == 0)
	{
		print_exec_error("Invalid variable name", argv[i]);
		ms_data->return_code = 1;
		return ;
	}
	while (argv[i])
	{
		if (find_variable(ms_data->variables, argv[i]) != -1)
		{
			ms_data->variables = reduce_environment(ms_data->variables, argv[i], ms_data);
		}
		i++;
	}
}
