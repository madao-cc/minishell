#include "minishell.h"
#include <signal.h>

static char *heredoc_input(char *delimiter);

// CREATE A SUBSTRING FROM POINTER START TO POINTER END
char	*substr(char *start, char *end)
{
	int		i;
	char	*str;

	str = (char *)malloc((end - start + 1) * sizeof(char));
	if (str)
	{
		i = 0;
		while (start < end)
		{
			str[i] = *start;
			start++;
			i++;
		}
		str[i] = '\0';
	}
	return (str);
}

// CREATE EXECUTION NODE
t_cmd	*exec_node(void)
{
	t_exec	*node;

	node = (t_exec *)malloc(sizeof(*node));
	if (!node)
		return (NULL);
	ft_memset(node, 0, sizeof(*node));
	node->type = EXEC;
	return ((t_cmd *)node);
}

// CREATE REDIRECTION NODE
t_cmd	*redir_node(t_cmd *sub_cmd, char *file, int mode, int fd)
{
	t_redir	*node;

	node = (t_redir *)malloc(sizeof(*node));
	if (!node)
		return (NULL);
	ft_memset(node, 0, sizeof(*node));
	node->type = REDI;
	node->cmd = sub_cmd;
	node->file = file;
	node->mode = mode;
	node->fd = fd;
	return ((t_cmd *)node);
}

// CREATE PIPE NODE
t_cmd	*pipe_node(t_cmd *left, t_cmd *right)
{
	t_pipe	*node;

	node = (t_pipe *)malloc(sizeof(*node));
	if (!node)
		return (NULL);
	ft_memset(node, 0, sizeof(*node));
	node->type = PIPE;
	node->left = left;
	node->right = right;
	return ((t_cmd *)node);
}

// CHECK IF NEXT CHARACTER IS ONE OF THE TOKEN SYMBOLS
int	look_token(char **cmdline, char *tokens)
{
	char	*str;

	str = *cmdline;
	while (*str != '\0' && ft_strchr(MS_SPACE, *str))
		str++;
	*cmdline = str;
	return (*str && ft_strchr(tokens, *str));
}

static char	*parse_text(char *str, int *token)
{
	char	quote;

	*token = TOKEN_TEXT;
	while (*str != '\0' && !ft_strchr(MS_SPACE, *str) && \
	!ft_strchr(MS_TOKENS, *str))
	{
		if (ft_strchr(MS_QUOTES, *str))
		{
			quote = *str;
			str++;
			while (*str != quote)
			{
				if (*str == '\0')
					break ;
				//ERROR UNCLOSED QUOTATIONS;
				str++;
			}
			if (*str != '\0')
				str++;
		}
		else
			str++;
	}
	return (str);
}

// SET TOKEN
static char	*set_token(char *str, int *token, int token_symbol)
{
	*token = token_symbol;
	str++;
	return (str);
}

// GET TOKEN
static char	*get_token(char *str, int *token)
{
	if (*str == '\0')
		*token = 0;
	else if (*str == '|')
		str = set_token(str, token, TOKEN_PIPE);
	else if (*str == '<')
	{
		str = set_token(str, token, TOKEN_INPU);
		if (*str == '<')
			str = set_token(str, token, TOKEN_DELI);
	}
	else if (*str == '>')
	{
		str = set_token(str, token, TOKEN_OUTP);
		if (*str == '>')
			str = set_token(str, token, TOKEN_APPE);
	}
	else
		str = parse_text(str, token);
	return (str);
}

// PARSE NEXT TOKEN IN INPUT LINE
int	parse_token(char **cmdline, char **stoken, char **etoken)
{
	char	*str;
	int		token;

	str = *cmdline;
	while (*str != '\0' && ft_strchr(MS_SPACE, *str))
		str++;
	if (stoken)
		*stoken = str;
	str = get_token(str, &token);
	if (etoken)
		*etoken = str;
	while (*str != '\0' && ft_strchr(MS_SPACE, *str))
		str++;
	*cmdline = str;
	return (token);
}

