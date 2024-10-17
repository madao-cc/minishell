/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikelitoris <mikelitoris@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:00:13 by antfonse          #+#    #+#             */
/*   Updated: 2024/10/17 17:28:43 by mikelitoris      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <linux/limits.h>
#include <limits.h>
#include <stdbool.h>
#include <signal.h>  // sigaction
#include <sys/types.h>  // pid_t
#include <sys/wait.h>  // waitpid
#include <sys/stat.h>  // stat
#include <readline/readline.h>  // readline and add_history
#include <readline/history.h>  // add_history
#include <dirent.h>  // opendir, readdir, closedir
#include <fcntl.h>
# include "../libft/libft.h"

# define MAXARGS 10

typedef struct s_cmd
{
	int	type;
}		t_cmd;

typedef struct s_exec
{
	int		type;
	char	*argv[MAXARGS];
}			t_exec;

typedef struct s_redir
{
	int		type;
	t_cmd	*cmd;
	char	*file;
	int		mode;  // O_RDONLY, O_WRONLY, O_CREATE
	int		fd;  // 0 = stdin, 1 = stdout, 2 = stderr
}			t_redir;

typedef struct s_pipe
{
	int		type;
	t_cmd	*left;
	t_cmd	*right;
}			t_pipe;

// PARSED NODE TYPES
# define EXEC		1
# define REDI		2
# define PIPE		3

// PARSING DICTIONARIES
# define MS_SPACE		" \t\r\n\v"
# define MS_TOKENS		"<|>"
# define MS_QUOTES		"\"\'"
# define MS_VAR_CHAR	"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz\
0123456789_"

// TOKEN SYMBOLS
# define TOKEN_PIPE	'|'
# define TOKEN_INPU	'<'
# define TOKEN_OUTP	'>'
# define TOKEN_DELI	'd'  // DELIMITER
# define TOKEN_APPE	'a'  // APPEND
# define TOKEN_TEXT	't'

// VARIABLES
# define VAR_BUFFER		50

// PARSER
void	print_tree(t_cmd *node);
char	*substr(char *start, char *end);
t_cmd	*exec_node(void);
t_cmd	*redir_node(t_cmd *sub_cmd, char *file, int mode, int fd);
t_cmd	*pipe_node(t_cmd *left, t_cmd *right);
int	look_token(char **cmdline, char *tokens);
int	parse_token(char **cmdline, char **stoken, char **etoken);
t_cmd	*parse_pipe(char **cmdline);
t_cmd	*parse_tree(char *cmdline);
char	*expand_var(char *str, char *end, char **sub_start, char **sub_end);
char	*substr_expans(char *start, char *end);

// PROMPT
char	*ft_prepare_prompt(void);
char	*ft_trim(char *str);

// CD
void	handle_cd(char *line);
void	handle_absolut_path(char *line);
void	handle_home(void);
int	ft_is_char(char c);
void	handle_dot_cases(char *line);
void	handle_relative_path(char *line);

// EXEC_TREE
char *find_executable(char *command);
void	exec_tree(t_cmd *tree);

// FREE
void	free_tree(t_cmd *tree);

// SIGNALS
void	handle_signals(void);
void	handle_sigint(int sig);

// GLOBAL VARIABLE
extern volatile sig_atomic_t g_signal_received;

#endif
