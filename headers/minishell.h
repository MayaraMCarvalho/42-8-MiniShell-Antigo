/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:52:02 by macarval          #+#    #+#             */
/*   Updated: 2023/05/20 23:12:07 by macarval         ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>
# include "../libs/libft/libft.h"

# define GLOBAL 0
# define LOCAL 1

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
}	t_shell;

// Minishell
char		*get_name(void);
char		*make_text(void);
void		inicialize(t_shell *shell);
void		free_struct(t_shell shell);

// Commands
int			c_pwd(t_shell shell);
int			c_clear(t_shell shell);
int			c_export(t_shell shell);
int			is_command(t_shell shell);
int			c_exit(t_shell shell);

// Unset
int			c_unset(t_shell shell);
void		remove_var(t_lst *env);
t_lst		*find_var(t_shell shell);

// Cd
int			c_cd(t_shell shell);
void		setenvp(t_shell shell, char *var, char *content);

// Echo
int			c_echo(t_shell shell);
char		*process_text(t_shell shell);

// Env
t_lst		*make_list(char **envp);
void		free_list(t_lst *list);
int			c_env(t_shell shell);
void		insert_last(t_lst **lst, t_lst *new);
t_lst		*insert_front(t_lst *new, char *var, char *msg, int type);

// Handle
char		**handle_close(char *line);
void		make_shell(t_shell *shell, char *line);
char		*handling(char *split);

// Free
void		free_split(char ***split);
int			size_split(char **split);

// Flags
int			is_flag_null(t_shell shell);
char		verify_flags(t_shell shell, char *pattern);

// Utils
char		*strchr_mod(const char *str, int c);
char		*strchr_rev(const char *str, int c);
int			strcmp_mod(const char *s1, const char *s2);

#endif
