#include "../../includes/minishell.h"

char **copy_environment(char **envp)
{
	int		i;
	char	**new_envp;

	i = 0;
	while (envp[i])
		i++;
	new_envp = malloc((i + 1) * sizeof(char *));
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
			while (i > 0)
			{
				free(new_envp[i - 1]);
				i--;
			}
			exit(EXIT_FAILURE);
		}
		i++;
	}
	new_envp[i] = NULL;
	return (new_envp);
}
