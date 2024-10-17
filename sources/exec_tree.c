#include "minishell.h"
#include <unistd.h>
#include <string.h>
#include <errno.h>

char	*find_executable(char *command)  // Find the executable file in the PATH variable
{
	char	*path_env;
	char	*path;
	char	*dir;
	char	full_path[PATH_MAX];
	
	path_env = getenv("PATH");  // Get the PATH variable
	if (!path_env)
        	return NULL;
	path = ft_strdup(path_env);  // Copy the PATH variable to avoid modifying the original environment variable
	if (!path)
	{
		perror("strdup");  //! HANDLE ERROR
        	exit(EXIT_FAILURE);  //! HANDLE ERROR
	}
	/* printf("PATH: %s\n", path); */
	dir = ft_strtok(path, ":");  // Split the PATH variable by ":"
	while (dir)
	{
		full_path[0] = '\0';  // Initialize the full path
		ft_strcpy(full_path, dir);  // Copy the directory to the full path
		ft_strcat(full_path, "/");  // Add a "/" to the full path
		ft_strcat(full_path, command);  // Add the command to the full path
		/* printf("Checking: %s\n", full_path); */
        	if (access(full_path, X_OK) == 0)  // Check if the file is executable
		{
			free(path);
        		return ft_strdup(full_path);  // Return the full path of the executable ; NULL if not found
        	}
		dir = ft_strtok(NULL, ":");  // Move to the next directory
	}
	free(path);
	return NULL;  // Return NULL if the executable is not found -> //! HANDLE ERROR
}

void	exec_tree(t_cmd *tree)
{
	t_exec	*exec_cmd;
	char	*executable;
	t_redir	*redir_cmd;
	int	fd;
	t_pipe	*pipe_cmd;
	int	pipe_fd[2];

	if (tree->type == EXEC)
	{
		exec_cmd = (t_exec *)tree;
		executable = find_executable(exec_cmd->argv[0]);
		if (!executable)  // if find_executable returns NULL
		{
        		fprintf(stderr, "Command not found: %s\n", exec_cmd->argv[0]);  //! HANDLE ERROR -> Obsidian for error handling
        		exit(EXIT_FAILURE);  //! HANDLE ERROR
        	}
		execve(executable, exec_cmd->argv, NULL);  // Execute the command
        	perror("execve");  //! if execve fails, print the error message -> HANDLE ERROR
        	exit(EXIT_FAILURE);  //! HANDLE ERROR
	}
	else if (tree->type == REDI)
	{
        	redir_cmd = (t_redir *)tree;
		//printf("Opening file: %s\n", redir_cmd->file);  // Debugging statement
        	fd = open(redir_cmd->file, redir_cmd->mode, 0644);  // Read/Write for the owner, Read-only for others
        	if (fd == -1)  // Open the file
		{
        		perror("open");  //! HANDLE ERROR
			//printf("Failed to open file: %s\n", redir_cmd->file);  // Debugging information
        		exit(EXIT_FAILURE);  //! HANDLE ERROR
		}
        	if (dup2(fd, redir_cmd->fd) == -1)  // Redirect the file descriptor. If it fails, print the error message
		{
        		perror("dup2");  //! HANDLE ERROR
        		exit(EXIT_FAILURE);  //! HANDLE ERROR
        	}
        	close(fd);
        	exec_tree(redir_cmd->cmd);  // Recursively execute the command
	}
	else if (tree->type == PIPE)
	{
        	pipe_cmd = (t_pipe *)tree;
        	if (pipe(pipe_fd) == -1)  // Create a pipe
		{
        		perror("pipe");  //! HANDLE ERROR
        		exit(EXIT_FAILURE);  //! HANDLE ERROR
		}
        	if (fork() == 0)  // Create a child process
		{
        		close(pipe_fd[0]);  // Close the read end of the pipe
        		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)  // Redirect the standard output to the write end of the pipe
			{
                		perror("dup2");  //! HANDLE ERROR
                		exit(EXIT_FAILURE);  //! HANDLE ERROR
        		}
        		close(pipe_fd[1]);  // Close the write end of the pipe
        		exec_tree(pipe_cmd->left);  // Execute the command on the left side of the pipe
        	} 
		else  // Parent process
		{
        		close(pipe_fd[1]);  // Close the write end of the pipe
        		if (dup2(pipe_fd[0], STDIN_FILENO) == -1)  // Redirect the standard input to the read end of the pipe
			{
        			perror("dup2");  //! HANDLE ERROR
               		 	exit(EXIT_FAILURE);  //! HANDLE ERROR
        		}
        		close(pipe_fd[0]);  // Close the read end of the pipe
        		exec_tree(pipe_cmd->right);  // Execute the command on the right side of the pipe
       		}
	}
}