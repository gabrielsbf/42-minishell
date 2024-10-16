#include"../../includes/minishell.h"

void	list_directory(const char *path)
{
	DIR				*dir;
	struct dirent	*entry;
	int				flag;

	flag = 0;
	if (!(dir = opendir(path)))
	{
		printf("ERROR");
		return;
	}
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (entry->d_name[0] != '.')
		{
			flag++;
			printf("%s  ", entry->d_name);
		}
		entry = readdir(dir);
	}
	if (flag > 0)
			printf("\n");
	closedir(dir);
}
