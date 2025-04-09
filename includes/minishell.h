/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madao-da <madao-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 18:45:27 by madao-da          #+#    #+#             */
/*   Updated: 2024/12/08 15:55:22 by madao-da         ###   ########.fr       */
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
# include <sys/ioctl.h>
# include <signal.h>  // For signal
# include <stdbool.h>  // For bool
# include <dirent.h>  // For opendir
# include <readline/readline.h>  // For readline
# include <readline/history.h>  // For add_history
# include "../LIBFT/src/libft.h"
# include <limits.h>
# include <termios.h>

extern int	g_sig_num;

// EXPORT
typedef struct s_var
{
	char	*name;
	char	*value;
}			t_var;

// GENERAL COMMAND STRUCT
typedef struct s_cmd
{
	int	type;
}		t_cmd;

// EXECUTION NODE STRUCT
typedef struct s_exec
{
	int		type;
	char	**argv;
}			t_exec;

// REDIRECTION NODE STRUCT
typedef struct s_redir
{
	int		type;
	t_cmd	*cmd;
	char	*file;
	int		mode;
	int		fd;
}			t_redir;

// PIPE NODE STRUCT
typedef struct s_pipe
{
	int		type;
	t_cmd	*left;
	t_cmd	*right;
}			t_pipe;

// FILE DETAILS STRUCT
typedef struct s_file
{
	char	*file;
	int		mode;
	int		fd;
}			t_file;

// MINISHELL MAIN DATA STRUCT
typedef struct s_data
{
	char	*prompt;
	char	*input;
	t_cmd	*tree;
	t_list	*lst_nodes;
	int		return_code;
	int		heredoc_count;
	char	**variables;
	char	*filename;
	bool	no_string;
	int		token;
	bool	text_quotes;
}			t_data;

// SIGNALS
# define NO_SIG			0
# define S_SIGQUIT		1
# define S_SIGINT		2
# define S_SIGEOF		3

// PARSED NODE TYPES
# define EXEC			1
# define REDI			2
# define PIPE			3

// PARSING DICTIONARIES
# define MS_SPACE		" \t\r\n\v"
# define MS_TOKENS		"<|>"
# define MS_QUOTES		"\"\'"
# define MS_DIGITS		"0123456789"
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

// HEREDOC FILE LIMIT
# define HEREDOC_LIMIT	999

// RETURN CODES
# define GENERAL_ERROR	1
# define SHELL_BUILT_IN	2
# define CMD_NOT_EXEC	126
# define SIG_INT_TERM	130

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
# define HEREDOC_CTRL_D	6
# define FORK			7
# define REDIR_FILE		8

