#include "../../includes/minishell.h"

void	handle_unset(char **argv, t_data *ms_data)
{
	int	i;
	/* char	*name; */
	int	index;

	i = 1;
	if (argv[i] == NULL)
	{
		ms_data->return_code = 0;
		return ;
	}

	/* name = strchr(argv[i], '=');
	if (name != NULL)
		*name = '\0';
	printf("name: %s\n", argv[i]); */

	while (argv[i])
	{
		if ((index = find_variable(ms_data->variables, argv[i])) != -1)
		{
			ms_data->variables = reduce_environment(ms_data->variables, argv[i], ms_data);
		}
		i++;
	}
}
