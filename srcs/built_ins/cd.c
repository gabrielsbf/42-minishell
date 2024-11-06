#include "../../includes/minishell.h"

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
			free(temp->value);
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
			free(temp->value);
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

void	free_oldpwd(char *oldpwd)
{
	if (oldpwd)
		free(oldpwd);
}

int	cd_manager(char *argument, t_env **env)
{
	char	*oldpwd;

	oldpwd = oldpwd_value(env);
	oldpwd_update(env);
	if (!argument || ft_strcmp(argument, "~") == 0)
		chdir(check_name_in_env(env, "HOME"));
	if (argument && ft_strcmp(argument, "-") == 0)
		chdir(oldpwd);
	if (chdir(argument) == -1)
	{
		ft_putendl_fd("cd: ERROR", 2);
		free_oldpwd(oldpwd);
		return (1);
	}
	free_oldpwd(oldpwd);
	pwd_update(env);
	return (0);
}
