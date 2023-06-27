/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 11:22:19 by abelayad          #+#    #+#             */
/*   Updated: 2023/06/18 15:59:33 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_err_msg(t_err err)
{
	if (err.msg == ERRMSG_CMD_NOT_FOUND)
		return (ft_putstr_fd("minishell: ", 2), ft_putstr_fd(err.cause, 2),
			ft_putstr_fd(": command not found\n", 2), err.no);
	else if (err.msg == ERRMSG_NO_SUCH_FILE)
		return (ft_putstr_fd("minishell: ", 2), ft_putstr_fd(err.cause, 2),
			ft_putstr_fd(": No such file or directory\n", 2), err.no);
	else if (err.msg == ERRMSG_PERM_DENIED)
		return (ft_putstr_fd("minishell: ", 2), ft_putstr_fd(err.cause, 2),
			ft_putstr_fd(": Permission denied\n", 2), err.no);
	else if (err.msg == ERRMSG_AMBIGUOUS)
		return (ft_putstr_fd("minishell: ", 2), ft_putstr_fd(err.cause, 2),
			ft_putstr_fd(": ambiguous redirect\n", 2), err.no);
	else if (err.msg == ERRMSG_TOO_MANY_ARGS)
		return (ft_putstr_fd("minishell: exit: too many arguments\n", 2),
			err.no);
	else if (err.msg == ERRMSG_NUMERIC_REQUI)
		return (ft_putstr_fd("minishell: exit: ", 2),
			ft_putstr_fd(err.cause, 2),
			ft_putstr_fd(": numeric argument required\n", 2), err.no);
	return (0);
}
