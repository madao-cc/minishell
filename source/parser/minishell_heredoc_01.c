/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antfonse <antfonse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 01:34:31 by antfonse          #+#    #+#             */
/*   Updated: 2024/11/03 16:34:38 by antfonse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// CREATE FILENAME FOR NEXT HEREDOC FILE
static char	*heredoc_filename(t_data *ms_data)
{
	char	*filename0;
	char	*filename1;
	char	index[RET_CODE_SIZE];
	char	*ptr_index;

	if (ms_data->heredoc_count > 999)
	{
		print_error(HEREDOC, "");
		return (NULL);
	}
	ft_memset(index, 0, RET_CODE_SIZE);
	ptr_index = (char *)index;
	putnbr_recursive(ms_data->heredoc_count, &ptr_index);
	filename0 = check_str(ft_strjoin(HEREDOC_FILE, index));
	if (!filename0)
		return (NULL);
	filename1 = check_str(ft_strjoin(filename0, HEREDOC_EXTEN));
	free(filename0);
	return (filename1);
}

int	write_heredoc(char *delimiter, int fd)
{
	size_t	len;
	char	*line;

	line = check_readline(readline("> "));
	if (!line)
		return (EXIT_FAILURE);
	len = ft_strlen(delimiter);
	while (ft_strncmp(delimiter, line, len) != 0 || ft_strlen(line) != len)
	{
		ft_putendl_fd(line, fd);
		free(line);
		line = check_readline(readline("> "));
		if (!line)
			return (EXIT_FAILURE);
	}
	free(line);
	return (EXIT_SUCCESS);
}

// CREATE HEREDOC FILES AND WRITE IN THEM
static char	*heredoc_file(t_data *ms_data, char *delimiter)
{
	int		fd;
	char	*filename;

	filename = heredoc_filename(ms_data);
	if (!filename)
		return (NULL);
	fd = check_fd(open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0664));
	if (fd == -1)
		return (NULL);
	ms_data->heredoc_count++;
	if (write_heredoc(delimiter, fd) == EXIT_FAILURE)
	{
		free(filename);
		filename = NULL;
	}
	free(delimiter);
	close(fd);
	return (filename);
}

// CREATE HEREDOC REDIRECTION NODE
t_cmd	*heredoc_node(t_data *ms_data, t_cmd *node, char *delimiter)
{
	char	*heredoc_name;

	heredoc_name = heredoc_file(ms_data, delimiter);
	if (!heredoc_name)
		return (free_tree(node));
	node = seq_redir(node, heredoc_name, O_RDONLY, 0);
	return (node);
}
