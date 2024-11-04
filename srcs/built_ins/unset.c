#include "../../includes/minishell.h"

void	free_env_node(t_env *env)
{
	env->head = NULL;
	free(env->name);
	free(env->value);
	free(env);
}

void	envnode_sewing(t_env **env, char **splitted_instructions)
{
	t_env	*prev_node;
	t_env	*node_remover;

	node_remover = NULL;
	prev_node = (*env);
	while ((*env) != NULL)
	{
		if (ft_strcmp((*env)->name, get_env_name(splitted_instructions)) == 0)//WSL2_GUI_APPS_ENABLED
		{
			node_remover = (*env);
			if ((*env)->next == NULL)
				prev_node->next = NULL;
			else
			{
				(*env) = (*env)->next;
				prev_node->next = (*env);
			}
			free_env_node(node_remover);
			break ;
		}
		prev_node = (*env);
		(*env) = (*env)->next;
	}
	(*env) = prev_node->head;
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

void	unset_from_env(t_env **env, char **arguments)
{
	t_env 	*swap;
	int		iarg;

	iarg = 0;
	swap = (*env);
	while (arguments[iarg])
	{
		if (!(*env))
			ft_putendl_fd("UNSET ENV ERROR", 2);
		if (!arguments[iarg] || ft_strcmp(arguments[iarg], "?") == 0)
		{
			iarg++;
			continue ;
		}
		else if (ft_strcmp(swap->name, get_env_name(&arguments[iarg])) == 0)
			define_new_head(env);
		else
			envnode_sewing(env, &arguments[iarg]);
		iarg++;
	}
}
