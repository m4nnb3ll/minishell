/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 22:55:17 by abelayad          #+#    #+#             */
/*   Updated: 2023/06/18 16:30:09 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*ft_term(void)
{
	t_node	*node;

	if (g_minishell.parse_err.type)
		return (NULL);
	if (ft_curr_token_is_binop() || g_minishell.curr_token->type == T_C_PARENT)
		return (ft_set_parse_err(E_SYNTAX), NULL);
	else if (g_minishell.curr_token->type == T_O_PARENT)
	{
		ft_get_next_token();
		node = ft_expression(0);
		if (!node)
			return (ft_set_parse_err(E_MEM), NULL);
		if (!g_minishell.curr_token
			|| g_minishell.curr_token->type != T_C_PARENT)
			return (ft_set_parse_err(E_SYNTAX), node);
		ft_get_next_token();
		return (node);
	}
	else
		return (ft_get_simple_cmd());
}

t_node	*ft_expression(int min_prec)
{
	t_node			*left;
	t_node			*right;
	int				n_prec;
	t_token_type	op;

	if (g_minishell.parse_err.type || !g_minishell.curr_token)
		return (NULL);
	left = ft_term();
	if (!left)
		return (NULL);
	while (ft_curr_token_is_binop() && ft_curr_token_prec() >= min_prec)
	{
		op = g_minishell.curr_token->type;
		ft_get_next_token();
		if (!g_minishell.curr_token)
			return (ft_set_parse_err(E_SYNTAX), left);
		n_prec = ft_prec(op) + 1;
		right = ft_expression(n_prec);
		if (!right)
			return (left);
		left = ft_combine(op, left, right);
		if (!left)
			return (ft_clear_ast(&left), ft_clear_ast(&right), NULL);
	}
	return (left);
}

t_node	*ft_combine(t_token_type op, t_node *left, t_node *right)
{
	t_node	*node;

	if (g_minishell.parse_err.type)
		return (NULL);
	node = ft_new_node(ft_get_node_type(op));
	if (!node)
		return (ft_set_parse_err(E_MEM), NULL);
	node -> left = left;
	node -> right = right;
	return (node);
}

t_node	*ft_parse(void)
{
	t_node	*ast;

	g_minishell.curr_token = g_minishell.tokens;
	ast = ft_expression(0);
	if (g_minishell.curr_token)
		return (ft_set_parse_err(E_SYNTAX), ast);
	return (ast);
}
