/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkwamme <bkwamme@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 01:32:12 by bkwamme           #+#    #+#             */
/*   Updated: 2024/11/14 12:01:27 by bkwamme          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	export_error(int *status, char *arguments)
{
	int	i;

	i = 0;
	if (ft_isalpha(arguments[0]) == 0 && arguments[0] != '_')
	{
		*status = 1;
		return (0);
	}
	while (arguments[i] != '\0')
	{
		if (arguments[i] == '=')
			return (1);
		if (ft_isalnum(arguments[i]) == 0 && arguments[i] != '_')
		{
			*status = 1;
			return (0);
		}
		i++;
	}
	return (0);
}

t_env	*add_export(t_env **env, char **arguments)
{
	t_env	*export;
	t_env	*status;
	t_env	*temp;

	temp = (*env);
	while (ft_strcmp(temp->name, "?") != 0)
		temp = temp->next;
	status = temp;
	export = (t_env *) malloc(sizeof(t_env) * 1);
	export->head = temp->head;
	export->next = status;
	export->name = get_env_name(arguments);
	export->value = get_env_value(arguments);
	return (export);
}

int	is_export_updated(t_env *env, char	**arguments)
{
	while (env && ft_strcmp(env->next->name, "?") != 0)
	{
		if (ft_strcmp(env->name, *arguments) == 0)
		{
			env->value = get_env_value(arguments);
			return (1);
		}
		env = env->next;
	}
	return (0);
}

int	export_to_env(t_env **env, char **arguments)
{
	t_env	*swap;
	int		iarg;
	int		status;

	status = 0;
	iarg = 0;
	swap = (*env);
	while ((arguments[iarg] != NULL))
	{
		if (!arguments[iarg] || export_error(&status, arguments[iarg]) == 0
			|| is_export_updated(swap, &arguments[iarg]) == 1)
		{
			iarg++;
			continue ;
		}
		while (ft_strcmp(swap->next->name, "?") != 0)
			swap = swap->next;
		swap->next = add_export(env, &arguments[iarg]);
		swap = swap->head;
		iarg++;
	}
	return (status);
}
