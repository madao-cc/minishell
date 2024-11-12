#include "../../includes/minishell.h"

void	handle_export(char **argv, t_data *ms_data)
{
	int	i;
	char *name;

	i = 1;
	while (argv[i])
	{
		if (ft_strchr(argv[i], '='))
		{
			name = ft_strndup(argv[i], ft_strchr(argv[i], '=') - argv[i]);
			printf("name: %s\n", name);
			if (!name)
			{
				print_exec_error("Something went wrong within the ft_strndup function. Malloc related", argv[i]);
				ms_data->return_code = 1;
				return ;
			}
			if (is_variable_name_ok(name) == 0 || argv[i][0] == '=')
			{
				print_exec_error("Invalid variable name", name);
				ms_data->return_code = 1;
				free(name);
				return ;
			}
			if (find_variable(ms_data->variables, name) != -1)
			{
				ms_data->variables = reduce_environment(ms_data->variables, name, ms_data);
			}
			ms_data->variables = expand_environment(ms_data->variables, argv[i], ms_data);  // OK! Fully checked
		}
		i++;
	}
	free(name);
	ms_data->return_code = 0;
}
