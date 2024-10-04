#include "../../includes/minishell.h"

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
void	cd_manager(char *argument, t_env **env)
{
	oldpwd_update(env);
	if (!argument)
		chdir(getenv("HOME"));
	else if (chdir(argument) == -1)
		ft_putstr_fd("CD ERROR\n", 2);
}
