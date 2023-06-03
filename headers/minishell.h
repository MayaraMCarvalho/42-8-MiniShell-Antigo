/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:52:02 by macarval          #+#    #+#             */
/*   Updated: 2023/06/03 19:31:36 by macarval         ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>
# include "../libs/libft/libft.h"

# define ENVP 0
# define GLOBAL 1
# define LOCAL 2

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
int			is_command(t_shell shell);

// Echo
int			c_echo(t_shell shell);
int			print_var(t_shell shell);
int			print_echo(t_shell shell);

// Env
int			c_env(t_shell shell);
t_lst		*make_list(char **envp);
t_lst		*duplicate_env(t_lst *env);
void		insert_last(t_lst **lst, t_lst *new);
t_lst		*insert_front(t_lst *new, char *var, char *msg, int type);

// Export
int			c_export(t_shell shell);
void		sort_export(t_lst *env);
void		print_export(t_lst *env);
int			add_export(t_shell shell);

// Flags
int			is_flag_null(t_shell shell);
char		verify_flags(t_shell shell, char *pattern);

// Free
int			c_exit(t_shell shell);
int			c_clear(t_shell shell);
void		free_list(t_lst *list);
void		free_split(char ***split);
void		free_shell(t_shell shell);

// Handle
void		make_shell(t_shell *shell, char *line);

// Local
int			c_local(t_shell shell);
int			add_local(t_shell shell);
int			is_args_local(char	**split);

// Minishell
char		*get_name(void);
char		*make_text(void);
void		inicialize(t_shell *shell);
void		verify_builtins(t_shell *shell);

// Node
t_lst		*get_min(t_lst *env);
t_lst		*remove_min(t_lst	*list, char *var);
void		add_node(t_shell shell, t_lst *node, t_lst *new_node);

// Unset
int			c_unset(t_shell shell);
int			exe_unset(t_shell shell);

// Utils
int			isalnum_mod(char *c);
char		*strchr_mod(const char *str, int c);
char		*strchr_rev(const char *str, int c);
int			strcmp_order(const char *s1, const char *s2);
int			strcmp_mod(const char *s1, const char *s2);

#endif
