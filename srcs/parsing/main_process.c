#include "../../includes/minishell.h"


int	jump_special_char(char *line_read)
{
	int	i;

	i = 0;
	while (is_special_char(line_read + i))
		i++;
	return (i);
}

/*(incomplete)
Note: Gets the line read trimmed
Get the first command of the vector.
Needs to work around*/
int	set_main_command(t_parse **parser, char *line_read)
{
	int	i;
	int i_spc;

	i_spc = 0;
	i = 0;
	i_spc = jump_special_char(line_read);
	while (line_read[i_spc] != '\0' && ft_isspace(line_read[i_spc]))
		i_spc++;
	while (line_read[i_spc + i] != '\0' && !ft_isspace(line_read[i_spc + i]))
		i++;
	(*parser)->main_command = ft_substr(line_read, i_spc, i);
	return (i_spc + i);
}

/*Preciso validar parte da leitura em cima do texto da esquerda pra direita.*/
/*(incomplete) maybe this function will get all the constructors and make the treatment of the line buffer.---*/
t_parse	*main_line_process(char *line_read, t_env **env)
{
	t_parse	*parser;
	t_parse	*head;
	char	*cmd_line;
	int		go_back;
	int		i;

	i = 0;
	go_back = (int)ft_strlen(line_read);
	(void)go_back;
	if (!validate_line_read(line_read))
		return NULL;
	while (pipe_char_pos(line_read) <= (int)ft_strlen(line_read) && line_read[0] != '\0')
	{
		cmd_line = separate_line_read(line_read);
		if (i == 0)
		{
			parser = init_parse(line_read, cmd_line, head, env);
			head = parser;
		}
		else if (i > 0)
		{
			parser->next = init_parse(line_read, cmd_line, head, env);
			parser = parser->next;
		}
		parsing_process(cmd_line, &parser);
		line_read = line_read + pipe_char_pos(line_read);
		if (line_read[0] != '\0')
			line_read++;
		free(cmd_line);
		i++;
	}
	parser = head;
	/*free(line_read - go_back);*/
	return (parser);
}

int	split_process(t_parse **parser, int memory, int pos)
{
	char	*text_to_parse;
	char	*substr_text;

	//printf("entered in split proccess\nmemory:%d, pos:%d, char c:%d\n",memory, pos, c);
	text_to_parse = (*parser)->command_text;
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

/*A CRIAR*/
int		def_parse_lim(t_parse **parser)
{
	char	*cmd_txt;
	int		i;
	int		mem;

	i = 0;
	mem = 0;
	cmd_txt = (*parser)->command_text;
	while (cmd_txt[i] != '\0')
	{
		if (is_special_char(cmd_txt + i) == 2 && is_between_quotes(cmd_txt, i) == 0)
		{
			(*parser)->special_char = ft_substr(cmd_txt, i, 1);
			return (i - 1);
		}
		else if (is_special_char(cmd_txt + i) != 0  && is_between_quotes(cmd_txt, i) == 0)
		{
			while (is_special_char(cmd_txt + i + mem) == 1 && is_between_quotes(cmd_txt, i + mem) == 0)
				mem++;
			(*parser)->special_char = ft_substr(cmd_txt, i, mem);
			return (i - 1);
		}
		i++;
	}
	return ft_strlen((*parser)->command_text);
}
/*Implantar funções para acoplar 25 linhas - Dpeois do while.*/
void	parsing_process(char *line_read, t_parse **parser)
{
	int	i;
	int	memory;

	i = set_main_command(parser, line_read);
	memory = i;
	while (line_read[i] != '\0' && i <= def_parse_lim(parser))
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

char	**get_env_path(t_env **env)
{
	t_env *temp;


	temp = (*env);
	while(temp != NULL)
	{
		if (ft_strcmp(temp->name, "PATH") == 0)
			return (ft_split(temp->value, ':'));
		temp = temp->next;
	}
	return (NULL);
}

t_parse	*init_parse(char *line_read, char *cmd_str, t_parse *head, t_env **env)
{
	t_parse	*parser_init;
	parser_init = malloc(sizeof(t_parse));
	parser_init->next = NULL;
	parser_init->entire_text = ft_strdup(line_read);
	parser_init->command_text = ft_strdup(cmd_str);
	parser_init->arguments = (char **)malloc(sizeof(char *));
	parser_init->arguments[0] = NULL;
	parser_init->env_path = get_env_path(env);
	parser_init->fd_in = STDIN_FILENO;
	parser_init->fd_out = STDOUT_FILENO;
	parser_init->special_char = NULL;
	parser_init->head = head;
	parser_init->pid = getpid();
	parser_init->exec_txt = NULL;
	parser_init->flags = NULL;
	return (parser_init);
}
