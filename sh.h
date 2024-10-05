#ifndef SH_H
# define SH_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <linux/limits.h>
#include <stdbool.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

#include <dirent.h>  // opendir, readdir, closedir

void	welcome_shell(void);
void	print_terminal_name(void);
void	ft_ls(void);
void	handle_cd(char *line);
void	handle_home(void);
void	handle_relative_path(char *line);
char	*ft_strdup(char *s);
int	ft_is_blankspace(char c);
char	*ft_strtrim(const char *s1, const char *set);
int	ft_is_in_set(char c, const char *set);
int	ft_strcmp(const char *s1, const char *s2);
int	ft_is_char(char c);
void	handle_dot_cases(char *line);
void	handle_absolut_path(char *line);
void handle_pwd(void);

void	setup_signals(void);
void	handle_sigint(int sig);

#endif