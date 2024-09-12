#include "../../includes/minishell.h"
/*
A ideia é fazer a expansão dentro do function listener
Que deve tratar os argumentos antes de passar para as funções
*/

void	validating_quotes(char *text, int memory)
{
	if (is_between_quotes(text, memory, 39))
		printf("SIMPLE QUOTE - doesn't expand\n");
	else if (is_between_quotes(text, memory, 34))
		printf("DOUBLE QUOTES - EXPAND\n");
	else
		printf("NOT BETWEEN QUOTES - EXPAND\n");
}

void	hand_cipher(char *text)
{
	int	i;

	i = 0;
	while (text[i] != '\0')
	{
		if (text[i] == '$')
			validating_quotes(text, i);
		i++;
	}
}

void	env_expansion(t_parse **parser)
{
	int		i;
	char	*text;

	i = 0;
	while ((*parser)->arguments[i] != NULL)
	{
		// printf("PARSER ARGUMENT IS: %s\n", (*parser)->arguments[i]);
		text = (*parser)->arguments[i];
		hand_cipher(text);
		i++;
	}

}
