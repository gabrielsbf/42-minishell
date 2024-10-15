#include "../../includes/minishell.h"

void	sp_char_validation(t_parse **parser, t_env **env)
{
	(void)env;
	if ((*parser)->special_char != NULL
		&& ft_strcmp((*parser)->special_char, ">") == 0)
	{
		(*parser)->pid = fork();
		if ((*parser)->pid == 0)
			redirect(parser);
	}
	if ((*parser)->special_char != NULL
		&& ft_strcmp((*parser)->special_char, ">>") == 0)
		printf("AAA\n");
	if ((*parser)->special_char != NULL
		&& ft_strcmp((*parser)->special_char, "|") == 0)
		printf("AAA\n");
}
