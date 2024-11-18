#include "../../includes/minishell.h"


char	**reduce_environment(char **envp, char *var, t_data *ms_data)
{
	int	index;
	char	**new_envp;
	int	i;
	int	j;
	int	len;

	index = find_variable(envp, var);
	if (index == -1)
	{
		print_exec_error("Variable not found", var);
		ms_data->return_code = 1;
		return (NULL);
	}

	len = 0;
	while (envp[len])
		len++;
	
	new_envp = malloc((len) * sizeof(char *));
	if (!new_envp)
	{
		print_exec_error("Malloc failed", var);
		ms_data->return_code = 1;
		return (NULL);
	}

	i = 0;
	j = 0;
	while (i < (len - 1))
	{
		if (i != index)
		{
			new_envp[j] = ft_strdup(envp[i]);
			if (!new_envp[j])
			{
				perror("strdup");
				while (j >= 0)
				{
					free(new_envp[j]);
					j--;
				}
				free(new_envp);
				ms_data->return_code = 1;
				return (NULL);
			}
			j++;
		}
		i++;
	}
	new_envp[j] = NULL;
	
	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
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
