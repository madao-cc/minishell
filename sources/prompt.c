#include "minishell.h"

char	*ft_prepare_prompt(void)
{
	char	cwd[PATH_MAX];
	char	*prompt;
	char	*color_prefix = "\033[1;35m";
	char	*color_cwd = "\033[1;36m";
	char	*color_reset = "\033[0m";
	size_t	len;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd");
		exit(EXIT_FAILURE);
	}
	len = strlen(color_prefix) + strlen(cwd) + strlen(color_cwd) + strlen("minishel-") + strlen(color_reset) + strlen("> ") + 1;
	prompt = malloc(len);
	if (prompt == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	strcpy(prompt, color_prefix);
	strcat(prompt, "minishel\033[0m-");
	strcat(prompt, color_cwd);
	strcat(prompt, cwd);
	strcat(prompt, color_reset);
	strcat(prompt, "> ");
	return (prompt);
}

char	*ft_trim(char *str)
{
	char	*start;
	char	*end;
	char	*trimmed;
	size_t	len;

	start = str;
	while (*start == ' ' || *start == '\t')
		start++;
	end = start;
	while (*end)
		end++;
	while (end > start && (*(end - 1) == ' ' || *(end - 1) == '\t'))
		end--;
	len = end - start;
	trimmed = malloc(len + 1);
	if (trimmed == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	memcpy(trimmed, start, len);
	trimmed[len] = '\0';
	free(str);
	return (trimmed);
}