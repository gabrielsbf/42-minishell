/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_path_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkwamme <bkwamme@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:23:59 by bkwamme           #+#    #+#             */
/*   Updated: 2024/11/20 01:12:18 by bkwamme          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_arg_len(t_parse *parser)
{
	t_parse	*temp;
	int		i;

	i = 0;
	temp = parser;
	if (!(parser)->arguments)
		return (0);
	while (temp->arguments[i] != NULL)
		i++;
	return (i);
}

void	get_execargs(char *args, char **exec_arg, int arr_i)
{
	int		i;

	i = 0;
	while (args[i] != '\0')
	{
		exec_arg[arr_i][i] = args[i];
		i++;
	}
}

void	create_execargs(t_parse **parser)
{
	int		arg_len;
	int		i;

	i = 0;
	arg_len = get_arg_len((*parser)) + 1;
	(*parser)->exec_txt = ft_calloc(sizeof(char *), arg_len + 1);
	while (arg_len > i)
	{
		if (i == 0)
			(*parser)->exec_txt[i] = ft_strdup((*parser)->main_command);
		else
			(*parser)->exec_txt[i] = ft_strdup((*parser)->arguments[i - 1]);
		i++;
	}
	(*parser)->exec_txt[i] = NULL;
}

char	*create_path_exec(t_parse **parser)
{
	char	*path;
	char	*s;
	int		i;

	i = 0;
	path = NULL;
	s = NULL;
	if ((*parser)->main_command[0] != '/')
		s = ft_strjoin("/", (*parser)->main_command);
	else
		s = ft_strdup((*parser)->main_command);
	while ((*parser)->env_path && (*parser)->env_path[i] != NULL)
	{
		path = ft_strjoin((*parser)->env_path[i], s);
		if (ft_is_dir(path) == 1 || access(path, F_OK & X_OK) != 0)
		{
			free_str(&path);
			path = NULL;
		}
		else
			break ;
		i++;
	}
	free_str(&s);
	return (path);
}
