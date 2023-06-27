/* ************************************************************************** */
/*	                                                                          */
/*                                                        :::      ::::::::   */
/*   parser_clear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:47:04 by abelayad          #+#    #+#             */
/*   Updated: 2023/05/16 21:28:44 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clear_io_list(t_io_node **lst)
{
	t_io_node	*curr_node;
	t_io_node	*next;

	curr_node = *lst;
	if (!curr_node)
		return ;
	while (curr_node)
	{
		free(curr_node->value);
		ft_free_char2(curr_node -> expanded_value);
		next = curr_node->next;
		free(curr_node);
		curr_node = next;
	}
	*lst = NULL;
}

void	ft_clear_cmd_node(t_node *node)
{
	if (!node)
		return ;
	ft_clear_io_list(&(node -> io_list));
	free(node -> args);
	ft_free_char2(node -> expanded_args);
}

void	ft_recursive_clear_ast(t_node *node)
{
	if (!node)
		return ;
	if (node -> type == N_CMD)
		ft_clear_cmd_node(node);
	else
	{
		if (node->left)
			ft_recursive_clear_ast(node->left);
		if (node->right)
			ft_recursive_clear_ast(node->right);
	}
	free(node);
}

void	ft_clear_ast(t_node **ast)
{
	ft_recursive_clear_ast(*ast);
	*ast = NULL;
	ft_clear_token_list(&g_minishell.tokens);
}
