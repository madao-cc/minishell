#include "../../includes/minishell.h"

void	ft_exec_builtin(char **argv, t_data *ms_data)
{
	char 	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		print_exec_error("getcwd failed", "ft_exec_builtin");
		ms_data->return_code = 1;
		return ;
	}
	if (strcmp(argv[0], "export") == 0)
	{
		if (argv[1] == NULL)
		{
			export_env(ms_data);
			free(pwd);
			return ;
		}
		handle_export(argv, ms_data);
	}
	else if (strcmp(argv[0], "unset") == 0)
	{
		handle_unset(argv, ms_data);
		free(pwd);
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
		handle_cd(ms_data, argv);
		update_pwd(pwd, ms_data);
	}
	free(pwd);
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

/* void	update_pwd(char *pwd, t_data *ms_data)
{
	char	*pwd;
	char	*new_pwd;

	pwd = my_getenv("PWD", ms_data->variables);
	if (!pwd)
	{
		print_exec_error("PWD not set", "update_pwd");
		ms_data->return_code = 1;
		return ;
	}
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		print_exec_error("getcwd failed", "update_pwd");
		ms_data->return_code = 1;
		free(pwd);
		return ;
	}
	if (my_getenv("OLDPWD", ms_data->variables) == NULL)
	{
		ms_data->variables = expand_environment(ms_data->variables, ft_strjoin("OLDPWD=", pwd), ms_data);
	}
	else
	{
		ms_data->variables = reduce_environment(ms_data->variables, "OLDPWD", ms_data);
		ms_data->variables = expand_environment(ms_data->variables, ft_strjoin("OLDPWD=", pwd), ms_data);
	}
	ms_data->variables = expand_environment(ms_data->variables, ft_strjoin("OLDPWD=", pwd), ms_data);
	ms_data->variables = reduce_environment(ms_data->variables, "PWD", ms_data);
	ms_data->variables = expand_environment(ms_data->variables, ft_strjoin("PWD=", new_pwd), ms_data);
	free(pwd);
	free(new_pwd);
	ms_data->return_code = 0;
} */