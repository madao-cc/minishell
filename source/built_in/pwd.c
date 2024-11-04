#include "../../includes/minishell.h"

void	handle_pwd(char **argv, t_data *ms_data)
{
	char	*cwd;

	if (argv[1])
	{
		ft_putstr_fd("pwd: too many arguments\n", 2);
		ms_data->return_code = 2;
		return ;
	}
	cwd = getcwd(NULL, 0);
	ft_putstr_fd(cwd, 1);
	ft_putstr_fd("\n", 1);
	free(cwd);
	ms_data->return_code = 0;
}
