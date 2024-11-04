#include "../../includes/minishell.h"


void	handle_echo(char **argv)
{
	int	i;
	int	print_newline;

	i = 1;
	print_newline = 1;

	/* print_test();
	printf("argv[0]: |%s|\n", argv[0]);
	printf("argv[1]: |%s|\n", argv[1]);
	printf("argv[2]: |%s|\n", argv[2]);
	printf("argv[3]: |%s|\n", argv[3]);
	print_test(); */

	if (argv[1] && !ft_strncmp(argv[1], "-n", 3))
	{
		i++;
		print_newline = -1;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i], 1);
		if (argv[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (print_newline == 1)
		ft_putstr_fd("\n", 1);
}

int	str_is_simple(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}
