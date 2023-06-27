/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 00:05:06 by abelayad          #+#    #+#             */
/*   Updated: 2023/02/22 17:27:49 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count(char const *s, char c)
{
	size_t	count;
	size_t	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && ++count)
			while (s[i] && s[i] != c)
				i++;
		while (s[i] && s[i] == c)
			i++;
	}
	return (count);
}

static char	**ft_allocater(char const *s, char c, char **strs)
{
	size_t	count;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		count = 0;
		if (s[i] != c)
		{
			while (s[i] && s[i] != c && ++count)
				i++;
			strs[j] = ft_calloc(count + 1, sizeof(char));
			if (!strs[j])
				return (NULL);
			j++;
		}
		while (s[i] && s[i] == c)
			i++;
	}
	return (strs);
}

static char	**ft_filler(char const *s, char c, char **strs)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	while (s[i] && strs[j])
	{
		if (s[i] != c)
		{
			k = 0;
			while (s[i] && s[i] != c)
				strs[j][k++] = s[i++];
			j++;
		}
		while (s[i] && s[i] == c)
			i++;
	}
	return (strs);
}

char	**ft_split(char const *s, char c)
{
	size_t		count;
	char		**strs;
	char		**tofree;

	if (!s)
		return (NULL);
	count = ft_count(s, c);
	strs = ft_calloc(count + 1, sizeof(char *));
	if (!strs)
		return (NULL);
	if (!count)
		return (strs);
	tofree = strs;
	strs = ft_allocater(s, c, strs);
	if (!strs)
		return (ft_free_char2(tofree), NULL);
	return (ft_filler(s, c, strs));
}
