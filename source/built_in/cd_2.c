/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikelitoris <mikelitoris@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:51:52 by mikelitoris       #+#    #+#             */
/*   Updated: 2024/11/19 17:24:32 by mikelitoris      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_relative_path(char *line, t_data *ms_data)
{
	char	*path;
	char	*original_path;

	original_path = get_original_path();
	path = ft_strsep(&line, "/");
	while (path != NULL)
	{
		if (ft_strcmp(path, "~") == 0)
		{
			if (handle_home(ms_data) == 1)
			{
				return(cleaner_original_path(original_path));
			}
			
		}
		else if (ft_strcmp(path, "") != 0)
		{
			if (relative_path_helper(path, ms_data) == 1)
			{
				return(cleaner_original_path(original_path));
			}
		}
		path = ft_strsep(&line, "/");
	}
	free(original_path);
	return (0);
}

int	relative_path_helper(char *path, t_data *ms_data)
{
	if (ft_strcmp(path, ".") == 0)
	{
		if (chdir(".") == -1)
		{
			prepare_cd_error("cd", path, ms_data, 1, errno);
			return (1);
		}
	}
	else if (ft_strcmp(path, "..") == 0)
	{
		if (chdir("..") == -1)
		{
			prepare_cd_error("cd", path, ms_data, 1, errno);
			return (1);
		}
	}
	else
	{
		if (chdir(path) == -1)
		{
			prepare_cd_error("cd", path, ms_data, 1, errno);
			return (1);
		}
	}
	return (0);
}

char	*get_original_path(void)
{
	char	*original_path;

	original_path = getcwd(NULL, 0);
	if (!original_path)
	{
		perror("getcwd");
		exit(EXIT_FAILURE);
	}
	return (original_path);
}

int	cleaner_original_path(char *original_path)
{
	chdir(original_path);
	free(original_path);
	return (1);
}