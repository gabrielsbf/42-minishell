#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>

int	is_dir(char *path)
{
	struct stat	st;

	if (stat(path, &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
			printf("IS DIR\n");
		else
			printf("IS NOT A DIR\n");
		return (1);
	}
	else
		perror("stat");
	return (0);
}

int main ()
{
	char *pwd = "/home/bkwamme/studies/core42/42-minishell/./minishell";
	char *actual = "./minishell";
	char *path = "/home/bkwamme/.local/bin/.";
	is_dir(pwd);

	return (0);
}
