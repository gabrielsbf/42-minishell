#include "../../includes/minishell.h"

int	sp_char_exec(t_parse **parser, t_env **env, char **envp)
{
	(void)envp;
	(void)env;
	if ((*parser)->special_char != NULL)
	{
		printf("--------------------- SPECIAL CHAR TEST ---------------------\n");
		printf("special char of the node is: %s\n", (*parser)->special_char);
		printf("---------------------------------------------------------------\n");
		// (*parser)->pid = fork();
		// if ((*parser)->pid == 0)
		// {
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
		// function_listener(parser, env, envp);
		waitpid(0, NULL, 0);
		return (0);
		// }
	}
	return(-1);
}
