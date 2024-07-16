#include "../../includes/minishell.h"

/*(finished) Function is called when a char that normally the user wants to
target is incountered, it then get the index of the char c encountered at the string(line_read)
the position argument set where is the index of the string that you want to begin.
The return is the absolute index of the position of the encountered char*/
int	get_next_match(char  *line_read, int position, char c)
{
	position++;
	while (line_read[position] != '\0' && line_read[position] != c)
		position++;
	if (line_read[position] != c)
		return -1;
	return position;

}

/*
(incomplete) Function to return 1 if the main command on the prompt is validated and 0 if not
 */
int	first_command_is_valid(char	*line_read)
{
	/*Just to work - return will change*/
	(void)line_read;

	return (1);
}

/*
(incomplete)Validates the line buffer.
Rules:
1. (already did) every simple or double quote that starts needs to have a second to end.
2. (still not did) the first command needs to be valid.
.*/
int	validate_line_read(char *line_read)
{
	int	i;

	i = 0;
	while (line_read[i] != '\0')
	{
		if (line_read[i] == 34 || line_read[i] == 39)
		{
			i = get_next_match(line_read, i, line_read[i]);
		}
		if (i == -1)
			return (0);
		i++;
	}
	printf("validate line read is OK\n");
	return (1);
}


/*(finished) Count the number of char * present on the vector.*/
int count_arr_nb(char **str)
{
	int i;

	i = 0;
	while (str[i] != NULL)
		i++;
	return (i);
}

/*(finished) This function do a realloc between two arrays of char pointers
It will be on the sequence -> the first char ** will be at the
start and the second will be at the end.*/
char **ft_realloc_two_lists(char **str, char **str_new)
{
	int		new_alloc;
	int		i;
	int		i_last;
	char	**new_arr;

	i = 0;
	i_last = 0;
	new_alloc = count_arr_nb(str) + count_arr_nb(str_new) + 1;
	new_arr = (char **)malloc(new_alloc * sizeof(char *));
	while (str[i] != NULL)
	{
		new_arr[i] = ft_strdup(str[i]);
		free(str[i++]);
	}
	while (str_new[i_last] != NULL)
	{
		new_arr[i++] = ft_strdup(str_new[i_last]);
		free(str_new[i_last++]);
	}
	free(str);
	free(str_new);
	new_arr[i] = NULL;
	return (new_arr);
}

/*(finished) This function do a realloc of an array of char pointers and puts a new
char pointer at the end of the array.*/
char **ft_realloc_list_and_str(char **str, char *str_new)
{
	int		new_alloc;
	int		i;
	char 	**new_arr;

	i = 0;
	new_alloc = count_arr_nb(str) + 2;
	new_arr = (char **)malloc(new_alloc * sizeof(char *));
	while (str[i] != NULL)
	{
		new_arr[i] = ft_strdup(str[i]);
		free(str[i]);
		i++;
	}
	new_arr[i] = ft_strdup(str_new);
	new_arr[i + 1] = NULL;
	free(str_new);
	free(str);
	return new_arr;
}


/*
(incomplete) This function will pass through the line_readed and will count how many arguments will exist
(an argument is a word that is not between quotes or a sentence that is indeed between simple or double quotes.)
*/
int	count_args(char *line_read)
{
	int	count;
	int	i;

	i = 0;
	count = 0;

	/*Just to work - return will change*/
	(void)count;
	while(line_read[i] != '\0')
	{
		if (line_read[i+1])
		i++;
	}
	/*Just to work - return will change*/
	return (i);
}

int	set_main_command(t_parse **parser, char *line_read)
{
	int	i;

	i = 0;
	printf("i begin set main command\nstring is: %s\n", line_read);
	while(line_read[i] != '\0' && !ft_isspace(line_read[i]))
	{
		printf("On 'set_main_command' -> line read c is:%c\n", line_read[i]);
		i++;
	}
	printf("i when found some space is: %d\n", i);
	(*parser)->main_command = ft_substr(line_read, 0, i);
	printf("main command is : %s and i is: %d\n", (*parser)->main_command, i);
	return (i);
}

