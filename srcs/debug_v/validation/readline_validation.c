/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_validation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrfern <gabrfern@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 00:05:33 by gabrfern          #+#    #+#             */
/*   Updated: 2024/11/17 00:22:30 by gabrfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	readline_writed(char *line_read)
{
	if (ft_strcmp(line_read, "") == 0
		|| is_blank_substr(line_read, 0, (int)ft_strlen(line_read)) == 1)
		return (0);
	return (1);
}

int	test_sp_char(char *line_read)
{
	int		valchar;
	int		i;

	valchar = 0;
	i = 0;
	if (is_blank_substr(line_read, 0, ft_strlen(line_read)))
		return (-1);
	while (line_read[i] != '\0')
	{
		if (is_btw_qts(line_read, i) != 0)
		{
			i++;
			continue ;
		}
		if (is_spchar(&line_read[i]) >= 1
			&& is_spchar(&line_read[i]) <= 2)
			valchar = check_along(line_read, i + 1);
		else if (is_spchar(&line_read[i]) == 3)
			valchar = check_along(line_read, i + 2);
		if (valchar != 0)
			return (-(valchar));
		i++;
	}
	return (1);
}

int	make_sp_validation(char *line_read)
{
	char	**splited_str;
	int		i;
	int		res;

	res = 0;
	i = 0;
	splited_str = ft_split(line_read, '|');
	if (count_arr_nb(splited_str) != num_of_pipes(line_read) + 1)
	{
		free_str_arr(splited_str);
		return (-4);
	}
	i = 0;
	while (splited_str[i])
	{
		res = test_sp_char(splited_str[i]);
		if (res <= 0)
		{
			free_str_arr(splited_str);
			return (res);
		}
		i++;
	}
	free_str_arr(splited_str);
	return (res);
}

int	validate_line_read(char *line_read)
{
	int	sp_res;

	sp_res = make_sp_validation(line_read);
	printf("test quote is >> %d\n", test_quote(line_read));
	printf("test special char is >> %d\n", sp_res);
	printf("you write anything on the readline is >> %d\n",
		readline_writed(line_read));
	if (!readline_writed(line_read))
		return (0);
	if (test_quote(line_read) == 0)
		ft_putendl_fd("bash: syntax error near unexpected token `quotes'", 2);
	else if (sp_res < 0)
		ft_putendl_fd("bash: syntax error near unexpected token", 2);
	else
		return (1);
	return (0);
}
