#include "../../includes/minishell.h"

/*função usada para identificar que tipo de redirect foi encontrado usando inteiros como identificadores*/
void	run_redir(t_parse *temp, int redir_i)
{
	if (temp->redir[redir_i][0] == '>' && (temp->redir[redir_i][1] != '>'
		&& temp->redir[redir_i][1] != '<'))
		redirect(temp, redir_i);
	if (temp->redir[redir_i][0] == '<' && (temp->redir[redir_i][1] != '>'
		&& temp->redir[redir_i][1] != '<'))
		redirect_in(temp, redir_i);
	if (temp->redir[redir_i][0] == '>' && temp->redir[redir_i][1] == '>')
		append(temp, redir_i);/*
	if (redir[0] == '<' && redir[1] == '<')
		return (4); */
}

void	sp_char_exec(t_parse **parser)
{
	int		redir_i;
	t_parse	*temp;

	temp = (*parser);
	if (temp->special_char != NULL)
			pipe_handler(parser);
	while (temp)
	{
		redir_i = 0;
		if (!temp->redir && temp->next != NULL)
		{
			temp = temp->next;
			continue ;
		}
		if (!temp->redir && !temp->next)
			return ;
		while (temp->redir[redir_i])
		{
			run_redir(temp, redir_i);
			redir_i++;
		}
		temp = temp->next;
	}
}
