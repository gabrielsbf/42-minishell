/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrfern <gabrfern@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 23:01:51 by gabrfern          #+#    #+#             */
/*   Updated: 2024/11/17 00:06:50 by gabrfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_redirect_part(t_parse **parser, char *cmd_txt, int mem)
{
	int	i;
	int	flip;

	flip = 0;
	i = mem;
	while (is_spchar(&cmd_txt[i]))
		i++;
	while (cmd_txt[i] != '\0')
	{
		while ((!ft_isspace(cmd_txt[i])
				|| is_btw_qts(cmd_txt, i) > 0) && cmd_txt[i] != '\0'
			&& is_spchar(&cmd_txt[i]) == 0)
		{
			flip = 1;
			i++;
		}
		if (flip == 1)
			break ;
		i++;
	}
	(*parser)->redir = ft_realloc_list_and_str((*parser)->redir,
			ft_substr(cmd_txt, mem, i - mem));
	return (i);
}

int	split_process(t_parse **parser, int memory, int pos)
{
	char	*text_to_parse;
	char	*substr_text;
	char	**text_spl;

	text_spl = NULL;
	text_to_parse = (*parser)->command_text;
	if (is_btw_qts(text_to_parse, memory) == 0)
	{
		if (is_blank_substr(text_to_parse, memory, pos))
			return (0);
		substr_text = ft_substr(text_to_parse, memory, (pos - memory));
		exclude_quotes(&substr_text);
		text_spl = ft_split(substr_text, ' ');
		free_str(&substr_text);
		(*parser)->arguments = ft_realloc_two_lists(
				(*parser)->arguments, text_spl);
	}
	else
	{
		substr_text = ft_substr(text_to_parse, memory, pos - memory);
		exclude_quotes(&substr_text);
		(*parser)->arguments = ft_realloc_list_and_str(
				(*parser)->arguments, substr_text);
	}
	return (1);
}

int	split_with_quote(t_parse **parser, char *exp_text, int *i, int *memory)
{
	if (is_btw_qts(exp_text, *i) == 0
		&& is_spchar(exp_text + *i) >= 2)
	{
		split_process(parser, *memory, *i);
		*i = get_redirect_part(parser, exp_text, *i);
		*memory = *i;
		return (0);
	}
	if (is_btw_qts(exp_text, *i) == exp_text[*i]
		|| is_btw_qts(exp_text, *i) == exp_text[*i] * 2)
		split_process(parser, *memory, *i);
	else
	{
		(*i) = (*i) + 1;
		return (0);
	}
	if (is_btw_qts(exp_text, *i) >= 34
		&& is_btw_qts(exp_text, *i) <= 39)
		*memory = *i;
	else
	{
		*memory = (*i) + 1;
		(*i) = (*i) + 1;
	}
	return (1);
}

/*Implantar funções para acoplar 25 linhas - Dpeois do while.*/
void	parsing_process(char **line_read, t_parse **parser, t_env **env)
{
	int		i;
	int		memory;
	char	*exp_text;
	int		parse_lim;

	env_and_quotes(parser, line_read, env);
	exp_text = (*parser)->command_text;
	i = set_main_command(parser, exp_text);
	memory = i;
	parse_lim = def_parse_lim(parser);
	while (exp_text[i] != '\0' && i < parse_lim)
	{
		if (split_with_quote(parser, exp_text, &i, &memory) == 0)
			continue ;
		if (exp_text[i] == '\0')
			break ;
		if (is_spchar(&exp_text[i]))
			i--;
		i++;
	}
	if (memory == i)
		return ;
	split_process(parser, memory, i);
}

/*
(complete) maybe this function will get all the constructors and make
 the treatment of the line buffer.
 */
t_parse	*main_line_process(char *line_read, t_env **env)
{
	t_parse	*parser;
	char	*cmd_line;
	int		i;
	char	*temp;

	temp = line_read;
	parser = NULL;
	i = 0;
	if (!validate_line_read(temp))
		return (NULL);
	while (temp[0] != '\0' && pipe_char_pos(temp) <= (int)ft_strlen(temp))
	{
		cmd_line = separate_line_read(temp);
		parser_set(&parser, temp, env, i);
		parsing_process(&cmd_line, &parser, env);
		temp = temp + pipe_char_pos(temp);
		if (temp[0] != '\0')
			temp++;
		free_str(&cmd_line);
		i++;
	}
	if (parser->head != NULL)
		parser = parser->head;
	return (parser);
}
