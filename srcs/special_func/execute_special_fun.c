#include "../../includes/minishell.h"

void	sp_char_exec(t_parse **parser, t_env **env, char **envp)
{
	(void)envp;
	(void)env;
	(void)envp;
	if ((*parser)->special_char != NULL)
	{
		printf("--------------------- SPECIAL CHAR TEST ---------------------\n");
		printf("special char of the node is: %s\n", (*parser)->special_char);
		printf("---------------------------------------------------------------\n");
    //Verificar se esse fork não irá dar problema.
		if (ft_strcmp((*parser)->special_char, ">") == 0)
			printf("redirect identified\n");
			// redirect(parser);
		if (ft_strcmp((*parser)->special_char, ">>") == 0)
			append(parser);
		if (ft_strcmp((*parser)->special_char, "|") == 0)
			pipe_handler(parser);
		if (ft_strcmp((*parser)->special_char, "<") == 0)
			printf("input redirect\n");
		if (ft_strcmp((*parser)->special_char, "<<") == 0)
			printf("heredoc");
		printf("--------------------- SPECIAL CHAR TEST ---------------------\n");
	}
}
