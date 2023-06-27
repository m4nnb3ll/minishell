/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 10:41:56 by abelayad          #+#    #+#             */
/*   Updated: 2023/06/18 16:03:51 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_isnumber(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (false);
		i++;
	}
	return (true);
}

static void	ft_skip_spaces_and_get_sign(char *s, int *i, int *sign)
{
	while (s[*i] && s[*i] == ' ')
		(*i)++;
	if (s[*i] == '+' || s[*i] == '-')
	{
		if (s[*i] == '-')
			*sign *= -1;
		(*i)++;
	}
}

static int	ft_exittoi(char *s)
{
	int					i;
	int					sign;
	int					exit_s;
	unsigned long long	result;

	i = 0;
	sign = 1;
	ft_skip_spaces_and_get_sign(s, &i, &sign);
	if (!ft_isnumber(s + i))
	{
		exit_s = ft_err_msg((t_err){ENO_EXEC_255, ERRMSG_NUMERIC_REQUI, s});
		(ft_clean_ms(), exit(exit_s));
	}
	result = 0;
	while (s[i])
	{
		result = (result * 10) + (s[i] - '0');
		if (result > LONG_MAX)
		{
			exit_s = ft_err_msg((t_err){ENO_EXEC_255, ERRMSG_NUMERIC_REQUI, s});
			(ft_clean_ms(), exit(exit_s));
		}
		i++;
	}
	return ((result * sign) % 256);
}

void	ft_exit(char **args)
{
	int	exit_s;

	exit_s = g_minishell.exit_s;
	if (args[1])
	{
		if (args[2] && ft_isnumber(args[1]))
		{
			exit_s = ft_err_msg(
					(t_err){ENO_GENERAL, ERRMSG_TOO_MANY_ARGS, NULL});
			(ft_clean_ms(), exit(exit_s));
		}
		else
			exit_s = ft_exittoi(args[1]);
	}
	(ft_clean_ms(), exit(exit_s));
}
