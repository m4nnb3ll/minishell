/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 20:07:14 by abelayad          #+#    #+#             */
/*   Updated: 2023/06/13 21:33:02 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZING_H
# define TOKENIZING_H

# define PROMPT "minishell$ "

typedef enum e_token_type
{
	T_IDENTIFIER,
	T_LESS,
	T_GREAT,
	T_DLESS,
	T_DGREAT,
	T_PIPE,
	T_O_PARENT,
	T_C_PARENT,
	T_AND,
	T_OR,
	T_NL,
}	t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	struct s_token		*next;
	struct s_token		*prev;
}	t_token;

// tokenizer_appenders.c
int		ft_append_separator(t_token_type type, char **line_ptr,
			t_token **token_list);
int		ft_append_identifier(char **line_ptr, t_token **token_list);

// tokenizer_handlers.c
int		ft_handle_separator(char **line_ptr, t_token **token_list);
t_token	*ft_tokenization_handler(char *line);

// tokenizer_lst.c
t_token	*ft_new_token(char *value, t_token_type type);
void	ft_token_list_add_back(t_token **lst, t_token *new_token);
void	ft_clear_token_list(t_token **lst);

// tokenizer_utils.c
int		ft_is_quote(char c);
int		ft_is_separator(char *s);
void	ft_skip_spaces(char **line);
bool	ft_skip_quotes(char *line, size_t *i);
void	ft_print_quote_err(char c);

// tokenizer.c
t_token	*ft_tokenize(void);

#endif
