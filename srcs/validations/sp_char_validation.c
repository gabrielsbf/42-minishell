#include "../../includes/minishell.h"

void	sp_char_validation(t_parse **parser, t_env **env)
{
	int	std_o;

	std_o = 1;
	if ((*parser)->special_char != NULL
		&& ft_strcmp((*parser)->special_char, ">") == 0)
		std_o = redirect(parser);
	if ((*parser)->special_char != NULL
		&& ft_strcmp((*parser)->special_char, ">>") == 0)
		std_o = append(parser);
	if ((*parser)->special_char != NULL
		&& ft_strcmp((*parser)->special_char, "|") == 0)
			std_o = pipe_handler(parser);
	function_listener(parser, env);
	dup2(std_o, STDOUT_FILENO);
}
