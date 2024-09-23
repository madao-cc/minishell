#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <linux/limits.h>
#include <stdbool.h>

#include <dirent.h>  // opendir, readdir, closedir

void	welcome_shell(void);
void	print_terminal_name(void);
void	handle_cd(char *line);
void	ft_ls(void);
void	navigate_up_directory(char *path);

int	main(int argc, char **argv)
{
	if (isatty(STDIN_FILENO))
	{
		welcome_shell();
		/*	Make sure the STDs are connected	*/
		printf("isatty(STDIN_FILENO) = %d\n", isatty(STDIN_FILENO));
		printf("isatty(STDOUT_FILENO) = %d\n", isatty(STDOUT_FILENO));
		printf("isatty(STDERR_FILENO) = %d\n", isatty(STDERR_FILENO));
		printf("\n\n");
		while (1)
		{
			print_terminal_name();
			char *line = NULL;
			char *input;
			size_t len = 0;
			getline(&line, &len, stdin);
			if (strcmp(line, "ls\n") == 0)
			{
				ft_ls();
			}
			else if (strcmp(line, "exit\n") == 0)  // Exit the shell
			{
				free(line);
				exit(0);
			}
			else if (strcmp(line, "clear\n") == 0)  // Clear the screen
			{
				printf("\033[2J");  // Clear the screen
				printf("\033[H");  // Move the cursor to the top left corner
			}
			else if (strncmp(line, "cd", 2) == 0)  // Change directory
			{
				handle_cd(line);
			}
			else
				printf("%s", line);
			free(line);
		}
	}
	else
	{
		printf("isatty(STDIN_FILENO) = %d\n", isatty(STDIN_FILENO));
		printf("isatty(STDOUT_FILENO) = %d\n", isatty(STDOUT_FILENO));
		printf("isatty(STDERR_FILENO) = %d\n", isatty(STDERR_FILENO));
	}
}

void	welcome_shell(void)
{
	printf("		\033[1;34m");  // Set color to bright blue
	printf("		\n\n");
	printf("		#########################################\n");
	printf("		#                                       #\n");
	printf("		#   \033[1;32mWelcome to Our Custom MiniShell!\033[1;34m    #\n");  // Bright green
	printf("		#                                       #\n");
	printf("		#   \033[1;31mFeel free to experiment, but...\033[1;34m     #\n");  // Bright red
	printf("		#      \033[1;5;31m**at your own risk!**\033[0m\033[1;34m            #\n");  // Bright red
	printf("		#                                       #\n");
	printf("		#########################################\n\n");
	printf("		\033[0m");  // Reset color to default
	printf("\n");
}

void	print_terminal_name(void)
{
	char cwd[PATH_MAX];

	getcwd(cwd, sizeof(cwd));
	printf("\033[1m\033[32mmy_shell\033[0m:\033[1m\033[33m%s\033[0m$ ", cwd);
}

void	handle_cd(char *line)
{
	char	*path;

	if (line[2] == '\n')
	{
		chdir(getenv("HOME"));
	}

}

void	ft_ls(void)
{
	DIR *dir;
	struct dirent *entry;
	bool nothing;

	dir = opendir(".");
	if (!dir)
	{
		perror("Erro ao abrir diretorio");
		exit(1);
	}
	nothing = true;
	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_name[0] != '.')
			printf("\033[34m%s\033[0m\t", entry->d_name);
		nothing = false;
	}
	if (nothing == false)
		printf("\n");
	closedir(dir);
}

void	navigate_up_directory(char *path)
{

}
