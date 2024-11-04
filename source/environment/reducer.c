#include "../../includes/minishell.h"


char	**reduce_environment(char **envp, char *var, t_data *ms_data)
{
	int	index;
	char	**new_envp;
	int	i;
	int	j;

	index = find_variable(envp, var);
	i = 0;
	j = 0;
	while (envp[i])
		i++;
	new_envp = malloc((i - 1) * sizeof(char *));
	if (!new_envp)
	{
		print_exec_error("Something went wrong within the malloc function. Malloc related", var);
		ms_data->return_code = 1;
		return (NULL);
	}
	i = 0;
	while (i != index)
	{
		new_envp[j] = ft_strdup(envp[i]);
		if (!new_envp[j])
		{
			perror("strdup");
			return (NULL);
		}
		i++;
		j++;
	}
	free(envp[index]);
	while (envp[i + 1])
	{
		new_envp[j] = ft_strdup(envp[i + 1]);
		if (!new_envp[j])
		{
			print_exec_error("Something went wrong within the ft_strdup function. Malloc related", var);
			ms_data->return_code = 1;
			return (NULL);
		}
		i++;
		j++;
	}
	new_envp[j] = NULL;
	free(envp);
	return (new_envp);
}

void	remove_variable(char **envp, const char *var)
{
	int	i;
	int	found;

	i = 0;
	found = -1;
	while (envp[i])  // Loop through the environment
	{
		if (strncmp(envp[i], var, strlen(var)) == 0 && envp[i][strlen(var)] == '=')
		{
			found = i;
			break ;
		}
		i++;
	}
	if (found != -1)  // Check if the variable was found
		free(envp[found]);  // Free the memory allocated for the variable
	while (envp[found])  // Shift the elements of the environment to remove the variable
	{
		envp[found] = envp[found + 1];
		found++;
	}
}
