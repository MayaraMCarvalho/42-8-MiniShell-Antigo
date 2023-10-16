/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:02:28 by macarval          #+#    #+#             */
/*   Updated: 2023/10/16 11:56:24 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../libs/libft/libft.h"
#include "../headers/minishell.h"


int	main(int argc, char **argv, char **envp)
{
	t_shell		shell;
	char		*text;

	shell.env = make_list(envp);
	shell.exit_code = 0;
	text = NULL;
	while (true || (argc && argv))
	{
		text = make_text();
		inicialize(&shell);
		shell.line = strtrim_mod(readline(text), " ");
		free(text);
		if (shell.line[0] != '\0')
		{
			add_history(shell.line);
			if (make_shell(&shell))
				verify_builtins(&shell);
			free_shell(shell);
		}
		else
			free(shell.line);
	}
	return (0);
}
