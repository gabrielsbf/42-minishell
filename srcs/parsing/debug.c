#include "../../includes/minishell.h"

void	print_parser_struct(t_parse **parser)
{
	t_parse *temp;
	int	i;

	temp = (*parser);
	while (temp != NULL)
	{
		i = 0;
		printf("Main Command -> %s\n", temp->main_command);
		printf("Cmd Text is: %s\n", temp->command_text);
		if ((*parser)->special_char != NULL)
			printf("special char is: %s\n",(*parser)->special_char);
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
