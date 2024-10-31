#include "../../includes/minishell.h"

void	redirect_in(t_parse *parser, int redir_i)
{
	char	*file_name;

	file_name = get_redir_name(parser->redir[redir_i]);
	if (parser->fd_in != 0)
		close(parser->fd_in);
	parser->fd_in = open(file_name, O_RDONLY);
	if (parser->fd_in == -1)
		free(file_name);
}
