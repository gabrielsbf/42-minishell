#include "../../includes/minishell.h"

void	print_parser_struct(t_parse **parser)
{
	int	i;

	i = 0;
	printf("Main Command -> %s\n", (*parser)->main_command);
	if ((*parser)->arguments == NULL)
		return ;
	while((*parser)->arguments[i] != NULL)
	{
		printf("parser argument number %d is: %s\n", i, (*parser)->arguments[i]);
		i++;
	}
}
