/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_exp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkwamme <bkwamme@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 01:42:45 by bkwamme           #+#    #+#             */
/*   Updated: 2024/11/09 01:43:16 by bkwamme          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	replace_here(char **text_in, char *find, char *replace)
{
	char	*line_here;
	int		new_alloc;
	int		i_old;
	int		i_new;

	i_old = 0;
	i_new = 0;
	new_alloc = ft_strlen((*text_in))
		- ft_strlen(find) + ft_strlen(replace) + 1;
	line_here = ft_strdup((*text_in));
	free((*text_in));
	(*text_in) = (char *)malloc(new_alloc * sizeof(char));
	printf("len alloqued for text is: %d\n", new_alloc);
	while (line_here[i_old] != '\0')
	{
		if (line_here[i_old] == '$')
		{
			if (ft_strncmp(&line_here[i_old + 1], find, ft_strlen(find)) == 0)
			{
				// printf("ENTERED IN THE EXPANSION MODULE\nreplacing %s to %s, on a %d len, index in i new is: %d and i_old is: %d\n", &(*text_in)[i_new], replace, (int)ft_strlen(replace)+1, i_new, i_old);
				ft_strlcpy(&(*text_in)[i_new], replace, ft_strlen(replace)+1);
				i_new = i_new + ft_strlen(replace);
				i_old = i_old + ft_strlen(find) + 1;
				// printf("final of process\ni_new is %d and i_old is %d\n", i_new, i_old);
				// printf("EXECUTED COPYSTR: newstring is: %s\n", (*text_in));
			}
		}
		if (line_here[i_old] != '\0')
		{
			// printf("line here is not null yet, char is: %d", line_here[i_old]);
			(*text_in)[i_new] = line_here[i_old];
			i_old++;
			i_new++;
		}
	}
	// printf("END OF WHILE LOOP - i_new is %d and , text is: %s\n", i_new, (*text_in));
	if ((*text_in)[i_new] != '\0')
		(*text_in)[i_new] = '\0';
}

int	expand_heredoc(char **text_in, int i_cipher, t_env **envs)
{
	char	*env_name;
	char	*env_value;
	int		memory;

	memory = i_cipher + 1;
	while((*text_in)[memory] != '\0' && is_env_available((*text_in)[memory]))
		memory++;
	env_name = ft_substr((*text_in), i_cipher + 1, memory - i_cipher - 1);
	env_value = check_name_in_env(envs, env_name);
	if (env_value == NULL)
		return 0;
	replace_here(text_in, env_name, env_value);
	free(env_name);
	return (1);
}

int	here_valid_qt(char *text, int memory)
{
	if (is_between_quotes(text, memory))
		return (1);
	else
		return (1);
}

void	here_expansion(char **text, t_env **envs)
{
	int	i;
	int expand_bool;
	char *temp;

	temp = (*text);
	i = 0;
	while (temp[i] != '\0')
	{
		expand_bool = 0;
		if (temp[i] == '$')
			expand_bool = here_valid_qt(temp, i);
		if (expand_bool == 1)
		{
			if (expand_heredoc(text, i, envs))
				i = 0;
			// printf("RESETED HEREDOC\nEXPANSION WAS FINISHED, text is: %s\n", (*text));
		}
		i++;
	}
	// printf("End of HERE EXPANSION -> Buffer is: %s\n", (*text));
}

