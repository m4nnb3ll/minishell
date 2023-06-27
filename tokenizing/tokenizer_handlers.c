/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_handlers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 21:41:11 by abelayad          #+#    #+#             */
/*   Updated: 2023/05/16 19:06:33 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_handle_separator(char **line_ptr, t_token **token_list)
{
	if (!ft_strncmp(*line_ptr, "<<", 2))
		return (ft_append_separator(T_DLESS, line_ptr, token_list) && 1);
	else if (!ft_strncmp(*line_ptr, ">>", 2))
		return (ft_append_separator(T_DGREAT, line_ptr, token_list) && 1);
	else if (!ft_strncmp(*line_ptr, "<", 1))
		return (ft_append_separator(T_LESS, line_ptr, token_list) && 1);
	else if (!ft_strncmp(*line_ptr, ">", 1))
		return (ft_append_separator(T_GREAT, line_ptr, token_list) && 1);
	else if (!ft_strncmp(*line_ptr, "(", 1))
		return (ft_append_separator(T_O_PARENT, line_ptr, token_list) && 1);
	else if (!ft_strncmp(*line_ptr, ")", 1))
		return (ft_append_separator(T_C_PARENT, line_ptr, token_list) && 1);
	else if (!ft_strncmp(*line_ptr, "&&", 2))
		return (ft_append_separator(T_AND, line_ptr, token_list) && 1);
	else if (!ft_strncmp(*line_ptr, "||", 2))
		return (ft_append_separator(T_OR, line_ptr, token_list) && 1);
	else
		return (ft_append_separator(T_PIPE, line_ptr, token_list) && 1);
}

t_token	*ft_tokenization_handler(char *line)
{
	int		error;
	t_token	*token_list;

	error = 0;
	token_list = NULL;
	while (*line)
	{
		if (error)
			return (ft_clear_token_list(&token_list), NULL);
		if (ft_isspace(*line))
			ft_skip_spaces(&line);
		else if (!ft_strncmp(line, "<", 1) || !ft_strncmp(line, ">", 1)
			|| !ft_strncmp(line, "|", 1) || !ft_strncmp(line, "&&", 2)
			|| !ft_strncmp(line, "(", 1) || !ft_strncmp(line, ")", 1))
			error = (!ft_handle_separator(&line, &token_list) && 1);
		else
			error = (!ft_append_identifier(&line, &token_list) && 1);
	}
	return (token_list);
}
