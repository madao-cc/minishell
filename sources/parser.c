#include "minishell.h"
#include "../libft/libft.h"

static char *heredoc_input(char *delimiter);

static void	print_exec(t_cmd *node)
{
	t_exec	*exec_node;
	char	**argv;
	int		i;

	exec_node = (t_exec *)node;
	argv = exec_node->argv;
	i = 0;
	while (argv[i] != NULL)
	{
		printf(" %s", argv[i]);
		i++;
	}
}

static void	print_redir(t_cmd *node)
{
	t_redir	*redir_node;

	redir_node = (t_redir *)node;
	if (redir_node->fd == 0)
		printf(" < %s", redir_node->file);
	if (redir_node->fd == 1)
		printf(" > %s", redir_node->file);
	print_tree(redir_node->cmd);
}

static void	print_pipe(t_cmd *node)
{
	t_pipe	*pipe_node;

	pipe_node = (t_pipe *)node;
	print_tree(pipe_node->left);
	printf(" |");
	print_tree(pipe_node->right);
}

void	print_tree(t_cmd *node)
{
	if (node->type == PIPE)
		print_pipe(node);
	else if (node->type == REDI)
		print_redir(node);
	else if (node->type == EXEC)
		print_exec(node);
}

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


	/* // TESTING
	printf("Creating redir_node:\n");  //! TESTING
	printf("file: %s\n", file);  //! TESTING
	printf("mode: %d\n", mode);  //! TESTING
	printf("fd: %d\n", fd);  //! TESTING */


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
	return (*str && ft_strchr(tokens, *str));  // RETURN 1 IF TRUE, 0 IF FALSE ('\0')
}

/*

FUNÇÃO PARA LER COMANDOS E OPÇÕES, TENDO EM CONTA " E '

*/

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
	{
		// -------------------------------
		// ADICIONAR FUNÇÃO PARA LER " E '
		// -------------------------------
		*token = TOKEN_TEXT;
		while (str != NULL && !ft_strchr(MS_SPACE, *str) && \
		!ft_strchr(MS_TOKENS, *str))
			str++;
	}
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
	char	*herodic_file;

	while (look_token(cmdline, "<>"))
	{
		token = parse_token(cmdline, 0, 0);
		if (parse_token(cmdline, &stoken, &etoken) != TOKEN_TEXT)
			token = 0; // ERROR MISSING FILE
		stoken = substr(stoken, etoken);
		if (!stoken)
			stoken = NULL; // ERROR NO SUBSTRING
		
		/* //! Debugging statements
		printf("Parsing redirection:\n");
		printf("  token: %d\n", token);
		printf("  stoken: %s\n", stoken); */


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
			//free(herodic_file); //! NAO SEI SE É SUPOSTO
		}
		else if (token == TOKEN_APPE)
			node = seq_redir(node, stoken, O_WRONLY | O_APPEND | O_CREAT, 1);
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
		stoken = substr(stoken, etoken);
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
		cmdline = NULL; // ERROR CHARACTERS LEFT...
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
