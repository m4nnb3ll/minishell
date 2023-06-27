/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 20:10:59 by abelayad          #+#    #+#             */
/*   Updated: 2023/06/18 16:26:37 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_get_io_list(t_io_node **io_list)
{
	t_token_type		redir_type;
	t_io_node			*tmp_io_node;

	if (g_minishell.parse_err.type)
		return (false);
	while (g_minishell.curr_token && ft_is_redir(g_minishell.curr_token->type))
	{
		redir_type = g_minishell.curr_token->type;
		ft_get_next_token();
		if (!g_minishell.curr_token)
			return (ft_set_parse_err(E_SYNTAX), false);
		if (g_minishell.curr_token->type != T_IDENTIFIER)
			return (ft_set_parse_err(E_SYNTAX), false);
		tmp_io_node = ft_new_io_node(redir_type, g_minishell.curr_token->value);
		if (!tmp_io_node)
			return (ft_set_parse_err(E_MEM), false);
		ft_append_io_node(io_list, tmp_io_node);
		ft_get_next_token();
	}
	return (true);
}

bool	ft_join_args(char **args)
{
	char	*to_free;

	if (g_minishell.parse_err.type)
		return (false);
	if (!*args)
		*args = ft_strdup("");
	if (!*args)
		return (false);
	while (g_minishell.curr_token
		&& g_minishell.curr_token -> type == T_IDENTIFIER)
	{
		to_free = *args;
		*args = ft_strjoin_with(*args, g_minishell.curr_token -> value, ' ');
		if (!*args)
			return (free(to_free), false);
		free(to_free);
		ft_get_next_token();
	}
	return (true);
}

t_node	*ft_get_simple_cmd(void)
{
	t_node	*node;

	if (g_minishell.parse_err.type)
		return (NULL);
	node = ft_new_node(N_CMD);
	if (!node)
		return (ft_set_parse_err(E_MEM), NULL);
	while (g_minishell.curr_token
		&& (g_minishell.curr_token->type == T_IDENTIFIER
			|| ft_is_redir(g_minishell.curr_token->type)))
	{
		if (g_minishell.curr_token->type == T_IDENTIFIER)
		{
			if (!ft_join_args(&(node -> args)))
				return (ft_clear_cmd_node(node), ft_set_parse_err(E_MEM), NULL);
		}
		else if (ft_is_redir(g_minishell.curr_token->type))
		{
			if (!ft_get_io_list(&(node->io_list)))
				return (free(node->args), free(node), NULL);
		}
	}
	return (node);
}
