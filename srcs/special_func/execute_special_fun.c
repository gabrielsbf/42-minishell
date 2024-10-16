#include "../../includes/minishell.h"

void	sp_char_exec(t_parse **parser, t_env **env)
{
	printf("SPECIAL CHAR TEST\n");
	printf("-------------------------------------------------\n");
	(void)env;
	if ((*parser)->special_char == NULL)
		printf("Doesn't have any special char\n");
	if ((*parser)->special_char != NULL
		&& ft_strcmp((*parser)->special_char, ">") == 0)
	{
		(*parser)->pid = fork();
		if ((*parser)->pid == 0)
			redirect(parser);
		printf("entered in >\n");
	}
	if ((*parser)->special_char != NULL
		&& ft_strcmp((*parser)->special_char, ">>") == 0)
		printf("entered in >>\n");
	if ((*parser)->special_char != NULL
		&& ft_strcmp((*parser)->special_char, "|") == 0)
		printf("entered in |\n");
	printf("-------------------------------------------------\n\n");
}
