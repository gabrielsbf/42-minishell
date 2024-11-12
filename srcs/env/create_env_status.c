/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env_status.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrfern <gabrfern@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 01:36:51 by bkwamme           #+#    #+#             */
/*   Updated: 2024/11/10 17:26:46 by gabrfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_env_status(t_env **env, int status)
{
	t_env	*temp;

	temp = (*env);
	while (temp->next)
	{
		temp = temp->next;
		if (temp->next == NULL)
		{
			free_str(&temp->value);
			temp->value = ft_itoa(status);
		}
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

void	verify_env_head(t_env **env)
{
	t_env	*temp;
	int		x;

	temp = (*env);
	x = 0;
	if ((*env)->head == NULL)
	{
		x++;
		printf("ENV HEAD IS NULL\n");
		temp = temp->next;
	}
	while (temp)
	{
		x++;
		printf("loop head print%s\n", temp->name);
		printf("loop head print%s\n", temp->head->name);
		temp = temp->next;
	}
	printf("env num%d\n", x);
}

void	add_env_status(t_env **env)
{
	t_env	*temp;

	temp = (*env);
	while (temp->next)
		temp = temp->next;
	if (temp->next == NULL)
		temp->next = create_env_status((*env));
}
