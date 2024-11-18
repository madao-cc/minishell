#include "../../includes/minishell.h"

char *my_getenv(char *var_name, char **variables)
{
	int		i;
	int		len;
	char	*var_value;

	i = 0;
	len = ft_strlen(var_name);
	while (variables[i])
	{
		if (ft_strncmp(variables[i], var_name, len) == 0 && variables[i][len] == '=')
		{
			var_value = ft_strdup(variables[i] + len + 1);
			if (!var_value)
			{
				perror("strdup");
				exit(EXIT_FAILURE);
			}
			return (var_value);
		}
		i++;
	}
	return (NULL);
}

int	find_variable(char **envp, const char *name)
{
	size_t	len;
	int		i;

	i = 0;
	len = strlen(name);
	while (envp[i])
	{
		if (strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_strndup(const char *s1, size_t n)
{
	char	*copy;
	size_t	i;

	copy = malloc((n + 1) * sizeof(char));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < n && s1[i])
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

int	is_variable_name_ok(char *name)
{
	int	i;

	i = 0;
	if (ft_isdigit(name[0]) || name[0] == '=')
		return (0);
	while (name[i])
	{
		if (ft_isalnum(name[i]) == 0 && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	update_pwd(char *old_pwd, t_data *ms_data)
{
	char	*new_pwd;
	char	*old_pwd_str;
	char	*new_pwd_str;

	old_pwd_str = NULL;
	new_pwd_str = NULL;
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		print_exec_error(strerror(errno), "getcwd");
		ms_data->return_code = 1;
		return ;
	}
	old_pwd_str = ft_strjoin("OLDPWD=", old_pwd);
	if (find_variable(ms_data->variables, "OLDPWD") == -1)
		ms_data->variables = expand_environment(ms_data->variables, old_pwd_str, ms_data);
	else
	{
		ms_data->variables = reduce_environment(ms_data->variables, "OLDPWD", ms_data);
		ms_data->variables = expand_environment(ms_data->variables, old_pwd_str, ms_data);
	}
	free(old_pwd_str);
	new_pwd_str = ft_strjoin("PWD=", new_pwd);
	if (find_variable(ms_data->variables, "PWD") != -1)
		ms_data->variables = expand_environment(ms_data->variables, new_pwd_str, ms_data);
	else
	{
		ms_data->variables = reduce_environment(ms_data->variables, "OLDPWD", ms_data);
		ms_data->variables = expand_environment(ms_data->variables, new_pwd_str, ms_data);
	}
	free(new_pwd_str);
	free(new_pwd);
	ms_data->return_code = 0;
}