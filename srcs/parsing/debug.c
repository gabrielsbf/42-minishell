#include "../../includes/minishell.h"

void	print_parser_struct(t_parse *parser)
{
	printf("\nPRINTING FUNDAMENTAL ELEM PARSER STRUCT\n-------------------------------------------------\n");
	t_parse *temp;
	int	i;
	int	index_node;

	index_node = 0;
	temp = parser;
	while (temp != NULL)
	{
		printf("NODE INDEX %d\n", index_node);
		i = 0;
		printf("Cmd Text is: %s\n", temp->command_text);
		printf("Main Command -> %s\n", temp->main_command);
		if ((temp)->special_char != NULL)
			printf("special char is: %s\n",temp->special_char);
		if (temp->arguments == NULL)
			return ;
		while(temp->arguments[i] != NULL)
		{
			printf("temp argument number %d is: %s\n", i, temp->arguments[i]);
			i++;
		}
		temp = temp->next;
		printf("*************************************\n");
		index_node++;
	}
	printf("\n");
}
