/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 01:32:13 by abelayad          #+#    #+#             */
/*   Updated: 2023/06/18 16:23:56 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>
# include <termios.h>
# include <limits.h>
# include "libft.h"
# include "tokenizing.h"
# include "parsing.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef enum e_err_msg
{
	ERRMSG_CMD_NOT_FOUND,
	ERRMSG_NO_SUCH_FILE,
	ERRMSG_PERM_DENIED,
	ERRMSG_AMBIGUOUS,
	ERRMSG_TOO_MANY_ARGS,
	ERRMSG_NUMERIC_REQUI
}	t_err_msg;

typedef enum e_err_no
{
	ENO_SUCCESS,
	ENO_GENERAL,
	ENO_CANT_EXEC = 126,
	ENO_NOT_FOUND,
	ENO_EXEC_255 = 255
}	t_err_no;

typedef enum e_ast_direction
{
	TD_LEFT,
	TD_RIGHT
}	t_ast_direction;

typedef struct s_err
{
	t_err_no	no;
	t_err_msg	msg;
	char		*cause;
}	t_err;

typedef struct s_path
{
	t_err	err;
	char	*path;
}	t_path;

typedef struct s_minishell
{
	char			*line;
	t_token			*tokens;
	t_token			*curr_token;
	t_node			*ast;
	int				exit_s;
	bool			signint_child;
	t_parse_err		parse_err;
	int				stdin;
	int				stdout;
	char			**environ;
	t_env			*envlst;
	bool			heredoc_sigint;
	struct termios	original_term;
}					t_minishell;

extern t_minishell	g_minishell;

/* ****************************   BUILTINS   ****************************** */
// * cd.c ********************************************************************
int		ft_cd(char *path);

// * echo.c ******************************************************************
int		ft_echo(char **args);

// * env_utils.c *************************************************************
char	*ft_get_envlst_val(char *key);
bool	ft_env_entry_exists(char *key);
void	ft_update_envlst(char *key, char *value, bool create);

// * env.c *******************************************************************
char	*ft_extract_key(char *str);
char	*ft_extract_value(char *str);
void	ft_init_envlst(void);
int		ft_env(void);

// * exit.c ******************************************************************
void	ft_exit(char **args);

// * export.c ****************************************************************
int		ft_check_key(char *str);
int		ft_export(char **argv);

// * pwd.c *******************************************************************
int		ft_pwd(void);

// * unset.c *****************************************************************
int		ft_unset(char **args);

/* ****************************   CLEANING   ****************************** */
// * ft_clean_ms.c ***********************************************************
void	ft_clean_ms(void);

/* ******************************   EXEC   ******************************** */
// * error_msg.c *************************************************************
int		ft_err_msg(t_err err);

// * exec_builtin.c **********************************************************
int		ft_exec_builtin(char **args);
bool	ft_is_builtin(char *arg);

// * exec_redirect.c *********************************************************
int		ft_out(t_io_node *io_list, int *status);
int		ft_in(t_io_node *io_list, int *status);
int		ft_append(t_io_node *io_list, int *status);

// * exec_utils.c ************************************************************
void	*ft_garbage_collector(void *ptr, bool clean);
bool	ft_is_delimiter(char *delimiter, char *str);

// * exec.c ******************************************************************
int		ft_get_exit_status(int status);
int		ft_exec_node(t_node *tree, bool piped);

// * exist_check.c ***********************************************************
t_err	ft_check_exec(char *file, bool cmd);
t_err	ft_check_read(char *file);
t_err	ft_check_write(char *file);

// * ft_exec_simple_cmd.c ****************************************************
int		ft_check_redirection(t_node *node);
void	ft_reset_stds(bool piped);
int		ft_exec_simple_cmd(t_node *node, bool piped);

// * ft_get_path.c ***********************************************************
t_path	ft_get_path(char *cmd);

// * init_tree.c *************************************************************
void	ft_init_tree(t_node *node);
void	ft_heredoc(t_io_node *io, int p[2]);

/* ****************************   EXPANDER   ****************************** */
// * ft_asterisker.c *********************************************************
bool	ft_match_star(char *pattern, char *str);

// * ft_clean_empty_strs.c ***************************************************
char	*ft_clean_empty_strs(char *str);

// * ft_expand_utils.c *******************************************************
bool	ft_is_valid_var_char(char c);
char	*ft_handle_normal_str(char *str, size_t *i);
char	*ft_handle_squotes(char *str, size_t *i);
char	*ft_handle_dquotes(char *str, size_t *i);

// * ft_expand.c *************************************************************
char	*ft_handle_dollar(char *str, size_t *i);
char	**ft_expand(char *str);

// * ft_expander_split.c *****************************************************
char	**ft_expander_split(char const *s);

// * ft_globber_utils.c ******************************************************
bool	ft_contains_asterisk(char *str);
size_t	ft_str_arr_len(char **str_arr);
size_t	ft_match_count(char *pattern);
char	**ft_join_str_arrs(char ***str_arrs);

// * ft_globber.c ************************************************************
char	**ft_globber(char **expanded);

// * ft_strip_quotes.c *******************************************************
char	*ft_strip_quotes(char *str);

// * heredoc_expander.c ******************************************************
void	ft_heredoc_expander(char *str, int fd);

/* ****************************   MINISHELL   ***************************** */
// * main_signals.c **********************************************************
void	ft_sigquit_handler(int num);
void	ft_init_signals(void);

#endif