// ERROR MESSAGES
# define MSG_MINISHELL	"minishell: "
# define MSG_MALLOC		"malloc: Cannot allocate memory"
# define MSG_FORK		"fork: Cannot allocate memory"
# define MSG_SYNTAX		"syntax error near unexpected token "
# define MSG_QUOTE		"unexpected EOF while looking for matching "
# define MSG_ARG_LIMIT	": Argument list too long"
# define MSG_HEREDOC	"cannot create heredoc file (limit reached)"
# define MSG_HDOC_CTRLD "warning: here-document delimited by end-of-file \
(wanted `"
# define MSG_REDIR_FILE	": ambiguous redirect"

// INITIALIZE / CLOSE / FREE
t_data	*init_minishell(char **envp, int return_code);
char	*free_str(char *str);
t_cmd	*free_tree(t_cmd *node);
void	free_exec(t_cmd *node);
void	ft_del(void *content);
void	lst_clean(t_list **lst);
void	delete_variables(char **variables);
void	free_environment(char **envp);
void	clean_shell(t_data *ms_data);

// PARSER - CREATE ABSTRACT SYNTAX TREE
t_cmd	*exec_node(void);
t_cmd	*redir_node(t_cmd *sub_node, t_file *file);
t_cmd	*pipe_node(t_cmd *left, t_cmd *right);
char	*expand_var(t_data *ms_data, char *start, char *end, char **str);
char	*substr(char *start, char *end);
char	*concat_str(char *str, char *sub_start, char *sub_end);
char	*substr_expans(t_data *ms_data, char *start, char *end, int token);
char	*get_return_code(t_data *ms_data, char *start, char **str);
int		getvarname(t_data *ms_data, char **start, char *end, char **var_name);
int		look_token(char **input, char *tokens);
char	*parse_text(t_data *ms_data, char *str, int *token);
int		parse_token(t_data *ms_data, char **input, char **stoken, \
char **etoken);
int		fill_argv(t_data *ms_data, char *stoken, t_exec *exec);
int		exit_heredoc(t_data *ms_data, char *delimiter, int fd, int r_code);
int		write_heredoc(t_data *ms_data, char *delimiter, int fd);
char	*substr_heredoc(t_data *ms_data, char *start, char *end);
t_cmd	*heredoc_node(t_data *ms_data, t_cmd *node, char *delimiter);
t_cmd	*seq_redir(t_data *ms_data, t_cmd *node, t_file *file);
t_cmd	*parse_redir(t_data *ms_data, t_cmd *node, char **input);
t_cmd	*parse_pipe(t_data *ms_data, char **input);
t_cmd	*create_tree(t_data *ms_data);
t_cmd	*check_node(t_data *ms_data, t_cmd *node);
char	*check_str(t_data *ms_data, char *str);
char	**check_str_2d(t_data *ms_data, char **str);
int		check_fd(t_data *ms_data, int fd);
char	*check_readline(t_data *ms_data, char *str, char *delimiter);
int		check_argv(t_data *ms_data, char **argv, int argc);
t_file	*check_file(t_data *ms_data, t_file *file);
pid_t	check_fork(t_data *ms_data, pid_t pid);
char	*check_red(t_data *ms_data, char *stoken, char *str);

// EXECUTION

// BUILT-IN FUNCTIONS
int		handle_relative_path(char *line, t_data *ms_data);
int		relative_path_helper(char *path, t_data *ms_data, char *line);
char	*get_original_path(void);
int		cleaner_original_path(char *original_path, char *full_path);
// cd
void	handle_cd(t_data *ms_data, char **argv, char *pwd);
int		handle_absolut_path(char *line, t_data *ms_data);
int		handle_home(t_data *ms_data);
int		ft_count_args(char **argv);
//check_options
int		check_options_echo(char **argv, t_data *ms_data);
int		check_options(char **argv, t_data *ms_data);
int		check_options_exit(char **argv, t_data *ms_data);
int		check_options_built_ins(char **argv, t_data *ms_data);
int		check_options_cd(char **argc, t_data *ms_data);
//echo
void	handle_echo(char **argv, t_data *ms_data);
void	print_arguments(char **argv, int i, t_data *ms_data, int new_line);
//env
void	handle_env(char **argv, t_data *ms_data);
//exit
int		str_is_white(char *str);
int		ft_is_special_char(char *arg);
int		check_special_char(int c);
int		is_valid_nbr(char *str);
int		check_required_args(char *arg, t_data *ms_data, long num);
void	prepare_to_exit(t_data *ms_data, char *pwd, int exit_code);
int		ft_isdigit_exit(int c);
int		ft_is_str(char *str);
int		check_2_in_1(char *arg);
void	handle_exit(char **argv, t_data *ms_data, char *pwd);
void	check_print_exit(void);
int		check_arg2(char **argv, t_data *ms_data);
//export
void	handle_export(char **argv, t_data *ms_data);
void	handle_existing_tmp(char *tmp, char **argv, t_data *ms_data, int i);
void	handle_variable(char **argv, t_data *ms_data, int i);
char	*ft_collapse_spaces(char *str);
char	*concactate_variable(char *arg, char *collapsed, \
t_data *ms_data, bool space);
void	case_no_equal(char **argv, t_data *ms_data, int i);
void	case_equal_plus(char **argv, t_data *ms_data, t_var **vars, int i);
void	export_env(t_data *ms_data);
int		sort_vars(t_var **vars);
void	delete_bulk_vars(t_var **vars);
char	*extract_variable_name(char *arg);
int		process_existing_variables(char *name, char *arg, \
t_data *ms_data, t_var **vars);
int		validate_variable_name(char *name, t_data *ms_data, char *arg);
void	add_new_variable(char *name, char *arg, t_data *ms_data);
//pwd
void	handle_pwd(char **argv, t_data *ms_data);
//search_buit_in
bool	search_builtin(char *command);
void	ft_exec_builtin(char **argv, t_data *ms_data);
void	ft_exec_builtin_2(char **argv, t_data *ms_data, char *pwd);
void	ft_exec_builtin_3(char **argv, t_data *ms_data, char *pwd);
//unset
void	handle_unset(char **argv, t_data *ms_data);

// ENVIROMENT
char	**copy_environment(char **envp);
void	delete_remaining_variables(char **variables, int len);
void	free_and_copy_environment(char ***my_envs, char **variables);
char	**expand_environment(char **envp, char *var, t_data *ms_data);
int		initial_checks_expander(char **envp, char *var, t_data *ms_data);
int		expander_helper(char **envp, char **new_envp, char *var, \
t_data *ms_data);
int		delete_remain_expander(char **variables, int len);
int		delete_remain_reducer(char **variables, int len, t_data *ms_data);
int		reducer_helper(char **envp, char **new_envp, t_data *ms_data, \
int index);
char	**reduce_environment(char **envp, char *var, t_data *ms_data);
//tmp_vars
t_var	**ft_create_bulk_vars(t_data *ms_data);
int		count_vars(char **variables);
t_var	**allocate_var_array(int count, t_data *ms_data);
int		populate_vars(t_var **vars, t_data *ms_data, int count);
void	free_vars(t_var **vars, int count);

void	update_new_pwd(char *new_pwd, char *new_pwd_str, t_data *ms_data);
void	update_old_pwd(char *old_pwd, char *old_pwd_str, t_data *ms_data);
void	update_pwd(char *old_pwd, t_data *ms_data);
int		is_variable_name_ok(char *name);
int		find_variable(char **envp, const char *name);
char	*my_getenv(char *var_name, char **variables);
char	*my_getenv_expans(char *var_name, char **variables);

// ERROR HANDLING
void	print_exec_error(char *error_message, char *command);
void	handle_exec_errors(char *path, t_data *ms_data);
void	handle_path_errors(char *path, t_data *ms_data);
void	prepare_error(char *error_message, char *command, t_data *ms_data, \
int return_code);
void	prepare_cd_error(char *error_message, char *command, \
t_data *ms_data, int error_code);
int		prepare_exit_error(char *error_message, char *arg, \
t_data *ms_data, int exit_code);
void	prepare_exit_numeric(char *str, char **argv, t_data *ms_data, \
int return_code);
int		error_options(char *error_msg, char *opt_msg, t_data *ms_data);
void	set_return_code(t_data *ms_data, int error_code);
void	print_error_msg_quotes(char *msg, char *info);
void	print_error(t_data *ms_data, int error_code, char *error_info);
void	print_syntax_error(t_data *ms_data, int token);

// EXECUTION
//case_exec
void	case_exec(t_exec *exec_cmd, t_data *ms_data);
void	handle_executable(char *executable, t_exec *exec_cmd, t_data *ms_data);
void	command_not_found(char *command, t_data *ms_data, int exit_code);
void	handle_null_exec(t_data *ms_data, int exit_code);
char	*check_path_exec(t_exec *exec_cmd, t_data *ms_data, int exit_code);
void	handle_executable_helper(char *executable, t_exec *exec_cmd, \
t_data *ms_data, int exit_code);
//case_pipe
void	case_pipe(t_pipe *pipe_cmd, t_data *ms_data);
void	setup_pipe_exec_left(t_pipe *pipe_cmd, t_data *ms_data, \
int *pipe_fd, pid_t pid);
void	setup_pipe_exec_right(t_pipe *pipe_cmd, t_data *ms_data, \
int *pipe_fd, pid_t pid);
void	handle_pipe_status(int status, t_data *ms_data);
void	prepare_pipe_error(char *error_message, t_data *ms_data, \
int error_code);
//case_redir
void	case_redir(t_cmd *tree, t_data *ms_data);
//exec_child
void	exec_tree(t_cmd *tree, t_data *ms_data);
//exec_tree
void	execute_tree(t_data *ms_data, t_exec *exec_cmd, int *status);
void	from_parent(int local_status, t_data *ms_data);
//exec_utils
int		is_valid_dir_token(char *dir);
int		is_duplicate_dir(char *dir, char **dirs, int count);
//find_executable
char	*find_executable(char *command, t_data *ms_data);
void	build_full_path_2(char *full_path, const char *dir, \
const char *command);
char	*get_path_env(t_data *ms_data, char *command);
int		build_full_path(char *full_path, const char *dir, const char *command);
char	*check_final_finder(char *path_env, char *path, char *full_path, \
int code);
//handle_input
void	handle_input(t_data *ms_data, char ***my_envs, int *return_code);
//main
void	set_routine(t_data *ms_data, char **my_envs, int return_code);
void	init_shell(t_data **ms_data, char ***my_envs, int return_code);
void	exit_minishell(t_data *ms_data, char **my_envs);
//print_tree
void	print_exec(t_cmd *node);
void	print_redir(t_cmd *node);
void	print_pipe(t_cmd *node);
void	print_tree(t_cmd *node);

// LIBFT_EXTRAS
int		ft_is_char(char c);
char	*ft_strsep(char **str, const char *delim);
size_t	ft_strcspn(const char *s1r, const char *s2r);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strndup(const char *s1, size_t n);
char	*ft_strtok(char *str, const char *sep);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strcat(char *dest, const char *src);
int		ft_is_char_opt(int c);

// SIGNALS
void	update_codes_130(t_data *ms_data, int *return_code);
void	handle_signals(void);
void	handle_sigint_parent(int sig);
void	handle_heredoc(int sig, t_data *ms_data, char *delimiter, int fd);

// LAST MINUTE ADDS
void	ft_xpo(char *tmp, char **argv, t_data *ms_data, int i);

#endif
