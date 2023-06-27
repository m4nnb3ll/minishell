/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 17:07:56 by abelayad          #+#    #+#             */
/*   Updated: 2023/06/18 16:19:40 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void
	ft_exec_pipe_child(t_node *node, int pfds[2], t_ast_direction direction)
{
	int	status;

	if (direction == TD_LEFT)
	{
		close(pfds[0]);
		dup2(pfds[1], STDOUT_FILENO);
		close(pfds[1]);
	}
	else if (direction == TD_RIGHT)
	{
		close(pfds[1]);
		dup2(pfds[0], STDIN_FILENO);
		close(pfds[0]);
	}
	status = ft_exec_node(node, true);
	(ft_clean_ms(), exit(status));
}

int	ft_get_exit_status(int status)
{
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}

static	int	ft_exec_pipeline(t_node *tree)
{
	int	status;
	int	pfds[2];
	int	pid_l;
	int	pid_r;

	g_minishell.signint_child = true;
	pipe(pfds);
	pid_l = fork();
	if (!pid_l)
		ft_exec_pipe_child(tree->left, pfds, TD_LEFT);
	else
	{
		pid_r = fork();
		if (!pid_r)
			ft_exec_pipe_child(tree->right, pfds, TD_RIGHT);
		else
		{
			(close(pfds[0]), close(pfds[1]),
				waitpid(pid_l, &status, 0), waitpid(pid_r, &status, 0));
			g_minishell.signint_child = false;
			return (ft_get_exit_status(status));
		}
	}
	return (ENO_GENERAL);
}

int	ft_exec_node(t_node *tree, bool piped)
{
	int	status;

	if (!tree)
		return (1);
	if (tree->type == N_PIPE)
		return (ft_exec_pipeline(tree));
	else if (tree->type == N_AND)
	{
		status = ft_exec_node(tree->left, false);
		if (status == ENO_SUCCESS)
			return (ft_exec_node(tree->right, false));
		return (status);
	}
	else if (tree->type == N_OR)
	{
		status = ft_exec_node(tree->left, false);
		if (status == ENO_SUCCESS)
			return (status);
		return (ft_exec_node(tree->right, false));
	}
	else
		return (ft_exec_simple_cmd(tree, piped));
	return (ENO_GENERAL);
}
