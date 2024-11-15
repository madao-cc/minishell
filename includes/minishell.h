/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikelitoris <mikelitoris@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:00:13 by antfonse          #+#    #+#             */
/*   Updated: 2024/11/15 17:55:12 by mikelitoris      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <linux/limits.h>  // For PATH_MAX
# include <fcntl.h>  // For open function
# include <unistd.h>  // For write and read functions
# include <stdio.h>  // For printf
# include <stdlib.h>  // For malloc, free, exit
# include <string.h>  // For strerror
# include <errno.h>  // For errno
# include <sys/types.h>  // For pid_t
# include <sys/wait.h>  // For waitpid
# include <sys/stat.h>  // For stat
# include <signal.h>  // For signal
# include <stdbool.h>  // For bool
# include <dirent.h>  // For opendir
# include <readline/readline.h>  // For readline
# include <readline/history.h>  // For add_history
# include "../LIBFT/src/libft.h"

// ENVIRONMENT
# define MAX_ENV		1024 // Can be changed to 4096

typedef struct s_cmd
{
	int	type;
}		t_cmd;

typedef struct s_exec
{
	int		type;
	char	**argv;
}			t_exec;

typedef struct s_redir
{
	int		type;
	t_cmd	*cmd;
	char	*file;
	int		mode;
	int		fd;
}			t_redir;

typedef struct s_pipe
{
	int		type;
	t_cmd	*left;
	t_cmd	*right;
}			t_pipe;

// MINISHELL MAIN DATA STRUCT
typedef struct s_data
{
	char	*prompt;
	char	*input;
	t_cmd	*tree;
	int		return_code;
	int		heredoc_count;
	char	**variables;
}			t_data;

// PARSED NODE TYPES
# define EXEC			1
# define REDI			2
# define PIPE			3

// PARSING DICTIONARIES
# define MS_SPACE		" \t\r\n\v"
# define MS_TOKENS		"<|>"
# define MS_QUOTES		"\"\'"
# define MS_VAR_CHAR	"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz\
0123456789_"

// TOKEN SYMBOLS
# define TOKEN_PIPE		'|'
# define TOKEN_INPU		'<'
# define TOKEN_OUTP		'>'
# define TOKEN_DELI		'd'
# define TOKEN_APPE		'a'
# define TOKEN_TEXT		't'
# define TOKEN_EOF		'\0'
# define TOKEN_ERROR	-1

// RETURN CODE SIZE
# define RET_CODE_SIZE	4

// HEREDOC
# define HEREDOC_FOLDER	"/tmp/"
# define HEREDOC_NAME	"heredoc_"
# define HEREDOC_FILE	"/tmp/heredoc_"
# define HEREDOC_EXTEN	".tmp"

// ERROR CODES
# define NO_ERROR		0
# define MALLOC			1
# define SYNTAX			2
# define QUOTE			3
# define ARG_LIMIT		4
# define HEREDOC		5
# define INPUT			6

// ERROR MESSAGES
# define MSG_MINISHELL	"minishell: "
# define MSG_MALLOC		"malloc: Cannot allocate memory"
# define MSG_SYNTAX		"syntax error near unexpected token "
# define MSG_QUOTE		"unexpected EOF while looking for matching "
# define MSG_ARG_LIMIT	": Argument list too long"
# define MSG_HEREDOC	"cannot create temp file for here-document"
# define MSG_INPUT		"readline: Input error"

// INITIALIZE / CLOSE / FREE
t_data	*init_minishell(char **envp);
t_cmd	*free_tree(t_cmd *node);
void	clean_shell(t_data *ms_data);

//INIT_CLOSE_01
void	delete_heredoc(void);
void	delete_variables(char **variables);
void	free_environment(char **envp);



// PARSER - CREATE ABSTRACT SYNTAX TREE
t_cmd	*exec_node(void);
t_cmd	*redir_node(t_cmd *sub_cmd, char *file, int mode, int fd);
t_cmd	*pipe_node(t_cmd *left, t_cmd *right);
void	putnbr_recursive(int nb, char **nb_char);
char	*expand_var(t_data *ms_data, char *start, char *end, char **str);
char	*substr(char *start, char *end);
char	*concat_str(char *str, char *sub_start, char *sub_end);
char	*substr_expans(t_data *ms_data, char *start, char *end);
int		look_token(char **input, char *tokens);
char	*parse_text(char *str, int *token);
int		parse_token(char **input, char **stoken, char **etoken);
int		fill_argv(char *stoken, t_exec *exec);
t_cmd	*heredoc_node(t_data *ms_data, t_cmd *node, char *delimiter);
t_cmd	*seq_redir(t_cmd *node, char *file, int mode, int fd);
t_cmd	*parse_redir(t_data *ms_data, t_cmd *node, char **input);
t_cmd	*parse_pipe(t_data *ms_data, char **input);
t_cmd	*create_tree(t_data *ms_data);
t_cmd	*check_node(t_cmd *node);
char	*check_str(char *str);
char	**check_str_2d(char **str);
int		check_fd(int fd);
char	*check_readline(char *str);
int		check_argv(char **argv, int argc);

// EXECUTION
void	exec_tree(t_cmd *tree, t_data *ms_data);
char	*find_executable(char *command, t_data *ms_data);
void	handle_redirection(t_redir *redir_cmd);  // NOT IN USE

void	ft_exec_builtin(char **argv, t_data *ms_data);
void	export_env(t_data *ms_data);
void	print_test(void);



// BUILT-IN FUNCTIONS
bool	search_builtin(char *command);

void	handle_cd(t_data *ms_data);
void	handle_absolut_path(char *line, t_data *ms_data);
void	handle_home(t_data *ms_data);
int	ft_is_char(char c);
void	handle_dot_cases(char *line, t_data *ms_data);
void	handle_relative_path(char *line, t_data *ms_data);

void	handle_echo(char **argv);
int	str_is_simple(char *str);

void	handle_env(char **argv, t_data *ms_data);

void	handle_exit(char **argv, t_data *ms_data);

void	handle_export(char **argv, t_data *ms_data);

void	handle_pwd(char **argv, t_data *ms_data);

void	handle_unset(char **argv, t_data *ms_data);

// ENVIROMENT
char **copy_environment(char **envp);

char	**expand_environment(char **envp, char *var, t_data *ms_data);
void	add_variable(char **envp, const char *var);

char	**reduce_environment(char **envp, char *var, t_data *ms_data);
void	remove_variable(char **envp, const char *var);

char *my_getenv(char *var_name, char **variables);
int	find_variable(char **envp, const char *name);
char	*ft_strndup(const char *s1, size_t n);
int	is_variable_name_ok(char *name);

// ERROR HANDLING
void	print_error(int error_code, char *error_info);
void	print_syntax_error(int token);

void	print_exec_error(char *error_message, char *command);
void	handle_path_errors(char *path, t_data *ms_data);

// SIGNALS
void handle_signals(t_data *ms_data);
void handle_sigint(int sig);
void handle_eof(int sig);

#endif