// GET VARIABLE NAME
static char	*getvarname(char *str, char *end, char *var_name)
{
	int		i;

	i = 0;
	while (str != end && ft_strchr(MS_VAR_CHAR, *str))
	{
		var_name[i] = *str;
		str++;
		i++;
	}
	var_name[i] = '\0';
	return (str);
}

// EXPAND VARIABLE
char	*expand_var(char *str, char *end, char **sub_start, char **sub_end)
{
	char	var_name[VAR_BUFFER];
	char	*var;

	str++;
	if (*str == '?')
		printf("RETURN CODE\n"); // RETURN CODE
	str = getvarname(str, end, (char *)var_name);
	if (var_name[0] == '\0')
	{
		*sub_end = str;
		*sub_start = str - 1;
		return (str);
	}
	var = getenv(var_name);
	if (var)
	{
		*sub_start = var;
		*sub_end = *sub_start + ft_strlen(*sub_start);
	}
	return (str);
}

// ADD TEXT IN SINGLE QUOTES
static char	*add_single_quotes(char *str, char *end, \
char **sub_start, char **sub_end)
{
	str++;
	*sub_start = str;
	while (str != end && *str != '\'')
		str++;
	*sub_end = str;
	return (str);
}

//  ADD PLAIN TEXT
static char	*add_text(char *str, char *end, char **sub_start, char **sub_end)
{
	*sub_start = str;
	while (str != end && *str != '$' && !ft_strchr(MS_QUOTES, *str))
		str++;
	*sub_end = str;
	return (str);
}

// CONCATENATE STRINGS 
static char	*concat_str(char *str, char *sub_start, char *sub_end)
{
	char	*str2;
	char	*str3;

	str2 = substr(sub_start, sub_end);
	if (!str)
		return (str2);
	str3 = ft_strjoin(str, str2);
	free(str);
	free(str2);
	return (str3);
}

// CREATE A SUBSTRING FROM POINTER START TO POINTER END, REMOVING " AND '
// AND EXPANDING VARIABLES
char	*substr_expans(char *start, char *end)
{
	char	*sub_start;
	char	*sub_end;
	char	*str;

	str = NULL;
	while (start < end)
	{
		sub_start = NULL;
		sub_end = NULL;
		if (*start == '$')
			start = expand_var(start, end, &sub_start, &sub_end);
		else if (*start == '"')
			start++;
		else if (*start == '\'')
			start = add_single_quotes(start, end, &sub_start, &sub_end);
		else
			start = add_text(start, end, &sub_start, &sub_end);
		if (sub_start && sub_end)
			str = concat_str(str, sub_start, sub_end);
	}
	return (str);
}

// CREATE NEW REDIRECTION NODE IN SEQUENTIAL ORDER
static t_cmd	*seq_redir(t_cmd *node, char *file, int mode, int fd)
{
	t_redir	*node0;
	t_cmd	*node1;

	if (node->type == EXEC)
		node = redir_node(node, file, mode, fd);
	else
	{
		node0 = (t_redir *)node;
		while (node0->cmd->type != EXEC)
			node0 = (t_redir *)(node0->cmd);
		node1 = redir_node(node0->cmd, file, mode, fd);
		node0->cmd = node1;
	}
	return (node);
}

// PARSE REDIRECTION
static t_cmd	*parse_redir(t_cmd *node, char **cmdline)
{
	int		token;
	char	*stoken;
	char	*etoken;
	char *herodic_file;

	while (look_token(cmdline, "<>"))
	{
		token = parse_token(cmdline, 0, 0);
		if (parse_token(cmdline, &stoken, &etoken) != TOKEN_TEXT)
			token = 0; // ERROR MISSING FILE
		stoken = substr_expans(stoken, etoken);
		if (!stoken)
			stoken = NULL; // ERROR NO SUBSTRING
		if (token == TOKEN_INPU)
			node = seq_redir(node, stoken, O_RDONLY, 0);
		else if (token == TOKEN_OUTP)
			node = seq_redir(node, stoken, O_WRONLY | O_TRUNC | O_CREAT, 1);
		else if (token == TOKEN_DELI)
		{
			herodic_file = heredoc_input(stoken);
			if (!herodic_file)
			{
				free(herodic_file);  //! NAO SEI SE É SUPOSTO
				return NULL; //! NAO SEI SE ESTA CORRETO
			}
			node = seq_redir(node, herodic_file, O_RDONLY, 0);
			//free(herodic_file); //! NAO É SUPOSTO
		}
		else if (token == TOKEN_APPE)
			node = seq_redir(node, stoken, O_WRONLY | O_CREAT, 1);
	}
	return (node);
}

