#include "../../includes/minishell.h"

void	print_parser_struct(t_parse *parser)
{
	t_parse *temp;
	int	i;

	temp = parser;
	while (temp != NULL)
	{
		i = 0;
		printf("Cmd Text is: %s\n", temp->command_text);
		printf("Main Command -> %s\n", temp->main_command);
		if ((temp)->special_char != NULL)
			printf("special char is: %s\n",temp->special_char);
		if (temp->arguments == NULL)
			return ;
		while(temp->arguments[i] != NULL)
		{
			printf("temp argument number %d is: %s\n\n", i, temp->arguments[i]);
			i++;
		}
		temp = temp->next;
	}
}
