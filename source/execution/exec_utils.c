#include "../../includes/minishell.h"

void	ft_exec_builtin(char **argv, t_data *ms_data)
{
	if (strcmp(argv[0], "export") == 0)
	{
		if (argv[1] == NULL)
		{
			export_env(ms_data);
			return ;
		}
		handle_export(argv, ms_data);
	}
	else if (strcmp(argv[0], "unset") == 0)
	{
		handle_unset(argv, ms_data);
		return ;
	}
	else if (strcmp(argv[0], "env") == 0)
	{
		handle_env(argv, ms_data);
	}
	else if (strcmp(argv[0], "exit") == 0)
	{
		handle_exit(argv, ms_data);
	}
	else if (strcmp(argv[0], "pwd") == 0)
	{
		handle_pwd(argv, ms_data);
	}
	else if (strcmp(argv[0], "echo") == 0)
	{
		handle_echo(argv);
	}
	else if (strcmp(argv[0], "cd") == 0)
	{
		handle_cd(ms_data);
	}
	else
	{
		print_test();
		printf("NO BUILTIN WAS FOUND...\n");
		print_test();
	}
}

void	export_env(t_data *ms_data)
{
	char *name;
	char *value;
	char **variables;
	int i;
	
	i = 0;
	variables = ms_data->variables;
	while (variables[i] != NULL)
	{
		name = ft_strndup(variables[i], ft_strchr(variables[i], '=') - variables[i]);
		value = ft_strchr(variables[i], '=') + 1;
		printf("declare -x %s=\"%s\"\n", name, value);
		i++;
	}
	ms_data->return_code = 0;
}

void	print_test(void)
{
	printf("\n");
	printf("-----------------------\n");
	printf("\n");
}
