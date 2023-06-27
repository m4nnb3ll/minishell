/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_globber_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 21:38:26 by abelayad          #+#    #+#             */
/*   Updated: 2023/06/18 15:45:31 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_contains_asterisk(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '*')
			return (true);
		i++;
	}
	return (false);
}

size_t	ft_str_arr_len(char **str_arr)
{
	size_t	i;

	i = 0;
	while (str_arr[i])
		i++;
	return (i);
}

size_t	ft_match_count(char *pattern)
{
	DIR				*dir;
	size_t			match_count;
	struct dirent	*entry;

	match_count = 0;
	dir = opendir(".");
	entry = readdir(dir);
	while (entry)
	{
		if (ft_match_star(pattern, entry->d_name))
			match_count++;
		entry = readdir(dir);
	}
	closedir(dir);
	return (match_count);
}

static size_t	ft_multi_arr_strs_count(char ***str_arrs)
{
	size_t	i;
	size_t	j;
	size_t	strs_count;

	i = 0;
	strs_count = 0;
	while (str_arrs[i])
	{
		j = 0;
		while (str_arrs[i][j])
			j++;
		strs_count += j;
		i++;
	}
	return (strs_count);
}

char	**ft_join_str_arrs(char ***str_arrs)
{
	size_t	i;
	size_t	j;
	size_t	strs_count;
	char	**joined;

	strs_count = ft_multi_arr_strs_count(str_arrs);
	joined = (char **)ft_calloc(strs_count + 1, sizeof(char *));
	i = 0;
	strs_count = 0;
	while (str_arrs[i])
	{
		j = 0;
		while (str_arrs[i][j])
		{
			joined[strs_count + j] = ft_strdup(str_arrs[i][j]);
			j++;
		}
		strs_count += j;
		i++;
	}
	return (ft_free_char3(str_arrs), joined);
}
