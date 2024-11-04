#include "../../includes/minishell.h"

char **copy_environment(char **envp)
{
	int		i;
	char	**new_envp;

	i = 0;
	while (envp[i])
		i++;
	new_envp = malloc(MAX_ENV * sizeof(char *));
	if (!new_envp)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (envp[i])
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (!new_envp[i])
		{
			perror("strdup");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	new_envp[i] = NULL;
	return (new_envp);
}
