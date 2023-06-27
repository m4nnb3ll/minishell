/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 00:37:08 by abelayad          #+#    #+#             */
/*   Updated: 2023/06/13 21:33:02 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s1cpy;
	size_t	s1len;

	s1len = ft_strlen(s1);
	s1cpy = ft_calloc(s1len + 1, sizeof(char));
	if (!s1cpy)
		return (NULL);
	return (ft_memcpy(s1cpy, s1, s1len));
}
