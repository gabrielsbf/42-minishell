#include "../../includes/minishell.h"

void	update_env_status(t_env **env, int	status)
{
	t_env	*temp;

	temp = (*env);
	while (temp->next)
	{
		temp = temp->next;
		if (temp->next == NULL)
			temp->value = ft_itoa(status);
	}
}

t_env	*create_env_status(t_env *head)
{
	t_env	*status;
	char	*name;

	name = ft_calloc(sizeof(char), 2);
	name[0] = '?';
	status = ft_calloc(sizeof(t_env), 1);
	status->head = head;
	status->name = name;
	status->value = ft_itoa(0);
	status->next = NULL;
	return (status);
}

void	add_env_status(t_env **env)
{
	t_env	*temp;

	temp = (*env);
	while (temp->next)
		temp = temp->next;
	if (temp->next == NULL)
		temp->next = create_env_status(temp);
}
