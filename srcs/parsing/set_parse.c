/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkwamme <bkwamme@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 23:33:17 by gabrfern          #+#    #+#             */
/*   Updated: 2024/11/19 18:49:30 by bkwamme          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	def_parse_lim(t_parse **parser)
{
	char	*cmd_txt;
	int		i;

	i = 0;
	cmd_txt = (*parser)->command_text;
	while (cmd_txt[i] != '\0')
	{
		if (is_spchar(cmd_txt + i) == 1
			&& is_btw_qts(cmd_txt, i) == 0)
		{
			(*parser)->special_char = ft_substr(cmd_txt, i, 1);
			return (i - 1);
		}
		i++;
	}
	return (ft_strlen((*parser)->command_text));
}

char	**get_env_path(t_env **env)
{
	t_env	*temp;

	temp = (*env);
	while (temp != NULL)
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

	parser_init = (t_parse *)malloc(sizeof(t_parse));
	parser_init->entire_text = ft_strdup(line_read);
	parser_init->command_text = ft_strdup(cmd_str);
	parser_init->main_command = NULL;
	parser_init->exec_txt = NULL;
	parser_init->env_path = get_env_path(env);
	parser_init->fd_in = STDIN_FILENO;
	parser_init->fd_out = STDOUT_FILENO;
	parser_init->special_char = NULL;
	parser_init->head = head;
	parser_init->status = 0;
	parser_init->fd_hdoc = 0;
	parser_init->pid = getpid();
	parser_init->arguments = (char **)malloc(sizeof(char *));
	parser_init->arguments[0] = NULL;
	parser_init->redir = NULL;
	parser_init->next = NULL;
	return (parser_init);
}

void	parser_set(t_parse **parser, char *line_read, t_env **env, int i)
{
	char	*cmd_line;

	cmd_line = separate_line_read(line_read);
	if (i == 0)
		(*parser) = init_parse(line_read, cmd_line, NULL, env);
	else if (i == 1)
		(*parser)->next = init_parse(line_read, cmd_line, *parser, env);
	else if (i > 1)
		(*parser)->next = init_parse(line_read, cmd_line, (*parser)->head, env);
	if (i > 0)
	{
		(*parser) = (*parser)->next;
		(*parser)->next = NULL;
	}
	free_str(&cmd_line);
}

int	set_main_command(t_parse **parser, char *line_read)
{
	int	i;
	int	i_spc;

	i_spc = 0;
	i = 0;
	while (line_read[i_spc] != '\0' && ft_isspace(line_read[i_spc]))
		i_spc++;
	while (!is_btw_qts(line_read, i_spc + i) && (ft_isspace(line_read[i_spc]
				|| is_spchar(&line_read[i_spc]) >= 2)))
	{
		if (is_spchar(&line_read[i_spc]) >= 2)
			i_spc = get_redirect_part(parser, line_read, i_spc);
		else
			i_spc++;
	}
	while (line_read[i_spc + i] != '\0' && !ft_isspace(line_read[i_spc + i])
		&& !is_spchar(&line_read[i_spc + i]))
		i++;
	while (is_btw_qts(line_read, i_spc + i) > 0)
		i++;
	if (is_blank_substr(line_read, i_spc, i_spc + i) || i == 0)
		return (0);
	(*parser)->main_command = ft_substr(line_read, i_spc, i);
	exclude_quotes(&(*parser)->main_command);
	return (i_spc + i);
}
