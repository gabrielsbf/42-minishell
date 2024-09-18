#include "../../includes/minishell.h"

void	envnode_sewing(t_env *swap, char **splitted_instructions)
{
	t_env	*prev_node;
	t_env	*node_remover;

	node_remover = NULL;
	prev_node = swap;
	swap = swap->next;
	while (swap != NULL)
	{
		if (ft_strcmp(swap->name, get_env_name(splitted_instructions)) == 0)
		{
			node_remover = swap;
			if (swap->next == NULL)
				prev_node->next = NULL;
			else
			{
				prev_node->next = swap;
				swap = swap->next;
			}
			free(node_remover);
			break ;
		}
		prev_node = swap;
		swap = swap->next;
	}
	swap = prev_node->head;
}

void	define_new_head(t_env **env)
{
	t_env	*new_head;
	t_env	*old_head;

	if(!(*env)->next)
	{
		free((*env));
		return ;
	}
	old_head = (*env);
	new_head = (*env)->next;
	(*env) = (*env)->next;
	while((*env)->next != NULL)
	{
		if ((*env) == new_head)
			(*env)->head = NULL;
		else
			(*env)->head = new_head;
		(*env) = (*env)->next;
	}
	(*env)->head = new_head;
	(*env) = new_head;
	free(old_head);
}

void	unset_from_env(t_env **env, char **splitted_instructions)
{
	t_env *swap;

	swap = (*env);
	if (!*splitted_instructions || !(*env))
		perror("ta erro isso ai menor");
	else if (ft_strcmp(swap->name, get_env_name(splitted_instructions)) == 0)
		define_new_head(env);
	else
		envnode_sewing(swap, splitted_instructions);
}
