/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 00:45:11 by abelayad          #+#    #+#             */
/*   Updated: 2023/02/02 16:08:49 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_matchset(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static char	*ft_trimmer(char const *s1, char const *set)
{	
	size_t	i;
	size_t	j;
	char	*trimmed;

	i = 0;
	while (s1[i] && ft_matchset(s1[i], set))
		i++;
	j = 0;
	while (s1[i + j])
		j++;
	while (j && ft_matchset(s1[i + (j - 1)], set))
		j--;
	trimmed = ft_calloc(j + 1, sizeof(char));
	if (!trimmed)
		return (NULL);
	while (j && j--)
		trimmed[j] = s1[i + j];
	return (trimmed);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	if (!s1)
		return (NULL);
	if (!set)
		return (NULL);
	return (ft_trimmer(s1, set));
}
