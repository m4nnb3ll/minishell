/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 22:29:11 by abelayad          #+#    #+#             */
/*   Updated: 2023/04/10 23:16:02 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	base_digit(char c, int base)
{
	char	*low;
	char	*up;
	int		i;

	low = "0123456789abcdef";
	up = "0123456789ABCDEF";
	i = -1;
	while (++i < base)
		if (c == low[i] || c == up[i])
			return (i);
	return (-1);
}

int	ft_atoi_base(const char *str, int base)
{
	size_t		i;
	int			sign;
	long int	sum;

	if (!str)
		return (0);
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	sum = 0;
	while (base_digit(str[i], base) != -1)
	{
		sum = sum * base + base_digit(str[i], base);
		if (sum < 0)
			return ((sign != -1) * -1);
		i++;
	}
	return (sum * sign);
}
