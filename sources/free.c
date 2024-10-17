#include "minishell.h"

void	free_tree(t_cmd *tree)
{
    if (tree->type == EXEC)
    {
        t_exec *exec_cmd = (t_exec *)tree;
        // Free any dynamically allocated members of exec_cmd if necessary
        free(exec_cmd);
    }
    else if (tree->type == REDI)
    {
        t_redir *redir_cmd = (t_redir *)tree;
        free_tree(redir_cmd->cmd);
        free(redir_cmd->file);
        free(redir_cmd);
    }
    else if (tree->type == PIPE)
    {
        t_pipe *pipe_cmd = (t_pipe *)tree;
        free_tree(pipe_cmd->left);
        free_tree(pipe_cmd->right);
        free(pipe_cmd);
    }
}