// FILL DATA IN EXECUTION NODE + LOOK FOR REDIRECTIONS AFTER COMMAND
static void	fill_exec_node(char **cmdline, t_exec *exec, t_cmd **node)
{
	int		argc;
	int		token;
	char	*stoken;
	char	*etoken;

	argc = 0;
	while (!look_token(cmdline, "|"))
	{
		token = parse_token(cmdline, &stoken, &etoken);
		if (token == 0)
			break ;
		if (token != TOKEN_TEXT)
			token = 0; // ERROR SYNTAX
		stoken = substr_expans(stoken, etoken);
		if (!stoken)
			stoken = NULL; // ERROR NO SUBSTRING
		exec->argv[argc] = stoken;
		argc++;
		if (argc >= MAXARGS)
			argc = 0; // ALTERAR LIMITE DE OPÇÕES
		*node = parse_redir(*node, cmdline);
	}
}

// PARSE EXECUTION
static t_cmd	*parse_exec(char **cmdline)
{
	t_cmd	*node;
	t_exec	*exec;

	node = exec_node();
	exec = (t_exec *)node;
	node = parse_redir(node, cmdline);
	fill_exec_node(cmdline, exec, &node);
	return (node);
}

// PARSE PIPE
t_cmd	*parse_pipe(char **cmdline)
{
	t_cmd	*node;

	node = parse_exec(cmdline);
	if (look_token(cmdline, "|"))
	{
		parse_token(cmdline, 0, 0);
		node = pipe_node(node, parse_pipe(cmdline));
	}
	return (node);
}

// MAIN PARSING FUNCTION
t_cmd	*parse_tree(char *cmdline)
{
	t_cmd	*node;

	node = parse_pipe(&cmdline);
	look_token(&cmdline, "");
	if (*cmdline != '\0')
		printf("CHARACTERS LEFT\n"); // ERROR CHARACTERS LEFT...
	return (node);
}

// FUNCTION TO HANDLE HEREDOC INPUT
static char *heredoc_input(char *delimiter)
{
	char	*line;
	char	tmp_filename[256];
	int		pid;
	int		tmp_fd;
	int		i;
	int		j;
	char tmp;

	// CREATE TEMP FILE
	ft_strcpy(tmp_filename, "/tmp/heredoc_tmp");
	pid = getpid();
	printf("PID: %d\n", pid);  //! TESTING
	i = 0;
	while (pid > 0)
	{
		tmp_filename[14 + i] = pid % 10 + '0';
		pid /= 10;
		i++;
	}
	tmp_filename[14 + i] = '\0';
	// Reverse the PID part of the filename
	j = 0;
	while (j < i / 2)
	{
		tmp = tmp_filename[14 + j];
		tmp_filename[14 + j] = tmp_filename[14 + i - j - 1];
		tmp_filename[14 + i - j - 1] = tmp;
		j++;
	}
	ft_strcat(tmp_filename, ".tmp");
	printf("Filename: %s\n", tmp_filename);  //! TESTING
	tmp_fd = open(tmp_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (tmp_fd == -1)
	{
		perror("open");
		printf("Failed to open file: %s\n", tmp_filename);  // Debugging information
		return NULL;
	}
	while (1)
	{
		if (g_signal_received)
		{
			close(tmp_fd);
        		unlink(tmp_filename);
        		return NULL;
		}
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			if (line)
				free(line);
			break ;
		}
		write(tmp_fd, line, ft_strlen(line));
		write(tmp_fd, "\n", 1);
		if (line)
			free(line);
	}
	close(tmp_fd);
	return (ft_strdup(tmp_filename));
}