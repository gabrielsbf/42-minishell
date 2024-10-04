#include "../../includes/minishell.h"

/*(incomplete)
Note: Gets the line read trimmed
Get the first command of the vector.
Needs to work around*/
int	set_main_command(t_parse **parser, char *line_read)
{
	int	i;

	i = 0;
	while(line_read[i] != '\0' && !ft_isspace(line_read[i]))
		i++;
	(*parser)->main_command = ft_substr(line_read, 0, i);
	return (i);
}

/*Preciso validar parte da leitura em cima do texto da esquerda pra direita.*/
/*(incomplete) maybe this function will get all the constructors and make the treatment of the line buffer.---*/
void	main_line_process(char *line_read, t_env **env)
{
	t_parse	*parser;

	parser = init_parse(line_read);
	if (!validate_line_read(line_read))
		return ;
	parsing_process(line_read, &parser);
	free(line_read);
	print_parser_struct(&parser);
	function_listener(&parser, env); //podemos alocar em um local mais adequado

}

int	split_process(t_parse **parser, int memory, int pos)
{
	char	*text_to_parse;
	char	*substr_text;

	//printf("entered in split proccess\nmemory:%d, pos:%d, char c:%d\n",memory, pos, c);
	text_to_parse = (*parser)->entire_text;
	//printf("text to parse variable is:%s\n", text_to_parse);
	if (is_between_quotes(text_to_parse, memory) == 0)
	{
		if (is_blank_substr(text_to_parse, memory, pos))
			return (0);
		substr_text = ft_substr(text_to_parse, memory, (pos - memory));
		//printf("substr text: %s\n", substr_text);
		(*parser)->arguments = ft_realloc_two_lists((*parser)->arguments, ft_split_and_free(substr_text, ' ' ));
	}
	else
	{
		substr_text = ft_substr(text_to_parse, memory, pos - memory + 1);
		(*parser)->arguments = ft_realloc_list_and_str((*parser)->arguments, substr_text);
	}
	return (1);
}

void	parsing_process(char *line_read, t_parse **parser)
{
	int	i;
	int	memory;

	i = set_main_command(parser, line_read);
	memory = i;
	while (line_read[i] != '\0')
	{
		if(line_read[i] == 34 || line_read[i] == 39)
		{
			if (is_between_quotes(line_read, i) == line_read[i] ||
			is_between_quotes(line_read, i) == line_read[i] * 2)
				split_process(parser, memory, i);
			else
			{
				i++;
				continue;
			}
			// printf("is between quotes result: %d\n----------------------------\n", is_between_quotes(line_read, i));
			if (is_between_quotes(line_read, i) >= 34 && is_between_quotes(line_read, i) <= 39)
				memory = i;
			else
				memory = i + 1;
		}
		i++;
	}
	if (memory == i)
		return ;
	split_process(parser, memory, i);
}

/*(incomplete) This function needs to set all the attributes of the parser struct.*/
t_parse	*init_parse(char *line_read)
{
	t_parse	*parser_init;
	parser_init = malloc(sizeof(t_parse));
	parser_init->next = NULL;
	parser_init->entire_text = ft_strdup(line_read);
	parser_init->arguments = (char **)malloc(sizeof(char *));
	parser_init->arguments[0] = NULL;
	parser_init->fd_in = 0;
	parser_init->fd_out = 1;
	return (parser_init);
}
