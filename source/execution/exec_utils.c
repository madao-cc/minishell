#include "../../includes/minishell.h"

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