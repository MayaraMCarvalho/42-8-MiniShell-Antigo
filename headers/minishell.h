/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:52:02 by macarval          #+#    #+#             */
/*   Updated: 2023/09/29 09:43:16 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <dirent.h>
# include <term.h>
# include <curses.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libs/libft/libft.h"

# define ENVP 0
# define GLOBAL 1
# define LOCAL 2
# define CLEAR_SCREEN "\033[2J\033[1;1H"

# define FLAG "FLAG"
# define FILE "FILE"
# define PIPE "PIPE"
# define COMMAND "COMMAND"
# define BUILTIN "BUILTIN"
# define CONTENT "CONTENT"
# define OPERATOR "OPERATOR"

typedef struct s_lex
{
	char			*token;
	char			*type;
}	t_lex;

typedef struct s_lst
{
	char			*var;
	char			*msg;
	int				type;
	struct s_lst	*prev;
	struct s_lst	*next;
}	t_lst;

typedef struct s_shell
{
	char		*line;
	char		*command;
	char		*flag;
	char		*content;
	t_lst		*env;
	int			exit_code;
}	t_shell;

// Args
int			is_args(t_shell shell);
t_lst		*find_arg(t_shell shell, char *var);
void		apart_args(t_shell shell, char c, int (*function)(t_shell));

// Cd
int			c_cd(t_shell shell);
void		exe_cd(t_shell shell);
void		update_var(t_shell shell, char *name, char *value);

// Commands
int			c_pwd(t_shell shell);
void		update_(t_shell shell);
int			c_history(t_shell shell);
int			is_command(t_shell shell);

// Echo
int			c_echo(t_shell shell);
int			print_echo(t_shell shell);

// Env
int			c_env(t_shell shell);
t_lst		*make_list(char **envp);
t_lst		*duplicate_env(t_lst *env);
void		insert_last(t_lst **lst, t_lst *new);
t_lst		*insert_front(t_lst *new, char *var, char *msg, int type);

// Exit
int			c_exit(t_shell shell);
int			c_clear(t_shell shell);

// Expansion
int			verify_literal(char *token);
char		*get_var(char *token, t_shell *shell);
char		*apart_var(t_shell *shell, char *token);
void		verify_expasion(char **token, t_shell *shell);


// Export
int			c_export(t_shell shell);
void		sort_export(t_lst *env);
void		print_export(t_lst *env);
int			add_export(t_shell shell);

// Flags
int			is_flag_null(t_shell shell);
char		verify_flags(char *flag, char *pattern);

// Free
void		free_list(t_lst *list);
void		free_array(char ***token);
void		free_shell(t_shell shell);
void		free_double(char ****array);

// Handling
void		make_shell(t_shell *shell);
void		put_token(t_shell *shell, char **token);

// Lexer
char		***lexer(char	**token);
char		***malloc_lexer(int size);

// Local
int			c_local(t_shell shell);
int			add_local(t_shell shell);
int			is_args_local(char	**token);

// Minishell
char		*get_name(void);
char		*make_text(void);
void		inicialize(t_shell *shell);
void		verify_builtins(t_shell *shell);

// Node
t_lst		*get_min(t_lst *env);
t_lst		*remove_min(t_lst	*list, char *var);
void		add_node(t_shell shell, t_lst *node, t_lst *new_node);

// Quotes_Void
int			check_void(char *str, int i);
char		*remove_quotes_void(char *str);
void		clear_quotes(char **token, char *temp);

// Quotes
int			quotes_void(char *str);
void		remove_quotes(char **token);
int			quotes_close(const char *str);
int			verify_quotes(const char *str);

// Split_mod
int			counter(const char *str, char c);
char		**ft_split_mod(char const *s, char c);
size_t		quantity_words(const char *str, char c);
size_t		len_word(const char *str, char c, size_t len);
char		*copy_word(const char *s, char c, size_t len);

// Strcmp
int			strcmp_mod(const char *s1, const char *s2);
int			strcmp_rev(const char *s1, const char *s2);
int			strcmp_order(const char *s1, const char *s2);

// Strtrim_mod
size_t		init(char *s1, char *set);
size_t		final(char *s1, char *set);
char		*strtrim_mod(char *s1, char *set);

// Syntax
void		error_syntax(char	*text);
int			check_prev_next(char	***lex, int	i);
int			syntax_error_check(char	***lex);
int			check_operator(char	***lex, int	i);
int			check_input_redirection(char **text);
int			check_output_redirection(char **text);
int			validate_name_file(char	*name);
int			check_permission(char *text, int permission, char *exit);
int			check_folder(char *text);
int			check_file(char *text);

// Token
char		*id_token(char *token);
int			token_size(char **token);
char		***tokenization(t_shell *shell);
void		copy_token(char ***lex, char **token);

// Unset
int			c_unset(t_shell shell);
int			exe_unset(t_shell shell);

// Utils
int			isalnum_mod(char *c);
char		*strchr_mod(const char *str, int c);
char		*strchr_rev(const char *str, int c);

// Verify
int			verify_commands(char *token);
int			verify_list(char *token, char **list);

#endif
