#include "../../includes/minishell.h"
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/types.h>

void	exec_tree(t_cmd *tree, t_data *ms_data)
{
	t_exec	*exec_cmd;
	char	*executable;
	t_redir	*redir_cmd;
	t_pipe	*pipe_cmd;
	int		pipe_fd[2];
	pid_t	pid;
	struct stat file_stat;

	if (tree->type == EXEC)
	{
		exec_cmd = (t_exec *)tree;
		if (search_builtin(exec_cmd->argv[0]))
		{
			ft_exec_builtin(exec_cmd->argv, ms_data);
			exit(ms_data->return_code);
		}
		if (exec_cmd->argv[0][0] == '.' || exec_cmd->argv[0][0] == '/')
			executable = strdup(exec_cmd->argv[0]);
		else
			executable = find_executable(exec_cmd->argv[0], ms_data);
		if (executable)
		{
			if (stat(executable, &file_stat) == 0 && (file_stat.st_mode & S_IFMT) == S_IFDIR)  // Check if the file is a directory
			{
				print_exec_error("Is a directory", executable);
				ms_data->return_code = 126;
				free(executable);
				exit(ms_data->return_code);
			}
			execve(executable, exec_cmd->argv, ms_data->variables);
			handle_path_errors(executable, ms_data);
	       		free(executable);
			exit(ms_data->return_code);
		}
		else
		{
			print_exec_error("command not found", exec_cmd->argv[0]);
			ms_data->return_code = 127;
			exit(ms_data->return_code);
		}
	}
	else if (tree->type == REDI)
	{
		redir_cmd = (t_redir *)tree;
		int fd;
		fd = open(redir_cmd->file,  redir_cmd->mode, 0644);
		if (fd == -1)
		{
			handle_path_errors(redir_cmd->file, ms_data);
			exit(ms_data->return_code);
		}
		if (dup2(fd, redir_cmd->fd) == -1)
		{
			print_exec_error(strerror(errno), "dup2");  //! ERROR MESSAGE
			exit(ms_data->return_code);  //! ERROR MESSAGE
		}
		close(fd);
		exec_tree(redir_cmd->cmd, ms_data);
	}
	else if (tree->type == PIPE)
	{
	       	pipe_cmd = (t_pipe *)tree;
	       	if (pipe(pipe_fd) == -1)  // Create a pipe
	       	{
	       		print_exec_error(strerror(errno), "pipe");  //! HANDLE ERROR
	       		exit(1);  //! HANDLE ERROR - 1 is a generic error code
	       	}
	       	pid = fork();
	       	if (pid == -1)  // Error handling for fork
	       	{
	       		print_exec_error(strerror(errno), "fork");  //! HANDLE ERROR
	       		exit(1);  //! HANDLE ERROR - 1 is a generic error code
	       	}
	       	if (pid == 0)  // Child process
	       	{
	       		close(pipe_fd[0]);  // Close the read end of the pipe
			if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)  // Redirect the standard output to the write end of the pipe
			{
				print_exec_error(strerror(errno), "dup2");  //! HANDLE ERROR
				exit(1);  //! HANDLE ERROR - 1 is a generic error code
			}
			close(pipe_fd[1]);  // Close the write end of the pipe
			exec_tree(pipe_cmd->left, ms_data);  // Execute the command on the left side of the pipe
			exit(ms_data->return_code);  // Ensure the child process exits after executing the command
		}
		else  // Parent process
		{
			close(pipe_fd[1]);  // Close the write end of the pipe
			if (dup2(pipe_fd[0], STDIN_FILENO) == -1)  // Redirect the standard input to the read end of the pipe
			{
				print_exec_error(strerror(errno), "dup2");  //! HANDLE ERROR
				exit(1);  //! HANDLE ERROR - 1 is a generic error code
			}
			close(pipe_fd[0]);  // Close the read end of the pipe
			waitpid(pid, NULL, 0);  // Wait for the child process to finish
			exec_tree(pipe_cmd->right, ms_data);  // Execute the command on the right side of the pipe
	       	}
	}
}

char	*find_executable(char *command, t_data *ms_data)  // Find the executable file in the PATH variable
{
	char	*path_env;
	char	*path;
	char	*dir;
	char	full_path[PATH_MAX];

	path_env = my_getenv("PATH", ms_data->variables);  // Get the PATH variable
	if (!path_env)
	{
		return (ft_strdup(command));  // Return the command if the PATH variable is not set
	}
    	path = ft_strdup(path_env);  // Copy the PATH variable to avoid modifying the original environment variable
/* 	if (!path)  //! COMENTADO PORQUE ACHO QUE NAO PRECISO DESTA VERIFICACAO.
	{
		print_exec_error("Something went wrong within the ft_strdup function. Malloc related", command);  //! HANDLE ERROR
        	exit(1);  //! HANDLE ERROR - 1 is a generic error code
	} */
	dir = strtok(path, ":");  // Split the PATH variable by ":"
	while (dir)
	{
        	full_path[0] = '\0';  // Initialize the full path
        	strcpy(full_path, dir);  // Copy the directory to the full path
        	strcat(full_path, "/");  // Add a "/" to the full path
        	strcat(full_path, command);  // Add the command to the full path
        	if (access(full_path, X_OK) == 0)  // Check if the file is executable
        	{
        		free(path);
			return strdup(full_path);  // Return the full path of the executable ; NULL if not found
        	}
		dir = strtok(NULL, ":");  // Move to the next directory
	}
	free(path);
	return (NULL);  // Return NULL if the executable is not found -> //! HANDLE ERROR
}

