/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 20:55:39 by abelayad          #+#    #+#             */
/*   Updated: 2022/10/13 21:02:34 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_filler(char *nums, int num_len, int sign)
{
	size_t	i;
	char	*str;

	str = ft_calloc(sign + num_len + 1, sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	if (sign)
		str[i++] = '-';
	while (--num_len >= 0)
		str[i++] = nums[num_len];
	return (str);
}

char	*ft_itoa(int n)
{
	int			sign;
	char		nums[10];
	char		*str;
	int			i;
	long int	num;

	num = n;
	sign = 0;
	if (!num)
	{
		str = ft_calloc(2, sizeof(char));
		if (!str)
			return (NULL);
		str[0] = '0';
		return (str);
	}
	i = 0;
	if (num < 0 && ++sign)
		num *= -1;
	while (num)
	{
		nums[i++] = (num % 10) + '0';
		num /= 10;
	}
	return (ft_filler(nums, i, sign));
}
