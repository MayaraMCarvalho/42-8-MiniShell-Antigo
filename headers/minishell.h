/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:52:02 by macarval          #+#    #+#             */
/*   Updated: 2023/04/07 14:55:20 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libs/libft/libft.h"

# define SPACES " \n\t\r\f\v"
# define SPECIALS "<>|"
# define HEREDOCNAME ".tmp00"

typedef struct s_cmd
{
	char	*command;
	char	**args;
}			t_cmd;

typedef struct s_block
{
	int				set;
	int				fd[2];
	int				io1_type;
	int				pipe[2];
	char			*heredoc_name;
	t_cmd			*command;
	struct s_block	*next;
	
}					t_block;

typedef struct s_shell
{
	char		*line;
	char		**envp;
	t_block		*pipelist;
}				t_shell;

// base
void 	minishell(t_shell *shell);
char	*make_text(void);

// Pipe_List
t_block	*new_block_on_pipe_list(t_block *pipe_current);

// Commands
int		cd(t_shell shell);
int		env(t_shell shell);
int		pwd(t_shell shell);
int		unset(t_shell shell);
int		export(t_shell shell);
int		is_command(t_shell shell);
int		exit_shell(t_shell shell);

// Echo
int		echo(t_shell shell);
char	*process_text(t_shell shell);

// Handle
char	**handle_close(char *line);
t_shell	make_shell(char *line);
char	*handling(char *split);

// Free
void	free_split(char **split);
int		size_split(char **split);

#endif
