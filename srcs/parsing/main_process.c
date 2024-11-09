#include "../../includes/minishell.h"

int	get_redirect_part(t_parse **parser, char *cmd_txt, int mem)
{
	int	i;
	int	flip;

	flip = 0;
	i = mem;
	while (is_special_char(&cmd_txt[i]))
		i++;
	while (cmd_txt[i] != '\0')
	{
		while (!ft_isspace(cmd_txt[i]) && cmd_txt[i] != '\0' &&
		is_special_char(&cmd_txt[i]) == 0)
		{
			flip = 1;
			i++;
		}
		if (flip == 1)
			break;
		i++;
	}
	printf("out of redirect\n");
	(* parser)->redir = ft_realloc_list_and_str((* parser)->redir,
	 					ft_substr(cmd_txt, mem, i - mem));
	return (i);
}

static void	exclude_quotes(char **argument)
{
	char *copy_text;
	int	i;
	char flag;

	if (!*argument)
		return ;
	i = 1;
	flag = *argument[0];
	copy_text = NULL;
	if (*argument[0] != 39 && *argument[0] != 34)
		return ;
	copy_text = ft_strdup((*argument));
	free((*argument));
	(*argument) = NULL;
	while (copy_text[i] != '\0' && (copy_text[i]) != flag)
		i++;
	(*argument) = ft_substr(copy_text, 1, i - 1);
	free(copy_text);
}

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
	printf("starting main command\n");
	while (line_read[i_spc] != '\0' && ft_isspace(line_read[i_spc]))
		i_spc++;
	while (is_special_char(&line_read[i_spc]) >= 2 || ft_isspace(line_read[i_spc]))
	{
		if (is_special_char(&line_read[i_spc]) >= 2)
			i_spc = get_redirect_part(parser, line_read, i_spc);
		else
			i_spc++;
	}

	while (line_read[i_spc + i] != '\0' && (is_between_quotes(line_read, i_spc + i) > 0
		|| !ft_isspace(line_read[i_spc + i])))
		i++;
	if (!is_blank_substr(line_read, i_spc, i_spc + i))
		(*parser)->main_command = ft_substr(line_read, i_spc, i);
	exclude_quotes(&(*parser)->main_command);
	return (i_spc + i);
}

void parser_set(t_parse **parser, char *line_read, t_env **env, int i)
{
	char	*cmd_line;

	cmd_line = separate_line_read(line_read);
	if (i == 0)
		(*parser) = init_parse(line_read, cmd_line, NULL, env);
	else if (i == 1)
		(*parser)->next = init_parse(line_read, cmd_line, *parser, env);
	else if (i > 1)
		(*parser)->next = init_parse(line_read, cmd_line,(*parser)->head, env);
	if (i > 0)
	{
		(*parser) = (*parser)->next;
		(*parser)->next = NULL;
	}
	free(cmd_line);
}

/*Preciso validar parte da leitura em cima do texto da esquerda pra direita.*/
/*(incomplete) maybe this function will get all the constructors and make the treatment of the line buffer.---*/
t_parse	*main_line_process(char *line_read, t_env **env)
{
	t_parse	*parser;
	char	*cmd_line;
	int		i;

	parser = NULL;
	i = 0;
	if (!validate_line_read(line_read, env))
		return NULL;
	while (pipe_char_pos(line_read) <= (int)ft_strlen(line_read) && line_read[0] != '\0')
	{
		cmd_line = separate_line_read(line_read);
		parser_set(&parser, line_read, env, i);
		parsing_process(cmd_line, &parser, env);
		line_read = line_read + pipe_char_pos(line_read);
		if (line_read[0] != '\0')
			line_read++;
		i++;
		free(cmd_line);
		cmd_line = NULL;
	}
	if (parser->head != NULL)
		parser = parser->head;
	return (parser);
}

int	split_process(t_parse **parser, int memory, int pos)
{
	char	*text_to_parse;
	char	*substr_text;
	char	**text_spl;

	text_spl = NULL;
	text_to_parse = (*parser)->command_text;
	printf("text to parse is: %s\n",text_to_parse);
	//printf("text to parse variable is:%s\n", text_to_parse);
	if (is_between_quotes(text_to_parse, memory) == 0)
	{
		if (is_blank_substr(text_to_parse, memory, pos))
			return (0);
		substr_text = ft_substr(text_to_parse, memory, (pos - memory));
		text_spl = ft_split(substr_text, ' ');
		free(substr_text);
		//printf("substr text: %s\n", substr_text);
		(*parser)->arguments = ft_realloc_two_lists((*parser)->arguments, text_spl);
	}
	else
	{
		substr_text = ft_substr(text_to_parse, memory, pos - memory);
		(*parser)->arguments = ft_realloc_list_and_str((*parser)->arguments, substr_text);
	}
	printf("SPLIT PROCESS ENDED SUCCESS\n");
	return (1);
}

/*A CRIAR*/
int		def_parse_lim(t_parse **parser)
{
	char	*cmd_txt;
	int		i;

	i = 0;
	cmd_txt = (*parser)->command_text;
	while (cmd_txt[i] != '\0')
	{
		if (is_special_char(cmd_txt + i) == 1 && is_between_quotes(cmd_txt, i) == 0)
		{
			printf("entered here\n");
			(*parser)->special_char = ft_substr(cmd_txt, i, 1);
			return (i - 1);
		}
		i++;
	}
	return ft_strlen((*parser)->command_text);
}
/*Implantar funções para acoplar 25 linhas - Dpeois do while.*/
void	parsing_process(char *line_read, t_parse **parser, t_env **env)
{
	int	i;
	int	memory;
	char	*exp_text;

	env_and_quotes(parser, line_read, env);
	exp_text = (*parser)->command_text;

	printf("text expanded is: %s\n", exp_text);
	i = set_main_command(parser, exp_text);
	memory = i;
	while (exp_text[i] != '\0' && i <= def_parse_lim(parser))
	{
		if (is_between_quotes(exp_text, i) == 0 && is_special_char(exp_text + i) >= 2)
		{
			split_process(parser, memory, i);
			printf("entering redirect\n");
			i = get_redirect_part(parser, exp_text, i);
			memory = i;
			continue;
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
	parser_init->entire_text = ft_strdup(line_read);//freed (free_parser_str)
	parser_init->command_text = ft_strdup(cmd_str);//freed (free_parser_str)
	parser_init->main_command = NULL; //freed (free_parser_str)
	parser_init->exec_txt = NULL;
	parser_init->env_path = get_env_path(env);
	parser_init->fd_in = STDIN_FILENO;
	parser_init->fd_out = STDOUT_FILENO;
	parser_init->special_char = NULL;
	parser_init->head = head;
	parser_init->status = 0;
	parser_init->pid = getpid();
	parser_init->arguments = NULL;
	parser_init->redir = NULL;
	parser_init->next = NULL;
	return (parser_init);
}
