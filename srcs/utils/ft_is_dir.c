/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrfern <gabrfern@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:25:31 by bkwamme           #+#    #+#             */
/*   Updated: 2024/11/18 01:07:10 by gabrfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_is_dir(char	*path)
{
	struct stat	st;

	if (stat(path, &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
			return (1);
		else
			return (0);
	}
	return (2);
}

int	check_slash(char *path)
{
	int	i;

	i = 0;
	while (path[i] != '\0')
		i++;
	if (i > 0 && path[i - 1] == '/')
		return (1);
	return (0);
}

char	*remove_slash(char *file)
{
	int		i;
	int		last_slash;
	char	*new_file;

	i = 0;
	while (file[i] != '\0')
		i++;
	last_slash = i - 1;
	i = 0;
	new_file = ft_calloc(sizeof(char), last_slash + 1);
	while (i != last_slash)
	{
		new_file[i] = file[i];
		i++;
	}
	free_str(&file);
	return (new_file);
}
