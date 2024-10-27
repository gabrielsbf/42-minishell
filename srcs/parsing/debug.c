#include "../../includes/minishell.h"

void	print_parser_struct(t_parse *parser)
{
	printf("\nPRINTING FUNDAMENTAL ELEM PARSER STRUCT\n-------------------------------------------------\n");
	t_parse *temp;
	int	i;
	int	index_node;
	int	i_redir;

	index_node = 0;
	temp = parser;
	while (temp != NULL)
	{
		printf("NODE INDEX %d\n", index_node);
		i = 0;
		i_redir = 0;
		printf("Cmd Text is: %s\n", temp->command_text);
		printf("Main Command -> %s\n", temp->main_command);
		if ((temp)->special_char != NULL)
			printf("special char is: %s\n",temp->special_char);
		if (temp->arguments != NULL)
		{
			while(temp->arguments[i] != NULL)
			{
				printf("temp argument number %d is: %s\n", i, temp->arguments[i]);
				i++;
			}
		}
		if (temp->redir != NULL)
		{
			while (temp->redir[i_redir] != NULL)
			{
				printf("redirect arr is: %s\n", temp->redir[i_redir]);
				i_redir++;
			}
		}
		printf("fd_in on node is: %d\n", temp->fd_in);
		printf("fd_out on node is: %d\n", temp->fd_out);
		printf("*************************************\n");
		index_node++;
		temp = temp->next;

	}
	printf("\n");
}
