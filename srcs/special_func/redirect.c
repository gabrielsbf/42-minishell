#include "../../includes/minishell.h"
/*redirect incomplete*/

char	*get_redir_name(char	*redir)
{
	int	i;
	int	file_i;
	char	*file_name;

	file_i = 0;
	i = 0;
	while (redir[i] != '\0')
	{
		if (redir[i] != '<' && redir[i] != '>' && redir[i] != ' ')
			file_i++;
		i++;
	}
	file_name = ft_calloc(sizeof(char), file_i + 1);
	i = 0;
	file_i = -1;
	while (redir[i] != '\0')
	{
		if (redir[i] != '<' && redir[i] != '>' && redir[i] != ' ')
			file_name[++file_i] = redir[i];
		i++;
	}
	return (file_name);
}

void	redirect(t_parse *parser, int redir_i)
{
	char	*file_name;

	file_name = get_redir_name(parser->redir[redir_i]);
	if (parser->fd_out != 1)
		close(parser->fd_out);
	parser->fd_out = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	free(file_name);
}
