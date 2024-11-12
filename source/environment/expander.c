#include "../../includes/minishell.h"

char	**expand_environment(char **envp, char *var, t_data *ms_data)
{
	char **new_envp;
	int i;
	int j;

	i = 0;
	j = 0;
	if (!var)
	{
		print_exec_error("Variable is NULL. Malloc related", var);
		ms_data->return_code = 1;
		return (NULL);
	}
	if (!envp)
	{
		print_exec_error("Environment is NULL. Malloc related", var);
		ms_data->return_code = 1;
		return (NULL);
	}
	
	while (envp[i])
		i++;
	new_envp = malloc((i + 2) * sizeof(char *));
	if (!new_envp)
	{
		print_exec_error("Something went wrong within the malloc function. Malloc related", var);
		ms_data->return_code = 1;
		return (NULL);
	}
	i = 0;
	while (envp[i] != NULL)
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (!new_envp[i])
		{
			print_exec_error("Something went wrong within the ft_strdup function. Malloc related", var);
			ms_data->return_code = 1;
			return (NULL);
		}
		i++;
	}
	while (envp[j])
	{
		free(envp[j]);
		j++;
	}
	free(envp);
	printf("|var:%s|\n", var);  //? Debugging statement
	printf("%d\n", i);  //? Debugging statement
	new_envp[i] = ft_strdup(var);
	if (!new_envp[i])
	{
		print_exec_error("Something went wrong within the ft_strdup function. Malloc related", var);
		ms_data->return_code = 1;
		return (NULL);
	}
	i++;
	new_envp[i] = NULL;
	return (new_envp);
}

void	add_variable(char **envp, const char *var)
{
	int	count;

	count = 0;
	while (envp[count])  // Count the number of variables in the environment
		count++;
	printf("Adding variable: %s\n", var);  // Debugging statement
	printf("Number of variables: %d\n", count);  // Debugging statement
	envp[count] = ft_strdup(var);  // Add the new variable to the environment
	if (!envp[count])  // Check if the variable was added successfully
	{
		perror("strdup");
		exit(EXIT_FAILURE);
	}
	printf("Variable added: %s\n", envp[count]);  // Debugging statement
	count = 0;
	while (envp[count])
	{
		count++;
	}
	printf("Number of variables after adding: %d\n", count);  // Debugging statement
	envp[count + 1] = NULL;  // Set the last element of the environment to NULL
}
