#include "../../includes/minishell.h"

bool	search_builtin(char *command)
{
	if (!strcmp(command, "echo"))
		return (true);
	if (!strcmp(command, "pwd"))
		return (true);
	if (!strcmp(command, "export"))
		return (true);
	if (!strcmp(command, "unset"))
		return (true);
	if (!strcmp(command, "env"))
		return (true);
	if (!strcmp(command, "exit"))
		return (true);
	if (!strcmp(command, "cd"))
		return (true);
	return (false);
}
