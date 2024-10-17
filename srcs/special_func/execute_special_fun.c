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
		if ((*parser)->pid != 0)
			(*parser)->pid = fork();
		waitpid((*parser)->pid, NULL, 0);
		if ((*parser)->pid == 0)
		{
			if (ft_strcmp((*parser)->special_char, ">") == 0)
				redirect(parser);
			if (ft_strcmp((*parser)->special_char, ">>") == 0)
				append(parser);
			if (ft_strcmp((*parser)->special_char, "|") == 0)
				pipe_handler(parser);
			if (ft_strcmp((*parser)->special_char, "<") == 0)
				printf("input redirect\n");
			if (ft_strcmp((*parser)->special_char, "<<") == 0)
				printf("heredoc");
			g_status = 0;
		}
		printf("--------------------- SPECIAL CHAR TEST ---------------------\n");
	}
}
