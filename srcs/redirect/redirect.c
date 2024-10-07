#include "../../includes/minishell.h"

void	check_redirect_file(t_parse *temp, int argument)
{
	int		fd;

	fd = 0;
	if (temp->arguments[argument] == NULL)
		return ;/*
	ft_calloc(sizeof(char), ft_strlen(temp->arguments[argument]) + 1);
	while (temp->arguments[argument][i] != '\0')
	{
		file_name[i] = temp->arguments[argument][i];
		i++;
	} */
	int pid = fork();
	if (pid == 0)
	{
		fd = open(temp->arguments[argument], O_WRONLY | O_CREAT, 0777);
		printf("%d\n", fd);
		dup2 (fd, STDOUT_FILENO);
		close(fd);
		exit(0);
	}
}

void	search_redirect(t_parse *temp, char *text, int argument)
{

	int	i;

	(void)argument;
	i = 0;
	while (text[i] != '\0')
	{
		if (text[i] == '>')
		{
			temp->special_char = ">";
			check_redirect_file(temp, ++argument);
		}
		i++;
	}
}

void	redirect(t_parse **parser)
{
	t_parse	*temp = (*parser);
	int		i;
	char	*text;

	i = 0;
	while (temp->arguments[i])
	{
		text = temp->arguments[i];
		search_redirect(temp,text, i);
		i++;
	}
}