int	is_between_quotes(char *line_read, int memory, char find)
{
	int	qt;
	printf("testing in quotes\n");
	qt = 0;
	while (memory >= 0)
	{
		printf("reverse getting memory -> char is: %c\n",line_read[memory]);
		if (line_read[memory] == find)
			qt++;
		memory--;
	}
	if (qt == 0 || qt % 2 == 0)
		return (0);
	return (1);
}

int	is_blank_substr(char *line_read, int memory, int pos)
{
	printf("start function -> is blank substr\n");
	while (pos >= memory)
	{
		if (!ft_isspace(line_read[pos]))
			return (0);
		pos--;
	}
	printf("is blank substr\n");
	return (1);
}

int	split_process(t_parse **parser, int memory, int pos, char c)
{
	char	*text_to_parse;
	char	*substr_text;

	printf("entered in split proccess\nmemory:%d, pos:%d, char c:%d\n",memory, pos, c);
	text_to_parse = (*parser)->entire_text;
	printf("text to parse variable is:%s\n", text_to_parse);
	if (!is_between_quotes(text_to_parse, memory, c))
	{
		printf("text is not between quotes\n");
		if (is_blank_substr(text_to_parse, memory, pos))
			return (0);
		printf("position - memory is: %d\n", (pos - memory));
		printf("it's not blank substr\ntext to parse is: %s\n", text_to_parse);
		substr_text = ft_substr(text_to_parse, memory, (pos - memory));
		printf("substr text: %s\n", substr_text);
		(*parser)->arguments = ft_realloc_two_lists((*parser)->arguments, ft_split_and_free(substr_text, ' ' ));
	}
	else
	{
		printf("entered in else\n");
		substr_text = ft_substr(text_to_parse, memory, pos - memory + 1);
		printf("substr text is: %s\n", substr_text);
		(*parser)->arguments = ft_realloc_list_and_str((*parser)->arguments, substr_text);
	}
	return (1);
}

void	parsing_process(char *line_read, t_parse **parser)
{
	int	i;
	int	memory;

	printf("initiating parsing process fun\n");
	i = set_main_command(parser, line_read);
	memory = i;
	while (line_read[i] != '\0')
	{
		printf("os parsing proccess - line read is: %c\n", line_read[i]);
		if(line_read[i] == 34 || line_read[i] == 39)
		{
			split_process(parser, memory, i, line_read[i]);
			if (is_between_quotes(line_read, i, line_read[i]))
				memory = i;
			else
				memory = i + 1;
		}
		i++;
	}
	split_process(parser, memory, i, line_read[i]);
}

/*(incomplete) This function needs to set all the attributes of the parser struct.*/
t_parse	*init_parse(char *line_read)
{
	t_parse	*parser_init;
	printf("Iniciei o parser\n");
	parser_init = malloc(sizeof(t_parse));
	printf("Parser Malocado\n");
	parser_init->next = NULL;
	printf("Parser em next é nulo\n");
	parser_init->entire_text = ft_strdup(line_read);
	printf("entire text duplicado -> line read\n");
	parser_init->arguments = (char **)malloc(sizeof(char *));
	printf("argumentos mallocados\n");
	parser_init->arguments[0] = NULL;
	printf("set de arguments pra nulo\n");
	return (parser_init);
}

/*Preciso validar parte da leitura em cima do texto da esquerda pra direita.*/
/*(incomplete) maybe this function will get all the constructors and make the treatment of the line buffer.---*/
void	main_line_process(char *line_read)
{
	char	*get_line_treated;
	t_parse	*parser;

	parser = init_parse(line_read);
	get_line_treated = ft_strtrim(line_read, " ");
	printf("Texto Trimado->%s\n", get_line_treated);
	free(line_read);
	printf("Passei o free\n");
	if (!validate_line_read(get_line_treated))
		return ;
	printf("Passei o validate\n");
	parsing_process(get_line_treated, &parser);
	print_parser_struct(&parser);
}

/*for debug -> print function*/
void	print_parser_struct(t_parse **parser)
{
	int	i;

	i = 0;
	printf("Main Command -> %s\n", (*parser)->main_command);
	if ((*parser)->arguments == NULL)
		return ;
	while((*parser)->arguments[i] != NULL)
	{
		printf("parser argument number %d is: %s\n", i, (*parser)->arguments[i]);
		i++;
	}
}
