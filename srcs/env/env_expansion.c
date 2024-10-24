#include "../../includes/minishell.h"
/*
A ideia é fazer a expansão dentro do function listener
Que deve tratar os argumentos antes de passar para as funções
*/
int	expand_variable(t_parse **parser, int argument, int i_cipher, t_env **envs)
{
	char	*env_name;
	char	*env_value;
	char 	*sentence;
	int		memory;

	memory = i_cipher + 1;
	sentence = (*parser)->arguments[argument];
	while(sentence[memory] != '\0' && is_env_available(sentence[memory]))
		memory++;
	env_name = ft_substr(sentence, i_cipher + 1, memory - i_cipher - 1);
	env_value = check_name_in_env(envs, env_name);
	if (env_value == NULL)
		return 0;
	replace_text(parser, argument, env_name, env_value);
	free(env_name);
	return (1);
}

int	is_valid_env_quote(char *text, int memory)
{
	if (is_between_quotes(text, memory) == 39 ||
	is_between_quotes(text, memory) == 78)
		return (0);
	else if (is_between_quotes(text, memory))
		return (1);
	else
		return (1);
}

void	hand_cipher(t_parse **parser, char *text, int argument, t_env **envs)
{
	int	i;
	int expand_bool;
	i = 0;
	while (text[i] != '\0')
	{
		expand_bool = 0;
		if (text[i] == '$')
			expand_bool = is_valid_env_quote(text, i);
		if (expand_bool == 1)
		{
			if (expand_variable(parser, argument, i, envs))
				hand_cipher(parser, (*parser)->arguments[argument], argument, envs);
		}
		i++;
	}
}

void	env_expansion(t_parse **parser, t_env **envs)
{
	int		i;
	char	*text;
	t_parse **head;

	head = parser;
	i = 0;
	while ((*parser) != NULL)
	{
		while ((*parser)->arguments[i] != NULL)
		{
			text = (*parser)->arguments[i];
			hand_cipher(parser, text, i, envs);
			i++;
		}
		(parser) = &(*parser)->next;
	}
	(parser) = head;
}
