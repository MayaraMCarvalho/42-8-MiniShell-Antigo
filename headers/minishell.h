/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:52:02 by macarval          #+#    #+#             */
/*   Updated: 2023/05/05 16:52:48 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libs/libft/libft.h"

typedef struct s_shell
{
	char	*line;
	char	*command;
	char	*flag;
	char	*content;
	char	**envp;
}	t_shell;

// Minishell
char	*make_text(void);
void	inicialize(t_shell *shell);
void	free_struct(t_shell shell);

// Commands
int		env(t_shell shell);
int		pwd(t_shell shell);
int		clear(t_shell shell);
int		unset(t_shell shell);
int		export(t_shell shell);
int		is_command(t_shell shell);
int		exit_shell(t_shell shell);

// Cd
int		cd(t_shell shell);
void	setenvp(t_shell shell, char *var, char *content);

// Ls
DIR		*get_folder(void);
int		ls(t_shell shell);
int		is_flag_ls(t_shell shell);
int		get_number(t_shell shell);
void	print_ls(DIR *folder, t_shell shell);

// Echo
int		echo(t_shell shell);
char	*process_text(t_shell shell);

// Handle
char	**handle_close(char *line);
t_shell	make_shell(char *line);
char	*handling(char *split);

// Free
void	free_split(char ***split);
int		size_split(char **split);

// Flags
int		is_flag_null(t_shell shell);
char	verify_flags(t_shell shell, char *pattern);

#endif
