/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrfern <gabrfern@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 01:28:40 by bkwamme           #+#    #+#             */
/*   Updated: 2024/11/21 19:56:02 by gabrfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	pwd_update(t_env **env)
{
	t_env	*temp;
	char	cwd[4097];
	int		i;

	i = 0;
	getcwd(cwd, sizeof(cwd));
	temp = (*env);
	while (temp != NULL)
	{
		if (ft_strcmp(temp->name, "PWD") == 0)
		{
			free_str(&temp->value);
			temp->value = ft_calloc(sizeof(char), ft_strlen(cwd) + 1);
			while (cwd[i] != '\0')
			{
				temp->value[i] = cwd[i];
				i++;
			}
			return ;
		}
		temp = temp->next;
	}
}

void	oldpwd_update(t_env **env)
{
	t_env	*temp;
	char	cwd[4097];
	int		i;

	i = 0;
	getcwd(cwd, sizeof(cwd));
	temp = (*env);
	while (temp != NULL)
	{
		if (ft_strcmp(temp->name, "OLDPWD") == 0)
		{
			free_str(&temp->value);
			temp->value = ft_calloc(sizeof(char), ft_strlen(cwd) + 1);
			while (cwd[i] != '\0')
			{
				temp->value[i] = cwd[i];
				i++;
			}
			return ;
		}
		temp = temp->next;
	}
}

char	*oldpwd_value(t_env **env)
{
	t_env	*temp;

	temp = (*env);
	while (temp)
	{
		if (ft_strcmp(temp->name, "OLDPWD") == 0)
			return (ft_strdup(temp->value));
		temp = temp->next;
	}
	return (NULL);
}

int	special_chdir(char *argument, char *oldpwd, t_env **env, int *status)
{
	if (!argument || ft_strcmp(argument, "~") == 0)
	{
		*status = -1;
		if (chdir(check_name_in_env(env, "HOME")) == -1)
			*status = 1;
		if (argument && ft_strcmp(argument, "~") == 0)
		{
			if (chdir(getenv("HOME")) == -1)
				*status = 1;
		}
	}
	if (argument && ft_strcmp(argument, "-") == 0)
	{
		*status = -1;
		if (oldpwd)
		{
			if (chdir(oldpwd) == -1)
				*status = 1;
		}
	}
	if (*status == 1)
		ft_putendl_fd("cd: ERROR", 2);
	return (*status);
}

int	cd_manager(char *argument, t_env **env)
{
	char	*oldpwd;
	int		status;

	status = 0;
	oldpwd = oldpwd_value(env);
	oldpwd_update(env);
	special_chdir(argument, oldpwd, env, &status);
	if (status == 0 && chdir(argument) == -1)
	{
		ft_putendl_fd("cd: ERROR", 2);
		status = 1;
	}
	if (oldpwd)
		free_str(&oldpwd);
	pwd_update(env);
	if (status == -1)
		return (0);
	return (status);
}
