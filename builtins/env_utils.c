/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 19:13:32 by abelayad          #+#    #+#             */
/*   Updated: 2023/06/17 21:43:45 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_env_entry_exists(char *key)
{
	t_env	*envlst;

	envlst = g_minishell.envlst;
	while (envlst)
	{
		if (!ft_strcmp(key, envlst->key))
			return (true);
		envlst = envlst->next;
	}
	return (false);
}

static t_env	*ft_envlst_new(char *key, char *value)
{
	t_env	*new;

	new = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_garbage_collector(ft_strdup(key), false);
	if (value)
		new->value = ft_garbage_collector(ft_strdup(value), false);
	new->next = NULL;
	return (new);
}

char	*ft_get_envlst_val(char *key)
{
	t_env	*envlst;

	envlst = g_minishell.envlst;
	while (envlst)
	{
		if (!ft_strcmp(key, envlst->key))
			return (envlst->value);
		envlst = envlst->next;
	}
	return (NULL);
}

void	ft_envlst_back(t_env *new)
{
	t_env	*curr;

	if (!g_minishell.envlst)
	{
		g_minishell.envlst = new;
		return ;
	}
	curr = g_minishell.envlst;
	while (curr && curr->next)
		curr = curr->next;
	curr->next = new;
}

void	ft_update_envlst(char *key, char *value, bool create)
{
	t_env	*envlst;

	envlst = g_minishell.envlst;
	while (envlst)
	{
		if (!ft_strcmp(key, envlst->key))
		{
			if (value)
				envlst->value = ft_garbage_collector(ft_strdup(value), false);
			return ;
		}
		envlst = envlst->next;
	}
	if (create)
		ft_envlst_back(ft_envlst_new(key, value));
}
