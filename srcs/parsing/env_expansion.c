#include "../../includes/minishell.h"
/*
A ideia é fazer a expansão dentro do function listener
Que deve tratar os argumentos antes de passar para as funções
*/

void	expand_variable(t_parse **parser, int argument, int i_cipher, t_env **envs)
{
	char	*env_var;
	char 	*sentence;
	int		memory;

	(void)envs;
	memory = i_cipher + 1;
	sentence = (*parser)->arguments[argument][memory];
	while(sentence[memory] != '\0' && ft_isalnum(sentence[memory]))
		memory++;
	env_var = ft_substr(sentence, i_cipher + 1, memory - i_cipher);
	printf("env var is: %s", env_var);
}

void	expand_prepare(t_parse **parser, int argument, t_env **envs)
{
	int	i;
	char *text;
	char *new_text;

	i = 0;
	text = (*parser)->arguments[argument][i];

	while (text[i] != '\0')
	{
		if (text[i] == '$')
			expand_variable(parser, argument, i, envs);
		i++;
	}
}

int	validating_quotes(char *text, int memory)
{
	if (is_between_quotes(text, memory, 39))
		return (0);
	else if (is_between_quotes(text, memory, 34))
		return (1);
	else
		return (1);
}

void	hand_cipher(t_parse **parser, char *text, int argument, t_env **envs)
{
	int	i;
	int expand_bool;

	i = 0;
	expand_bool = 0;
	while (text[i] != '\0')
	{
		if (text[i] == '$')
			expand_bool = validating_quotes(text, i);
		if (expand_bool == 1)
			expand_prepare(parser, argument, envs);
		i++;
	}
}

void	env_expansion(t_parse **parser, t_env **envs)
{
	int		i;
	char	*text;

	i = 0;
	while ((*parser)->arguments[i] != NULL)
	{
		// printf("PARSER ARGUMENT IS: %s\n", (*parser)->arguments[i]);
		text = (*parser)->arguments[i];
		hand_cipher(parser, text, i, envs);
		i++;
	}

}
